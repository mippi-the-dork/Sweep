#include "SweepModule.h"

#include "SweepOperations.h"

#include "BlueprintEditor.h"
#include "BlueprintEditorModule.h"
#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphSchema_K2.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "GraphEditor.h"
#include "GraphEditorModule.h"
#include "K2Node_VariableGet.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "SweepModule"

void FSweepModule::StartupModule()
{
    if (IsRunningCommandlet())
    {
        return;
    }

    FGraphEditorModule& GraphEditorModule = FModuleManager::LoadModuleChecked<FGraphEditorModule>(TEXT("GraphEditor"));
    GraphEditorModule.GetAllGraphEditorContextMenuExtender().Add(
        FGraphEditorModule::FGraphEditorMenuExtender_SelectedNode::CreateRaw(
            this,
            &FSweepModule::ExtendGraphEditorContextMenu));

    SelectionSnapshotTickerHandle = FTSTicker::GetCoreTicker().AddTicker(
        FTickerDelegate::CreateRaw(this, &FSweepModule::TickSelectionSnapshots));
}

void FSweepModule::ShutdownModule()
{
    if (SelectionSnapshotTickerHandle.IsValid())
    {
        FTSTicker::GetCoreTicker().RemoveTicker(SelectionSnapshotTickerHandle);
        SelectionSnapshotTickerHandle.Reset();
    }

    SelectionSnapshots.Reset();

    if (FGraphEditorModule* GraphEditorModule = FModuleManager::GetModulePtr<FGraphEditorModule>(TEXT("GraphEditor")))
    {
        GraphEditorModule->GetAllGraphEditorContextMenuExtender().RemoveAll(
            [this](const FGraphEditorModule::FGraphEditorMenuExtender_SelectedNode& Delegate)
            {
                return Delegate.IsBoundToObject(this);
            });
    }
}

bool FSweepModule::TickSelectionSnapshots(float DeltaTime)
{
    FBlueprintEditorModule* BlueprintEditorModule = FModuleManager::GetModulePtr<FBlueprintEditorModule>(TEXT("Kismet"));
    if (!BlueprintEditorModule)
    {
        return true;
    }

    const TArray<TSharedRef<IBlueprintEditor>> BlueprintEditors = BlueprintEditorModule->GetBlueprintEditors();

    for (const TSharedRef<IBlueprintEditor>& Editor : BlueprintEditors)
    {
        UEdGraph* FocusedGraph = Editor->GetFocusedGraph();
        if (!FocusedGraph)
        {
            continue;
        }

        TSharedRef<FBlueprintEditor> ConcreteEditor = StaticCastSharedRef<FBlueprintEditor>(Editor);
        const FGraphPanelSelectionSet SelectedNodes = ConcreteEditor->GetSelectedNodes();

        TArray<TWeakObjectPtr<UEdGraphNode>>& Snapshot = SelectionSnapshots.FindOrAdd(FocusedGraph);
        Snapshot.Reset();
        Snapshot.Reserve(SelectedNodes.Num());

        for (const auto& SelectedEntry : SelectedNodes)
        {
            UObject* SelectedObject = SelectedEntry;
            if (UEdGraphNode* SelectedNode = Cast<UEdGraphNode>(SelectedObject))
            {
                if (SelectedNode->GetGraph() == FocusedGraph)
                {
                    Snapshot.Add(SelectedNode);
                }
            }
        }
    }

    for (auto It = SelectionSnapshots.CreateIterator(); It; ++It)
    {
        if (!It.Key().IsValid())
        {
            It.RemoveCurrent();
        }
    }

    return true;
}

