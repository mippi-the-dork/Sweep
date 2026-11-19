# Batch Operations and Selection — Technical

**Sweep v1.0.0 · C++ implementation reference**

## Selection snapshots

<!-- Final IMAGE: docs/assets/media/selection-snapshot.png -->
<figure class="doc-media" data-kind="image" data-media-id="selection-snapshot">
  <img src="../../assets/media-placeholder.png" alt="Sweep uses the stored selected Gets only when the right-clicked Get belonged to that selection." loading="lazy">
  <figcaption>Sweep uses the stored selected Gets only when the right-clicked Get belonged to that selection.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Diagram focused Blueprint graph -&gt; selection snapshot -&gt; decision clicked Get in snapshot? Yes uses supported selected Gets; No falls back to clicked Get only.</span></figcaption>
</figure>


`FSweepModule::TickSelectionSnapshots` queries `FBlueprintEditorModule::GetBlueprintEditors()`, inspects each editor's focused graph, and stores weak `UEdGraphNode` pointers for the current `FGraphPanelSelectionSet`, keyed by weak graph pointer. Invalid graph entries are pruned.

`ResolveSelectedVariableGets` uses the saved set **only when the clicked Variable Get was a member**. It filters to supported Gets in the same graph. Otherwise it falls back to the clicked Get alone.

## Context menu authorization

`AddSweepMenuEntry` re-checks live node pointers and collects `CanSweep`-eligible Gets separately from all supported Gets. **Distribute Selected Variable Gets** appears when more than one eligible source can be distributed. Consolidation uses `CanConsolidate(InitialLiveNodes, InitialAnchor)`.

Both menu actions have `FCanExecuteAction` lambdas that revalidate the relevant live Gets at execution time, guarding against stale selections.

## Batch transaction semantics

`SweepMany` deduplicates and selects one shared graph for eligible nodes, creates an `FScopedTransaction` and invokes `SweepSingle` on each. Only changed results trigger Blueprint modification notification. `ConsolidateMany` also uses one transaction for its selected Get group.

## Performance concern

Selection snapshotting uses a core ticker across open Blueprint editors; it is not an event-only mechanism. Any future performance review should measure costs with large selections and several open editors rather than assuming constant zero overhead.

---

For practical use, [read Design](DESIGN.md).

**Source:** [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp) · [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp)
