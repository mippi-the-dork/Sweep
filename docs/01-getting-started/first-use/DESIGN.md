# First Refactor — Design

**Sweep v1.0.0 · User workflow**

## Try Sweep on a disposable Blueprint

Before applying it to a production graph, make a short test with one pure Variable Get connected to **three different consumer nodes**. Leave room for local nodes to appear beside the consumers.

1. Open the Blueprint's Event Graph or another supported K2 graph.
2. Right-click that shared Variable Get (not its pin).
3. Choose **Sweep → Distribute Variable Get**.
4. Observe one local Get near each destination node and the outgoing wires reconnecting.
5. Press **Ctrl+Z** once: the original arrangement should return.
6. Press **Ctrl+Y** if your editor key bindings support Redo, or use **Edit → Redo**.

## Now try Consolidate

Select two or more equivalent Gets that read the same underlying variable with equivalent target/context inputs. Right-click the specific Get you want to keep and choose **Sweep → Consolidate Selected Variable Gets**.

Only that right-clicked Get should survive; it keeps its location while the other selected Gets' consumers are connected to it. Try Undo again.

## Three rules to remember

- **Distribute:** requires at least two terminal consuming input pins. A reroute node is not a terminal consumer.
- **Consolidate:** requires two or more equivalent selected Gets; the right-clicked one must belong to the selection.
- **Different object targets:** even visually identical variable names cannot be consolidated when they read different object contexts.

## What to inspect afterward

Check the actual variable references, any target input links, reroute structure and successful Blueprint compilation. Sweep tries to preserve graph behavior, but every substantive Blueprint change should still be reviewed in the project's own context.

---

For the implementation, [read Technical](TECHNICAL.md).
