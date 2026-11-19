# Troubleshooting and Recovery — Technical

**Sweep v1.0.0 · Source-reviewed technical reference**

## Layered triage

1. **Module installation:** Editor-only descriptor, compatible Win64 UE version, module loaded and plugins enabled.
2. **Menu integration:** `FGraphEditorModule` extender registration; non-debug, node-body context and K2 graph schema.
3. **Selection:** prior snapshot exists and the clicked Get belonged to the selected group; stale weak nodes are filtered.
4. **Eligibility:** supported pure Get, terminal consumers for Distribute, full variable/context equivalence for Consolidate.
5. **Mutation:** spawned Get and K2 schema connections; reconnect failures and per-source restoration.
6. **Layout:** estimated size, fixed offsets, bounded clearance search and 16-unit snapping.
7. **Transactions:** graph/Blueprint `Modify()`, `NotifyGraphChanged()`, Undo/Redo and post-operation compilation.

## How to isolate a regression

Use one minimal Blueprint graph and **save a copy**. Record the exact pin topology and source/context defaults. Apply the action, compare link sets, compile, Undo, then Redo. If reroutes are involved, distinguish shared/live paths from orphaned paths.

For failed consolidation, capture whether another source Get was already successfully merged before a later transfer failed. The code rolls back the failed source, not necessarily the whole batch.

## Testing status

These are source-directed diagnostics. They are **not** claims that every engine configuration, input-pin type or platform was tested. Use the [verification matrix](../../VERIFICATION_MATRIX.md) to record actual results.

---

For use cases and troubleshooting, [read Design](DESIGN.md).

**Source:** [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp) · [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
