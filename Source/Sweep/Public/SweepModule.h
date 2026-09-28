#pragma once

#include "CoreMinimal.h"
#include "Containers/Ticker.h"
#include "Modules/ModuleManager.h"

class FExtender;
class FMenuBuilder;
class FUICommandList;
class UEdGraph;
class UEdGraphNode;
class UEdGraphPin;
class UK2Node_VariableGet;

class FSweepModule final : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TSharedRef<FExtender> ExtendGraphEditorContextMenu(
        const TSharedRef<FUICommandList> CommandList,
        const UEdGraph* Graph,
        const UEdGraphNode* Node,
        const UEdGraphPin* Pin,
        bool bIsDebugging);

    void AddSweepMenuEntry(
        FMenuBuilder& MenuBuilder,
        TArray<TWeakObjectPtr<UK2Node_VariableGet>> VariableGets,
        TWeakObjectPtr<UK2Node_VariableGet> ClickedVariableGet);

    TArray<TWeakObjectPtr<UK2Node_VariableGet>> ResolveSelectedVariableGets(
        const UEdGraph* Graph,
        UK2Node_VariableGet* ClickedVariableGet) const;

    bool TickSelectionSnapshots(float DeltaTime);

    FTSTicker::FDelegateHandle SelectionSnapshotTickerHandle;
    TMap<TWeakObjectPtr<UEdGraph>, TArray<TWeakObjectPtr<UEdGraphNode>>> SelectionSnapshots;
};
