# Editor Integration — Design

**Sweep v1.0.0 · User guide**

## Sweep lives where you already work

Sweep is not a separate utility window. Its actions are available directly from the **Blueprint graph node context menu**, only when the clicked pure Variable Get and selected nodes meet the required rules.

## Menu behavior

When an eligible node is right-clicked, the context menu gains a **Sweep** section. Depending on your selection, it can show **Distribute Variable Get**, **Distribute Selected Variable Gets**, and/or **Consolidate Selected Variable Gets**.

No command appears if you click a pin, the graph is unsupported, the clicked node isn't a supported pure Get, or neither operation is currently possible.

## Why selection may look different

Unreal can visually change the selection as a context menu opens. Sweep tracks the preceding selection to support batch operations when the clicked Get was already a member. Right-clicking a different, previously unselected Get intentionally targets only that Get.

## Runtime impact

Sweep is an **Editor-only** module. The refactoring happens to Blueprint graph authoring data; the plugin itself adds no runtime module, component or dependency to packaged games.

## Staying safe

Use the actual available menu item, check which Get will survive consolidation, review wires after refactoring, and compile the Blueprint. The source review explains how the integration works but is not a substitute for hands-on tests.

---

For engine integration details, [read Technical](TECHNICAL.md).
