# Transactions and Safe Reconnection — Design

**Sweep v1.0.0 · User guide**

## One action, one Undo

Sweep groups a single refactor—or a supported multi-selection batch—inside one Unreal Editor transaction. Press **Undo** to restore the original node arrangement and **Redo** to reapply the change.

## What's included?

The graph changes are ordinary Blueprint editor data: new or removed Gets, wire reconnections, and (during distribution) genuinely unused reroutes. Sweep does not change the variable declaration itself or introduce a runtime component.

## When a connection cannot be made

Consolidate has a specific safeguard: when Unreal rejects transferring a connection, Sweep attempts to restore that particular source Get's original wires rather than leaving it half-consolidated.

This does **not** mean every possible batch can never partially change. Other selected Gets may have already been processed. After any unexpected failure, use Undo and report the actual Blueprint graph.

## Best verification sequence

1. Save or duplicate a representative Blueprint if it's critical.
2. Execute a Sweep operation.
3. Inspect its wire connections and context pins.
4. Compile the Blueprint.
5. Undo once and compare to the original.
6. Redo and compile again if needed.

## Important distinction

A successful command is not the same as guaranteed runtime equivalence in an unfamiliar project. Sweep is specifically designed to preserve the intended variable source and wire behavior, but Blueprint compilation and gameplay validation remain valuable.

---

For implementation, [read Technical](TECHNICAL.md).
