#include "SweepOperations.h"

#include "EdGraph/EdGraph.h"
#include "EdGraph/EdGraphNode.h"
#include "EdGraph/EdGraphPin.h"
#include "EdGraphNode_Comment.h"
#include "EdGraphSchema_K2.h"
#include "EdGraphSchema_K2_Actions.h"
#include "K2Node_Knot.h"
#include "K2Node_VariableGet.h"
#include "Kismet2/BlueprintEditorUtils.h"
#include "ScopedTransaction.h"

#define LOCTEXT_NAMESPACE "SweepOperations"

namespace
{
    constexpr int32 GetterHorizontalOffset = 220;
    constexpr int32 ApproximatePinSpacing = 28;
    constexpr int32 ApproximateHeaderOffset = 36;
    constexpr int32 ApproximateGetterOutputPinOffset = 36;
    constexpr int32 PlacementClearance = 18;
    constexpr int32 PlacementVerticalStep = 56;
    constexpr int32 PlacementAttemptsPerDirection = 8;

    struct FSweepAnalysis
    {
        TArray<UEdGraphPin*> DestinationPins;
        TSet<UK2Node_Knot*> ReachableKnots;
    };

    bool IsSupportedGraph(const UEdGraph* Graph)
    {
        return Graph && Graph->GetSchema() && Graph->GetSchema()->IsA<UEdGraphSchema_K2>();
    }

    bool HaveSameLinkedPins(const UEdGraphPin* A, const UEdGraphPin* B)
    {
        if (!A || !B || A->LinkedTo.Num() != B->LinkedTo.Num())
        {
            return false;
        }

        for (const UEdGraphPin* LinkedPin : A->LinkedTo)
        {
            if (!B->LinkedTo.Contains(const_cast<UEdGraphPin*>(LinkedPin)))
            {
                return false;
            }
        }

        return true;
    }

    bool HaveEquivalentInputContext(
        const UK2Node_VariableGet* A,
        const UK2Node_VariableGet* B)
    {
        if (!A || !B || A->SelfContextInfo != B->SelfContextInfo)
        {
            return false;
        }

        TArray<const UEdGraphPin*> AInputs;
        TArray<const UEdGraphPin*> BInputs;

        for (const UEdGraphPin* Pin : A->Pins)
        {
            if (Pin && Pin->Direction == EGPD_Input)
            {
                AInputs.Add(Pin);
            }
        }

        for (const UEdGraphPin* Pin : B->Pins)
        {
            if (Pin && Pin->Direction == EGPD_Input)
            {
                BInputs.Add(Pin);
            }
        }

        if (AInputs.Num() != BInputs.Num())
        {
            return false;
        }

        for (const UEdGraphPin* APin : AInputs)
        {
            const UEdGraphPin* MatchingPin = nullptr;
            for (const UEdGraphPin* BPinCandidate : BInputs)
            {
                if (BPinCandidate && BPinCandidate->PinName == APin->PinName)
                {
                    MatchingPin = BPinCandidate;
                    break;
                }
            }

            if (!MatchingPin)
            {
                return false;
            }

            if (APin->DefaultValue != MatchingPin->DefaultValue ||
                APin->DefaultObject != MatchingPin->DefaultObject ||
                !APin->DefaultTextValue.EqualTo(MatchingPin->DefaultTextValue) ||
                !HaveSameLinkedPins(APin, MatchingPin))
            {
                return false;
            }
        }

        return true;
    }

    bool AreEquivalentGetters(
        const UK2Node_VariableGet* A,
        const UK2Node_VariableGet* B)
    {
        if (!A || !B || A == B)
        {
            return A == B;
        }

        if (A->GetGraph() != B->GetGraph() ||
            !A->IsNodePure() ||
            !B->IsNodePure() ||
            !A->VariableReference.IsSameReference(B->VariableReference))
        {
            return false;
        }

        return HaveEquivalentInputContext(A, B);
    }

