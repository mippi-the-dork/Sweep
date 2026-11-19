# Editor Integration — Technical

**Sweep v1.0.0 · Source-reviewed technical reference**

## Registration and teardown

<!-- Final IMAGE: docs/assets/media/editor-registration.png -->
<figure class="doc-media" data-kind="image" data-media-id="editor-registration">
  <img src="../../assets/media-placeholder.png" alt="Sweep registers a GraphEditor menu extension and a selection snapshot ticker during its editor-module lifetime." loading="lazy">
  <figcaption>Sweep registers a GraphEditor menu extension and a selection snapshot ticker during its editor-module lifetime.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a lifecycle diagram: StartupModule registers FGraphEditorModule extender and FTSTicker; context-menu callback checks eligibility; ShutdownModule removes extender/ticker and clears weak snapshots.</span></figcaption>
</figure>


`FSweepModule::StartupModule` returns immediately under `IsRunningCommandlet()`, otherwise loads `FGraphEditorModule` and adds an `FGraphEditorMenuExtender_SelectedNode` delegate to `GetAllGraphEditorContextMenuExtender()`. It also registers a core ticker for selection snapshots.

`ShutdownModule` removes the ticker, resets stored snapshots and removes extenders bound to the module.

## Context-menu filtering

`ExtendGraphEditorContextMenu` rejects debugging mode, null graph/node, non-null pin, graph schemas outside `UEdGraphSchema_K2`, and unsupported `UK2Node_VariableGet`. It resolves the current selection and adds a menu section after `EdGraphSchemaNodeActions` only when a command is possible.

## Snapshot mechanism

`TickSelectionSnapshots` iterates Blueprint editors and inspects focused graphs. `ResolveSelectedVariableGets` uses weak node references, filters to the same graph, checks whether the clicked Get belonged to the snapshot, and otherwise returns just the clicked Get.

## Execute-time checks

The menu's `FUIAction` handlers use `FCanExecuteAction` lambdas that re-check `CanSweep` or `CanConsolidate`. The execution lambdas turn weak references into live nodes and perform `SweepMany` or `ConsolidateMany`.

## Risk boundary

This integration uses **editor** GraphEditor/Kismet interfaces. Extending it to other graph editors requires separate type-specific eligibility and correctness rules, not merely exposing the same context menu everywhere.

---

For use cases and troubleshooting, [read Design](DESIGN.md).

**Source:** [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp) · [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