TArray<TWeakObjectPtr<UK2Node_VariableGet>> FSweepModule::ResolveSelectedVariableGets(
    const UEdGraph* Graph,
    UK2Node_VariableGet* ClickedVariableGet) const
{
    TArray<TWeakObjectPtr<UK2Node_VariableGet>> Result;

    if (!Graph || !ClickedVariableGet)
    {
        return Result;
    }

    const TArray<TWeakObjectPtr<UEdGraphNode>>* Snapshot = SelectionSnapshots.Find(
        TWeakObjectPtr<UEdGraph>(const_cast<UEdGraph*>(Graph)));

    if (Snapshot)
    {
        bool bClickedNodeWasSelected = false;
        for (const TWeakObjectPtr<UEdGraphNode>& WeakNode : *Snapshot)
        {
            if (WeakNode.Get() == ClickedVariableGet)
            {
                bClickedNodeWasSelected = true;
                break;
            }
        }

        if (bClickedNodeWasSelected)
        {
            for (const TWeakObjectPtr<UEdGraphNode>& WeakNode : *Snapshot)
            {
                UK2Node_VariableGet* VariableGet = Cast<UK2Node_VariableGet>(WeakNode.Get());
                if (VariableGet && VariableGet->GetGraph() == Graph && SweepOperations::IsSupportedVariableGet(VariableGet))
                {
                    Result.AddUnique(VariableGet);
                }
            }

            if (!Result.IsEmpty())
            {
                return Result;
            }
        }
    }

    // Fallback for single-node use or for an editor that has not produced a selection snapshot yet.
    if (SweepOperations::IsSupportedVariableGet(ClickedVariableGet))
    {
        Result.Add(ClickedVariableGet);
    }

    return Result;
}

TSharedRef<FExtender> FSweepModule::ExtendGraphEditorContextMenu(
    const TSharedRef<FUICommandList> CommandList,
    const UEdGraph* Graph,
    const UEdGraphNode* Node,
    const UEdGraphPin* Pin,
    bool bIsDebugging)
{
    TSharedRef<FExtender> Extender = MakeShared<FExtender>();

    if (bIsDebugging || !Graph || !Node || Pin)
    {
        return Extender;
    }

    if (!Graph->GetSchema() || !Graph->GetSchema()->IsA<UEdGraphSchema_K2>())
    {
        return Extender;
    }

    UK2Node_VariableGet* VariableGet = const_cast<UK2Node_VariableGet*>(Cast<UK2Node_VariableGet>(Node));
    if (!SweepOperations::IsSupportedVariableGet(VariableGet))
    {
        return Extender;
    }

    TArray<TWeakObjectPtr<UK2Node_VariableGet>> VariableGets = ResolveSelectedVariableGets(Graph, VariableGet);
    if (VariableGets.IsEmpty())
    {
        return Extender;
    }

    Extender->AddMenuExtension(
        TEXT("EdGraphSchemaNodeActions"),
        EExtensionHook::After,
        CommandList,
        FMenuExtensionDelegate::CreateRaw(
            this,
            &FSweepModule::AddSweepMenuEntry,
            MoveTemp(VariableGets),
            TWeakObjectPtr<UK2Node_VariableGet>(VariableGet)));

    return Extender;
}

