# Node Placement and Readability — Design

**Sweep v1.0.0 · User guide**

## Where local Gets appear

Distribute creates each new Variable Get **to the left of its destination node**, approximately aligned to the consumer inputs. If one destination node has several inputs fed by the same source, Sweep creates **one Get for that destination**.

This is meant to reduce crossing wires without making the rest of the graph jump around.

## Handling nearby nodes

<!-- Final GIF: docs/assets/media/placement-demo.gif -->
<figure class="doc-media" data-kind="gif" data-media-id="placement-demo">
  <img src="../../assets/media-placeholder.png" alt="Sweep positions local Gets near consuming inputs while leaving existing graph nodes in place." loading="lazy">
  <figcaption>Sweep positions local Gets near consuming inputs while leaving existing graph nodes in place.<span class="media-capture-instructions"><strong>Capture instructions · GIF:</strong> Record a moderately crowded Blueprint graph inside a comment box; run Distribute and show a new local Get move to an available vertical position left of its destination without shifting existing nodes.</span></figcaption>
</figure>


Sweep checks the approximate size and position of other nodes before choosing a location. If a target spot would overlap, it tries alternate positions above and below.

Existing nodes are **not moved**. Comment boxes are treated as containers, so a new Get can appear inside an existing comment group instead of being pushed outside it.

## What to expect in dense graphs

Placement is a **best-effort estimate**, not a pixel-perfect layout. Complex node sizes, long pin lists, manually adjusted spacing or crowded graph areas may still require small adjustments after the operation.

## Practical approach

Before distributing across a dense area, leave some room to the left of consumers. Run Distribute, inspect the new local Gets and make minor layout changes where needed. Undo returns to the original node arrangement if the result doesn't help.

## Consolidation differs

Consolidate keeps the clicked survivor in its existing position and does not lay out the other nodes. It only transfers connections and removes redundant Gets.

---

For implementation, [read Technical](TECHNICAL.md).
