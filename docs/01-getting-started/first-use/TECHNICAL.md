# First Refactor — Technical

**Sweep v1.0.0 · C++ implementation reference**

## Context-menu entry conditions

`ExtendGraphEditorContextMenu` returns no extender during debugging, for null graph/node, when a **pin** was clicked, or for non-K2 schemas. It then casts to `UK2Node_VariableGet`, checks `SweepOperations::IsSupportedVariableGet`, and collects eligible selection snapshots.

`AddSweepMenuEntry` offers **Distribute** if one selected source satisfies `CanSweep`, and **Consolidate** only if the anchor plus supported selected Gets satisfy `CanConsolidate`. The section is omitted if neither is available.

## Refactoring pathway

An eligible action creates an `FScopedTransaction`, calls `Modify()` on Blueprint and graph objects, and notifies the graph and Blueprint when a change occurred. Distribution is handled by `SweepMany`, consolidation by `ConsolidateMany`.

## Expected verification

A native editor test should compare source and destination pin links before/after, validate one-step Undo/Redo and compile the Blueprint. The documentation's examples are not evidence of a completed UE session test; see [verification matrix](../../VERIFICATION_MATRIX.md).

---

For the practical workflow, [read Design](DESIGN.md).

**Source:** [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp) · [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
