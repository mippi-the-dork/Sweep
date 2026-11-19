# Troubleshooting and Recovery — Design

**Sweep v1.0.0 · User guide**

## Sweep is missing from the menu

<!-- Final IMAGE: docs/assets/media/troubleshoot-menu.png -->
<figure class="doc-media" data-kind="image" data-media-id="troubleshoot-menu">
  <img src="../../assets/media-placeholder.png" alt="The Sweep menu appears for eligible pure Variable Get node bodies rather than pin clicks or arbitrary nodes." loading="lazy">
  <figcaption>The Sweep menu appears for eligible pure Variable Get node bodies rather than pin clicks or arbitrary nodes.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture a side-by-side Blueprint example: context menu from eligible Get node body showing Sweep, and context menu from its output pin not showing Sweep.</span></figcaption>
</figure>


Confirm **Edit → Plugins → Sweep** is enabled and the editor restarted if necessary. Use a Blueprint K2 graph and right-click the **node body** of a pure Variable Get, not an output pin. Debugging mode can suppress the extension.

## Distribute doesn't appear

Make sure the Get leads to at least two terminal input pins. If a wire only goes through two reroute nodes to one calculation, Sweep still counts **one** consumer.

## Consolidate doesn't appear

Select at least two Gets from the same graph. The clicked Get must be selected. Check that every selected Get refers to the same underlying variable and equivalent target-object context.

## Only one node changed in my selection

If you clicked a Get **outside** your preselected group, Sweep intentionally falls back to a single-node operation. Also check whether the other selected Gets were eligible.

## A reroute vanished

Distribute removes reachable reroutes whose outputs become unused. A still-live reroute should be preserved. Consolidate doesn't explicitly clean reroutes.

## A Get overlaps nearby graph content

Placement is estimated and searches a limited number of alternative spots. It doesn't move existing nodes, and tightly packed graphs may need manual adjustment. Undo if you prefer the original.

## Blueprint compilation fails afterward

Undo once and recompile the original graph. Save a copy of both before and after states when possible. Report a minimal example with the variable type, context pins, graph type, reroutes and the exact compiler output.

## File a useful issue

Open [Sweep Issues](https://github.com/mippi-the-dork/Sweep/issues) with Sweep/Unreal versions, installation source, the operation, graph type, selection, variables/targets, before/after screenshots or GIF, and relevant Output Log or compiler diagnostics.

---

For engine integration details, [read Technical](TECHNICAL.md).
