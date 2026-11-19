# What Sweep Does — Technical

**Sweep v1.0.0 · C++ implementation reference**

## Public implementation boundary

`Sweep.uplugin` declares a single `Sweep` module with `Type: Editor`, `LoadingPhase: PostEngineInit`, `PlatformAllowList: Win64`, and `CanContainContent: false`. There is no runtime module and no new Blueprint node type.

## Responsibilities

<!-- Final IMAGE: docs/assets/media/overview-components.png -->
<figure class="doc-media" data-kind="image" data-media-id="overview-components">
  <img src="../../assets/media-placeholder.png" alt="Sweep separates native editor menu handling from graph transformation and data ownership." loading="lazy">
  <figcaption>Sweep separates native editor menu handling from graph transformation and data ownership.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Diagram FSweepModule for context-menu registration and selection, SweepOperations for graph analysis/rewiring, and UE K2 Schema and UEdGraph as the native engine owners.</span></figcaption>
</figure>


`FSweepModule` registers a `FGraphEditorModule` node-context-menu extender and keeps pre-context-menu graph selections available. `SweepOperations` performs eligibility analysis, graph transformation, schema-aware reconnection and transactional changes.

## Supported graph and node types

`IsSupportedVariableGet` requires a valid `UK2Node_VariableGet`, `IsNodePure()`, a non-null `GetValuePin()`, and an `UEdGraphSchema_K2`-derived graph schema. `CanSweep` additionally requires at least **two distinct terminal input pins** after traversing reroutes.

Consolidation uses `CanConsolidate` to require two or more unique equivalent Gets from the same graph, including the clicked anchor.

## No runtime source dependencies

`Sweep.Build.cs` includes editor dependencies such as `GraphEditor`, `BlueprintGraph`, `Kismet` and `UnrealEd`. Edits occur on editor graph objects; the plugin is not loaded into packaged gameplay.

## Limit

Preservation is an implementation goal, not a substitute for Blueprint compilation and testing. The [verification matrix](../../VERIFICATION_MATRIX.md) distinguishes expected behavior from tested behavior.

---

For the practical workflow, [read Design](DESIGN.md).

**Source:** [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp) · [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
