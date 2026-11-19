# Equivalent Variable Gets — Design

**Sweep v1.0.0 · User guide**

## Why visible names aren't enough

Two Blueprint nodes can both display `Health` while reading different objects. Consolidating them would change where the value comes from, so Sweep rejects that operation.

## What must match

Two Variable Gets are consolidation-compatible only when they:

- Are supported pure Variable Get nodes within the **same Blueprint graph**.
- Refer to the **same underlying variable**, not merely the same label.
- Have equivalent **self/context** information.
- Have matching input pins and input defaults, including object and text defaults.
- Use the **same incoming context connections** on corresponding pins.

## Example: same variable, different target

<!-- Final IMAGE: docs/assets/media/context-comparison.png -->
<figure class="doc-media" data-kind="image" data-media-id="context-comparison">
  <img src="../../assets/media-placeholder.png" alt="Variable Gets with the same visible name are not equivalent when their target-object context differs." loading="lazy">
  <figcaption>Variable Gets with the same visible name are not equivalent when their target-object context differs.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Capture two Blueprint Get Health nodes with clearly labeled Target A and Target B object wires, plus an eligible pair reading from the same target; mark the two different-target Gets Not equivalent.</span></figcaption>
</figure>


`Target A → Get Health` and `Target B → Get Health` are **not equivalent** even if the nodes look identical. The actual source object differs.

By contrast, two reads of `Self.CurrentHealth` in the same graph with matching context can be eligible for consolidation.

## When you're blocked

If the Consolidate command isn't offered, compare the source variable, target-object wires, pin defaults and actual graph membership. Do not disconnect context links merely to force a consolidation unless you intentionally want to change the Blueprint's logic.

## Safe practice

Validate the Blueprint after consolidation, especially in graphs that use target-object references or inherited variables. Sweep is conservative by design; it does not claim to prove every possible semantic behavior.

---

For implementation, [read Technical](TECHNICAL.md).
