# Distribute Variable Gets — Technical

**Sweep v1.0.0 · C++ implementation reference**

## Eligibility and analysis

`SweepOperations::CanSweep` first calls `IsSupportedVariableGet`, then `AnalyzeSweep`, requiring `Analysis.DestinationPins.Num() >= 2`. `GatherTerminalDestinations` walks from `GetValuePin` through a `UK2Node_Knot` input→output and records unique non-reroute `EGPD_Input` pins. A visited-output set prevents cycles or repeated walks.

## Graph mutation

`SweepSingle` groups destination pins by their owning `UEdGraphNode` in `TMap<UEdGraphNode*, TArray<UEdGraphPin*>>`. It spawns a new `UK2Node_VariableGet` through `FEdGraphSchemaAction_K2NewNode::SpawnNode` for each destination node, preserving `VariableReference` and `SelfContextInfo`. `CopyInputContext` copies matching input default values, objects and text and attempts to recreate linked input context.

For each terminal consumer, `UEdGraphSchema_K2::TryCreateConnection` reconnects the new output. A new Get with no successful destination is destroyed. If no new destination connection succeeds, `SweepSingle` returns false.

## Cleanup

`RemoveOrphanedReachableKnots` iteratively deletes only reachable knots with no outgoing links. The old source Get is destroyed only when its value output's `LinkedTo` is empty. The remaining graph is marked modified and notified through the batch entry point.

## Nuance

Some destinations can fail schema reconnection while others succeed. The source retains a Get if live connections remain rather than claiming all-or-nothing behavior. The edit still needs normal Blueprint compilation and an Undo check in the target project.

---

For practical use, [read Design](DESIGN.md).

**Source:** [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp) · [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp)
