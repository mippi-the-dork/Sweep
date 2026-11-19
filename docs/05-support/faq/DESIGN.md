# Frequently Asked Questions — Design

**Sweep v1.0.0 · User guide**

## Where are Sweep's commands?

Right-click a **pure Variable Get node body** inside a Blueprint K2 graph. Look for the **Sweep** section if an operation is eligible. Sweep doesn't have a separate main toolbar window.

## Why is Distribute missing?

The source Get must feed at least **two distinct terminal consuming input pins**. Reroutes don't count as terminals. A single consumer remains a single consumer, even with several knots on the wire.

## Does Distribute create one Get per wire?

No. It groups terminal inputs by **destination node** and creates one local Get for each destination node. Several inputs on the same destination can share that Get.

## How do I choose the Get that survives consolidation?

Select equivalent Gets and **right-click the one you want to keep**. That Get stays where it is.

## Why can't I merge two Gets named Health?

<!-- Final IMAGE: docs/assets/media/faq-different-target.png -->
<figure class="doc-media" data-kind="image" data-media-id="faq-different-target">
  <img src="../../assets/media-placeholder.png" alt="Two Gets with identical visible names can read different target objects and must remain separate." loading="lazy">
  <figcaption>Two Gets with identical visible names can read different target objects and must remain separate.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture Target A -&gt; Get Health and Target B -&gt; Get Health in one Blueprint graph; make object target wires clearly visible and show they are not consolidation-equivalent.</span></figcaption>
</figure>


They may refer to different underlying variables or read from different target objects. Sweep checks actual `VariableReference`, pin defaults and linked context; the visible label isn't enough.

## What if Unreal deselects the other nodes when I right-click?

Sweep stores the most recent graph selection. If the clicked Get was selected, the multi-selection operation can use that snapshot. If it wasn't selected, Sweep uses that clicked Get alone.

## Will my reroute nodes disappear?

**During Distribute:** only reachable reroutes left with no outgoing connections are removed. **During Consolidate:** existing reroute topology remains.

## Does Sweep automatically lay out my whole Blueprint?

No. It places new Gets near their consumers while leaving existing nodes in place. Some minor manual spacing may still be helpful.

## Is Undo supported?

Yes. A single operation or eligible batch is wrapped in an Unreal Editor transaction. Verify your Blueprint after Undo/Redo.

## Does it change my packaged game?

No Sweep runtime code is packaged. The plugin intends to preserve Blueprint value semantics, but graph changes should still be compiled and verified before release.

---

For engine integration details, [read Technical](TECHNICAL.md).