    void GatherTerminalDestinations(
        UEdGraphPin* OutputPin,
        FSweepAnalysis& Analysis,
        TSet<UEdGraphPin*>& VisitedOutputs)
    {
        if (!OutputPin || VisitedOutputs.Contains(OutputPin))
        {
            return;
        }

        VisitedOutputs.Add(OutputPin);

        // Copy the link array because later sweep execution mutates pin links.
        const TArray<UEdGraphPin*> LinkedPins = OutputPin->LinkedTo;
        for (UEdGraphPin* LinkedPin : LinkedPins)
        {
            if (!LinkedPin)
            {
                continue;
            }

            UEdGraphNode* OwningNode = LinkedPin->GetOwningNode();
            if (!OwningNode)
            {
                continue;
            }

            if (UK2Node_Knot* Knot = Cast<UK2Node_Knot>(OwningNode))
            {
                // We only follow the normal data-flow direction: source output -> knot input -> knot output.
                if (LinkedPin == Knot->GetInputPin())
                {
                    Analysis.ReachableKnots.Add(Knot);
                    GatherTerminalDestinations(Knot->GetOutputPin(), Analysis, VisitedOutputs);
                }

                continue;
            }

            if (LinkedPin->Direction == EGPD_Input)
            {
                Analysis.DestinationPins.AddUnique(LinkedPin);
            }
        }
    }

    FSweepAnalysis AnalyzeSweep(UK2Node_VariableGet* VariableGet)
    {
        FSweepAnalysis Analysis;

        if (!VariableGet)
        {
            return Analysis;
        }

        UEdGraphPin* ValuePin = VariableGet->GetValuePin();
        if (!ValuePin)
        {
            return Analysis;
        }

        TSet<UEdGraphPin*> VisitedOutputs;
        GatherTerminalDestinations(ValuePin, Analysis, VisitedOutputs);
        return Analysis;
    }

    UEdGraphPin* FindMatchingInputPin(UK2Node_VariableGet* Node, const UEdGraphPin* SourcePin)
    {
        if (!Node || !SourcePin)
        {
            return nullptr;
        }

        for (UEdGraphPin* Candidate : Node->Pins)
        {
            if (Candidate && Candidate->Direction == EGPD_Input && Candidate->PinName == SourcePin->PinName)
            {
                return Candidate;
            }
        }

        return nullptr;
    }

    int32 GetInputPinIndex(const UEdGraphPin* DestinationPin)
    {
        if (!DestinationPin)
        {
            return 0;
        }

        const UEdGraphNode* DestinationNode = DestinationPin->GetOwningNode();
        if (!DestinationNode)
        {
            return 0;
        }

        int32 InputIndex = 0;
        for (const UEdGraphPin* Pin : DestinationNode->Pins)
        {
            if (!Pin || Pin->Direction != EGPD_Input)
            {
                continue;
            }

            if (Pin == DestinationPin)
            {
                return InputIndex;
            }

            ++InputIndex;
        }

        return InputIndex;
    }

    float ApproximateDestinationPinY(const UEdGraphPin* DestinationPin)
    {
        const UEdGraphNode* DestinationNode = DestinationPin ? DestinationPin->GetOwningNode() : nullptr;
        if (!DestinationNode)
        {
            return 0.0f;
        }

        return static_cast<float>(DestinationNode->NodePosY + ApproximateHeaderOffset + (GetInputPinIndex(DestinationPin) * ApproximatePinSpacing));
    }

    FVector2D DesiredGetterLocation(
        const UEdGraphNode* DestinationNode,
        const TArray<UEdGraphPin*>& DestinationPins)
    {
        if (!DestinationNode)
        {
            return FVector2D::ZeroVector;
        }

        float TargetPinY = static_cast<float>(DestinationNode->NodePosY + ApproximateHeaderOffset);
        if (!DestinationPins.IsEmpty())
        {
            double Sum = 0.0;
            int32 Count = 0;
            for (const UEdGraphPin* Pin : DestinationPins)
            {
                if (Pin)
                {
                    Sum += ApproximateDestinationPinY(Pin);
                    ++Count;
                }
            }

            if (Count > 0)
            {
                TargetPinY = static_cast<float>(Sum / Count);
            }
        }

        return FVector2D(
            DestinationNode->NodePosX - GetterHorizontalOffset,
            TargetPinY - ApproximateGetterOutputPinOffset);
    }