void FSweepModule::AddSweepMenuEntry(
    FMenuBuilder& MenuBuilder,
    TArray<TWeakObjectPtr<UK2Node_VariableGet>> VariableGets,
    TWeakObjectPtr<UK2Node_VariableGet> ClickedVariableGet)
{
    TArray<UK2Node_VariableGet*> InitialLiveNodes;
    TArray<UK2Node_VariableGet*> InitialDistributableNodes;

    for (const TWeakObjectPtr<UK2Node_VariableGet>& WeakNode : VariableGets)
    {
        if (UK2Node_VariableGet* Node = WeakNode.Get())
        {
            if (SweepOperations::IsSupportedVariableGet(Node))
            {
                InitialLiveNodes.AddUnique(Node);

                if (SweepOperations::CanSweep(Node))
                {
                    InitialDistributableNodes.AddUnique(Node);
                }
            }
        }
    }

    UK2Node_VariableGet* InitialAnchor = ClickedVariableGet.Get();
    const bool bCanDistribute = !InitialDistributableNodes.IsEmpty();
    const bool bCanConsolidate = SweepOperations::CanConsolidate(InitialLiveNodes, InitialAnchor);

    if (!bCanDistribute && !bCanConsolidate)
    {
        return;
    }

    MenuBuilder.BeginSection(TEXT("Sweep"), LOCTEXT("SweepSection", "Sweep"));

    if (bCanDistribute)
    {
        const bool bMultipleDistributable = InitialDistributableNodes.Num() > 1;

        MenuBuilder.AddMenuEntry(
            bMultipleDistributable
                ? LOCTEXT("DistributeSelectedVariableGets", "Distribute Selected Variable Gets")
                : LOCTEXT("DistributeVariableGet", "Distribute Variable Get"),
            bMultipleDistributable
                ? LOCTEXT(
                    "DistributeSelectedVariableGetsTooltip",
                    "Distribute every eligible selected Variable Get in one Undo transaction. Each shared Get is replaced by local copies beside its consumers, while preserving the variable reference and input context. Reroute chains are followed and only reroutes left unused are removed.")
                : LOCTEXT(
                    "DistributeVariableGetTooltip",
                    "Replace this shared Variable Get with local copies beside each consuming node. Sweep preserves the variable reference and input context, follows reroute chains, and removes only reroutes left unused."),
            FSlateIcon(),
            FUIAction(
                FExecuteAction::CreateLambda(
                    [VariableGets]()
                    {
                        TArray<UK2Node_VariableGet*> LiveNodes;
                        for (const TWeakObjectPtr<UK2Node_VariableGet>& WeakNode : VariableGets)
                        {
                            if (UK2Node_VariableGet* Node = WeakNode.Get())
                            {
                                if (SweepOperations::CanSweep(Node))
                                {
                                    LiveNodes.AddUnique(Node);
                                }
                            }
                        }

                        SweepOperations::SweepMany(LiveNodes);
                    }),
                FCanExecuteAction::CreateLambda(
                    [VariableGets]()
                    {
                        for (const TWeakObjectPtr<UK2Node_VariableGet>& WeakNode : VariableGets)
                        {
                            if (SweepOperations::CanSweep(WeakNode.Get()))
                            {
                                return true;
                            }
                        }

                        return false;
                    })));
    }

    if (bCanConsolidate)
    {
        MenuBuilder.AddMenuEntry(
            LOCTEXT("ConsolidateSelectedVariableGets", "Consolidate Selected Variable Gets"),
            LOCTEXT(
                "ConsolidateSelectedVariableGetsTooltip",
                "Merge the selected equivalent Variable Gets into the Get you right-clicked. The right-clicked Get stays in place, direct and rerouted wire paths are preserved, and one Undo restores the original nodes."),
            FSlateIcon(),
            FUIAction(
                FExecuteAction::CreateLambda(
                    [VariableGets, ClickedVariableGet]()
                    {
                        TArray<UK2Node_VariableGet*> LiveNodes;
                        for (const TWeakObjectPtr<UK2Node_VariableGet>& WeakNode : VariableGets)
                        {
                            if (UK2Node_VariableGet* Node = WeakNode.Get())
                            {
                                if (SweepOperations::IsSupportedVariableGet(Node))
                                {
                                    LiveNodes.AddUnique(Node);
                                }
                            }
                        }

                        SweepOperations::ConsolidateMany(LiveNodes, ClickedVariableGet.Get());
                    }),
                FCanExecuteAction::CreateLambda(
                    [VariableGets, ClickedVariableGet]()
                    {
                        TArray<UK2Node_VariableGet*> LiveNodes;
                        for (const TWeakObjectPtr<UK2Node_VariableGet>& WeakNode : VariableGets)
                        {
                            if (UK2Node_VariableGet* Node = WeakNode.Get())
                            {
                                if (SweepOperations::IsSupportedVariableGet(Node))
                                {
                                    LiveNodes.AddUnique(Node);
                                }
                            }
                        }

                        return SweepOperations::CanConsolidate(LiveNodes, ClickedVariableGet.Get());
                    })));
    }

    MenuBuilder.EndSection();
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSweepModule, Sweep)
