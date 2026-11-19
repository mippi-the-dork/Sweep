# Transactions and Safe Reconnection — Technical

**Sweep v1.0.0 · Source-verified implementation**

## Transaction boundaries

`SweepMany` creates `FScopedTransaction("Sweep Variable Get")` for one source and `FScopedTransaction("Sweep Variable Gets")` for multiple; `ConsolidateMany` uses `FScopedTransaction("Consolidate Variable Gets")`.

Blueprint and graph objects call `Modify()`. Affected nodes call `Modify()` around edits; successful operations call `FBlueprintEditorUtils::MarkBlueprintAsModified` and `SharedGraph->NotifyGraphChanged()`.

## Schema-governed links

Both operations use `UEdGraphSchema_K2::TryCreateConnection` rather than writing arbitrary `LinkedTo` arrays directly. This lets the current K2 schema validate connection compatibility.

## Failure handling differs

**Distribution:** each new Get is destroyed if no destination accepts its connection. If some destinations succeed, the source may remain for any still-live links. Cleanup is limited to orphaned reachable reroutes.

**Consolidation:** `TransferGetterLinks` snapshots the source's original outgoing connections; on a failed schema connection it attempts to restore that source wire plus the wires previously moved from that same source. It returns false so that Get isn't destroyed.

## Scope of the safeguard

Rollback is **per redundant source Get**. A multi-source operation may have already committed other successful transfers inside the surrounding transaction before reaching a failing source. Users can Undo the transaction for a full graph-level reversal.

## Verification priorities

Test undo/redo and compile after partial schema failures, rerouted destinations, multiple equivalent Gets and multi-selection distribution. A visual screenshot alone is insufficient to prove pin-link integrity.

---

For expected workflows, [read Design](DESIGN.md).

**Source:** [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