    void CopyInputContext(
        const UK2Node_VariableGet* SourceNode,
        UK2Node_VariableGet* NewNode,
        const UEdGraphSchema_K2* Schema)
    {
        if (!SourceNode || !NewNode || !Schema)
        {
            return;
        }

        for (const UEdGraphPin* SourcePin : SourceNode->Pins)
        {
            if (!SourcePin || SourcePin->Direction != EGPD_Input)
            {
                continue;
            }

            UEdGraphPin* NewPin = FindMatchingInputPin(NewNode, SourcePin);
            if (!NewPin)
            {
                continue;
            }

            NewPin->DefaultValue = SourcePin->DefaultValue;
            NewPin->DefaultObject = SourcePin->DefaultObject;
            NewPin->DefaultTextValue = SourcePin->DefaultTextValue;

            for (UEdGraphPin* LinkedPin : SourcePin->LinkedTo)
            {
                if (LinkedPin)
                {
                    Schema->TryCreateConnection(LinkedPin, NewPin);
                }
            }
        }
    }

    UK2Node_VariableGet* SpawnMatchingGetter(
        UK2Node_VariableGet* SourceNode,
        UEdGraph* Graph,
        const FVector2D& Location,
        const UEdGraphSchema_K2* Schema)
    {
        if (!SourceNode || !Graph || !Schema)
        {
            return nullptr;
        }

        UK2Node_VariableGet* NewNode = FEdGraphSchemaAction_K2NewNode::SpawnNode<UK2Node_VariableGet>(
            Graph,
            Location,
            EK2NewNodeFlags::None,
            [SourceNode](UK2Node_VariableGet* Node)
            {
                Node->VariableReference = SourceNode->VariableReference;
                Node->SelfContextInfo = SourceNode->SelfContextInfo;
            });

        if (!NewNode)
        {
            return nullptr;
        }

        CopyInputContext(SourceNode, NewNode, Schema);
        return NewNode;
    }

    FVector2D GetEstimatedNodeSize(UEdGraphNode* Node)
    {
        if (!Node)
        {
            return FVector2D(160.0, 48.0);
        }

        const float Width = Node->NodeWidth > 0
            ? static_cast<float>(Node->NodeWidth)
            : FMath::Max(UEdGraphSchema_K2::EstimateNodeWidth(Node), 80.0f);

        const float Height = Node->NodeHeight > 0
            ? static_cast<float>(Node->NodeHeight)
            : FMath::Max(UEdGraphSchema_K2::EstimateNodeHeight(Node), 40.0f);

        return FVector2D(Width, Height);
    }

    bool RectsOverlapWithClearance(
        const FVector2D& APosition,
        const FVector2D& ASize,
        const FVector2D& BPosition,
        const FVector2D& BSize)
    {
        return !(
            APosition.X + ASize.X + PlacementClearance <= BPosition.X ||
            BPosition.X + BSize.X + PlacementClearance <= APosition.X ||
            APosition.Y + ASize.Y + PlacementClearance <= BPosition.Y ||
            BPosition.Y + BSize.Y + PlacementClearance <= APosition.Y);
    }

    bool WouldOverlapGraph(
        UEdGraph* Graph,
        UEdGraphNode* NewNode,
        const FVector2D& Candidate,
        const TSet<UEdGraphNode*>& IgnoreNodes)
    {
        if (!Graph || !NewNode)
        {
            return false;
        }

        const FVector2D NewSize = GetEstimatedNodeSize(NewNode);

        for (const TObjectPtr<UEdGraphNode>& ExistingNodePtr : Graph->Nodes)
        {
            UEdGraphNode* ExistingNode = ExistingNodePtr.Get();
            if (!ExistingNode || ExistingNode == NewNode || IgnoreNodes.Contains(ExistingNode))
            {
                continue;
            }

            // Comment boxes are containers, not obstacles. Generated Gets should be allowed to stay
            // inside the same visual grouping as their destination.
            if (ExistingNode->IsA<UEdGraphNode_Comment>())
            {
                continue;
            }

            const FVector2D ExistingPosition(ExistingNode->NodePosX, ExistingNode->NodePosY);
            const FVector2D ExistingSize = GetEstimatedNodeSize(ExistingNode);

            if (RectsOverlapWithClearance(Candidate, NewSize, ExistingPosition, ExistingSize))
            {
                return true;
            }
        }

        return false;
    }

