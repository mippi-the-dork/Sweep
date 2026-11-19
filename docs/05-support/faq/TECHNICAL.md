# Frequently Asked Questions — Technical

**Sweep v1.0.0 · Source-reviewed technical reference**

## FAQ implementation lookup

| Question | Source implementation |
| --- | --- |
| Menu absent | `FSweepModule::ExtendGraphEditorContextMenu` |
| Selection collapsed | `TickSelectionSnapshots` / `ResolveSelectedVariableGets` |
| Distribute unavailable | `IsSupportedVariableGet` / `CanSweep` |
| Consumer count | `AnalyzeSweep` / `GatherTerminalDestinations` |
| Wrong Get survivor | `CanConsolidate` and `ClickedVariableGet` anchor |
| Same label not equivalent | `AreEquivalentGetters` / `HaveEquivalentInputContext` |
| Reroute removal | `RemoveOrphanedReachableKnots` |
| Reroute preservation | `TransferGetterLinks` |
| Unexpected placement | `DesiredGetterLocation` / `FindAndApplyClearPlacement` |
| Undo/Redo | `FScopedTransaction` and `Modify()` |

## Diagnostic process

First identify whether the issue occurs before the menu appears, at action eligibility, during schema rewiring, or during editor layout. This separates graph-context errors from data-equivalence and placement concerns.

The implementation can report that some connections were accepted without proving the Blueprint will behave correctly after compilation; use the test matrix before treating a fix as verified.

## Scope

Only pure K2 Variable Get nodes are supported in v1.0.0. Avoid assuming the same handler is installed for Materials, Niagara, Behavior Trees or arbitrary editor graph systems.

---

For use cases and troubleshooting, [read Design](DESIGN.md).

**Source:** [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp) · [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
