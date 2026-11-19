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

`Target A → Get Health` and `Target B → Get Health` are **not equivalent** even if the nodes look identical. The actual source object differs.

By contrast, two reads of `Self.CurrentHealth` in the same graph with matching context can be eligible for consolidation.

## When you're blocked

If the Consolidate command isn't offered, compare the source variable, target-object wires, pin defaults and actual graph membership. Do not disconnect context links merely to force a consolidation unless you intentionally want to change the Blueprint's logic.

## Safe practice

Validate the Blueprint after consolidation, especially in graphs that use target-object references or inherited variables. Sweep is conservative by design; it does not claim to prove every possible semantic behavior.

---

For implementation, [read Technical](TECHNICAL.md).