    void FindAndApplyClearPlacement(
        UEdGraph* Graph,
        UK2Node_VariableGet* NewGetter,
        const FVector2D& DesiredLocation,
        const TSet<UEdGraphNode*>& IgnoreNodes)
    {
        if (!Graph || !NewGetter)
        {
            return;
        }

        TArray<FVector2D> Candidates;
        Candidates.Reserve(1 + PlacementAttemptsPerDirection * 2);
        Candidates.Add(DesiredLocation);

        for (int32 Step = 1; Step <= PlacementAttemptsPerDirection; ++Step)
        {
            const float Offset = static_cast<float>(Step * PlacementVerticalStep);
            Candidates.Add(FVector2D(DesiredLocation.X, DesiredLocation.Y + Offset));
            Candidates.Add(FVector2D(DesiredLocation.X, DesiredLocation.Y - Offset));
        }

        FVector2D Chosen = DesiredLocation;
        for (const FVector2D& Candidate : Candidates)
        {
            if (!WouldOverlapGraph(Graph, NewGetter, Candidate, IgnoreNodes))
            {
                Chosen = Candidate;
                break;
            }
        }

        NewGetter->NodePosX = FMath::RoundToInt(Chosen.X);
        NewGetter->NodePosY = FMath::RoundToInt(Chosen.Y);
        NewGetter->SnapToGrid(16);
    }

    void RemoveOrphanedReachableKnots(const TSet<UK2Node_Knot*>& ReachableKnots)
    {
        TSet<UK2Node_Knot*> RemovedKnots;

        bool bRemovedAny = true;
        while (bRemovedAny)
        {
            bRemovedAny = false;

            for (UK2Node_Knot* Knot : ReachableKnots)
            {
                if (!IsValid(Knot) || RemovedKnots.Contains(Knot))
                {
                    continue;
                }

                UEdGraphPin* OutputPin = Knot->GetOutputPin();
                if (OutputPin && OutputPin->LinkedTo.IsEmpty())
                {
                    Knot->Modify();
                    Knot->DestroyNode();
                    RemovedKnots.Add(Knot);
                    bRemovedAny = true;
                }
            }
        }
    }

    bool TransferGetterLinks(
        UK2Node_VariableGet* SourceGetter,
        UK2Node_VariableGet* AnchorGetter,
        const UEdGraphSchema_K2* Schema)
    {
        if (!SourceGetter || !AnchorGetter || !Schema || SourceGetter == AnchorGetter)
        {
            return false;
        }

        UEdGraphPin* SourceValuePin = SourceGetter->GetValuePin();
        UEdGraphPin* AnchorValuePin = AnchorGetter->GetValuePin();
        if (!SourceValuePin || !AnchorValuePin)
        {
            return false;
        }

        SourceGetter->Modify();
        AnchorGetter->Modify();

        const TArray<UEdGraphPin*> OriginalLinks = SourceValuePin->LinkedTo;
        TArray<UEdGraphPin*> TransferredLinks;

        for (UEdGraphPin* LinkedPin : OriginalLinks)
        {
            if (!LinkedPin)
            {
                continue;
            }

            if (UEdGraphNode* LinkedNode = LinkedPin->GetOwningNode())
            {
                LinkedNode->Modify();
            }

            SourceValuePin->BreakLinkTo(LinkedPin);

            if (Schema->TryCreateConnection(AnchorValuePin, LinkedPin))
            {
                TransferredLinks.Add(LinkedPin);
                continue;
            }

            // If an unexpected schema rule rejects any wire, restore this getter exactly rather than
            // leaving a half-consolidated source node behind.
            Schema->TryCreateConnection(SourceValuePin, LinkedPin);

            for (UEdGraphPin* TransferredPin : TransferredLinks)
            {
                if (!TransferredPin)
                {
                    continue;
                }

                AnchorValuePin->BreakLinkTo(TransferredPin);
                Schema->TryCreateConnection(SourceValuePin, TransferredPin);
            }

            return false;
        }

        return SourceValuePin->LinkedTo.IsEmpty();
    }

    bool SweepSingle(UK2Node_VariableGet* VariableGet)
    {
        if (!SweepOperations::CanSweep(VariableGet))
        {
            return false;
        }

        UEdGraph* Graph = VariableGet->GetGraph();
        const UEdGraphSchema_K2* Schema = Cast<UEdGraphSchema_K2>(Graph ? Graph->GetSchema() : nullptr);
        UEdGraphPin* OriginalValuePin = VariableGet->GetValuePin();

        if (!Graph || !Schema || !OriginalValuePin)
        {
            return false;
        }

        const FSweepAnalysis Analysis = AnalyzeSweep(VariableGet);
        if (Analysis.DestinationPins.Num() < 2)
        {
            return false;
        }

        TMap<UEdGraphNode*, TArray<UEdGraphPin*>> DestinationsByNode;
        for (UEdGraphPin* DestinationPin : Analysis.DestinationPins)
        {
            if (DestinationPin && DestinationPin->Direction == EGPD_Input && DestinationPin->GetOwningNode())
            {
                DestinationsByNode.FindOrAdd(DestinationPin->GetOwningNode()).Add(DestinationPin);
            }
        }

        if (DestinationsByNode.IsEmpty())
        {
            return false;
        }

        VariableGet->Modify();
        bool bCreatedAny = false;

        for (TPair<UEdGraphNode*, TArray<UEdGraphPin*>>& Pair : DestinationsByNode)
        {
            UEdGraphNode* DestinationNode = Pair.Key;
            TArray<UEdGraphPin*>& DestinationPins = Pair.Value;

            if (!DestinationNode || DestinationPins.IsEmpty())
            {
                continue;
            }

            DestinationNode->Modify();

            const FVector2D DesiredLocation = DesiredGetterLocation(DestinationNode, DestinationPins);
            UK2Node_VariableGet* NewGetter = SpawnMatchingGetter(VariableGet, Graph, DesiredLocation, Schema);
            if (!NewGetter)
            {
                continue;
            }

            // Ignore the source and destination while finding a clear spot. The getter is deliberately
            // placed beside its destination, and the source may be deleted at the end of this operation.
            TSet<UEdGraphNode*> IgnoreNodes;
            IgnoreNodes.Add(VariableGet);
            IgnoreNodes.Add(DestinationNode);
            FindAndApplyClearPlacement(Graph, NewGetter, DesiredLocation, IgnoreNodes);

            UEdGraphPin* NewValuePin = NewGetter->GetValuePin();
            if (!NewValuePin)
            {
                NewGetter->DestroyNode();
                continue;
            }

            bool bConnectedThisGetter = false;
            for (UEdGraphPin* DestinationPin : DestinationPins)
            {
                if (DestinationPin && Schema->TryCreateConnection(NewValuePin, DestinationPin))
                {
                    bConnectedThisGetter = true;
                    bCreatedAny = true;
                }
            }

            if (!bConnectedThisGetter)
            {
                NewGetter->DestroyNode();
            }
        }

        if (!bCreatedAny)
        {
            return false;
        }

        // Rewiring terminal inputs can leave the original reroute path with no consumers. Remove only
        // knots reachable from this source whose output genuinely becomes empty. Shared/live reroutes stay.
        RemoveOrphanedReachableKnots(Analysis.ReachableKnots);

        // Direct consumers are replaced by TryCreateConnection. Reroute consumers disappear as orphaned
        // knot chains are pruned. Delete the source only when no connection still depends on it.
        if (OriginalValuePin->LinkedTo.IsEmpty())
        {
            VariableGet->DestroyNode();
        }

        return true;
    }
}

bool SweepOperations::IsSupportedVariableGet(UK2Node_VariableGet* VariableGet)
{
    return VariableGet &&
        VariableGet->IsNodePure() &&
        IsSupportedGraph(VariableGet->GetGraph()) &&
        VariableGet->GetValuePin();
}

bool SweepOperations::CanSweep(UK2Node_VariableGet* VariableGet)
{
    if (!IsSupportedVariableGet(VariableGet))
    {
        return false;
    }

    const FSweepAnalysis Analysis = AnalyzeSweep(VariableGet);
    return Analysis.DestinationPins.Num() >= 2;
}

bool SweepOperations::Sweep(UK2Node_VariableGet* VariableGet)
{
    TArray<UK2Node_VariableGet*> Nodes;
    if (VariableGet)
    {
        Nodes.Add(VariableGet);
    }

    return SweepMany(Nodes);
}

bool SweepOperations::SweepMany(const TArray<UK2Node_VariableGet*>& VariableGets)
{
    TArray<UK2Node_VariableGet*> EligibleNodes;
    UEdGraph* SharedGraph = nullptr;

    for (UK2Node_VariableGet* VariableGet : VariableGets)
    {
        if (!CanSweep(VariableGet))
        {
            continue;
        }

        UEdGraph* Graph = VariableGet->GetGraph();
        if (!SharedGraph)
        {
            SharedGraph = Graph;
        }

        if (Graph == SharedGraph)
        {
            EligibleNodes.AddUnique(VariableGet);
        }
    }

    if (!SharedGraph || EligibleNodes.IsEmpty())
    {
        return false;
    }

    UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraph(SharedGraph);
    if (!Blueprint)
    {
        return false;
    }

    const FScopedTransaction Transaction(
        EligibleNodes.Num() > 1
            ? LOCTEXT("SweepVariableGetsTransaction", "Sweep Variable Gets")
            : LOCTEXT("SweepVariableGetTransaction", "Sweep Variable Get"));

    Blueprint->Modify();
    SharedGraph->Modify();

    bool bChangedAny = false;
    for (UK2Node_VariableGet* VariableGet : EligibleNodes)
    {
        if (IsValid(VariableGet) && SweepSingle(VariableGet))
        {
            bChangedAny = true;
        }
    }

    if (bChangedAny)
    {
        FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
        SharedGraph->NotifyGraphChanged();
    }

    return bChangedAny;
}

bool SweepOperations::CanConsolidate(
    const TArray<UK2Node_VariableGet*>& VariableGets,
    UK2Node_VariableGet* AnchorVariableGet)
{
    if (!IsSupportedVariableGet(AnchorVariableGet) || VariableGets.Num() < 2)
    {
        return false;
    }

    int32 UniqueEligibleCount = 0;
    TSet<UK2Node_VariableGet*> Seen;

    for (UK2Node_VariableGet* VariableGet : VariableGets)
    {
        if (!IsSupportedVariableGet(VariableGet) || Seen.Contains(VariableGet))
        {
            continue;
        }

        if (!AreEquivalentGetters(AnchorVariableGet, VariableGet))
        {
            return false;
        }

        Seen.Add(VariableGet);
        ++UniqueEligibleCount;
    }

    return Seen.Contains(AnchorVariableGet) && UniqueEligibleCount >= 2;
}

bool SweepOperations::ConsolidateMany(
    const TArray<UK2Node_VariableGet*>& VariableGets,
    UK2Node_VariableGet* AnchorVariableGet)
{
    if (!CanConsolidate(VariableGets, AnchorVariableGet))
    {
        return false;
    }

    UEdGraph* SharedGraph = AnchorVariableGet->GetGraph();
    const UEdGraphSchema_K2* Schema = Cast<UEdGraphSchema_K2>(SharedGraph ? SharedGraph->GetSchema() : nullptr);
    UBlueprint* Blueprint = FBlueprintEditorUtils::FindBlueprintForGraph(SharedGraph);

    if (!SharedGraph || !Schema || !Blueprint)
    {
        return false;
    }

    TArray<UK2Node_VariableGet*> UniqueNodes;
    for (UK2Node_VariableGet* VariableGet : VariableGets)
    {
        if (IsSupportedVariableGet(VariableGet) &&
            VariableGet->GetGraph() == SharedGraph &&
            AreEquivalentGetters(AnchorVariableGet, VariableGet))
        {
            UniqueNodes.AddUnique(VariableGet);
        }
    }

    if (UniqueNodes.Num() < 2 || !UniqueNodes.Contains(AnchorVariableGet))
    {
        return false;
    }

    const FScopedTransaction Transaction(
        LOCTEXT("ConsolidateVariableGetsTransaction", "Consolidate Variable Gets"));

    Blueprint->Modify();
    SharedGraph->Modify();
    AnchorVariableGet->Modify();

    bool bChangedAny = false;

    for (UK2Node_VariableGet* VariableGet : UniqueNodes)
    {
        if (!IsValid(VariableGet) || VariableGet == AnchorVariableGet)
        {
            continue;
        }

        if (TransferGetterLinks(VariableGet, AnchorVariableGet, Schema))
        {
            VariableGet->DestroyNode();
            bChangedAny = true;
        }
    }

    if (bChangedAny)
    {
        FBlueprintEditorUtils::MarkBlueprintAsModified(Blueprint);
        SharedGraph->NotifyGraphChanged();
    }

    return bChangedAny;
}

#undef LOCTEXT_NAMESPACE
