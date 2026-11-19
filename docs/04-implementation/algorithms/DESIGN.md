# Algorithms and Data Ownership — Design

**Sweep v1.0.0 · User guide**

## What Sweep changes

Sweep modifies existing Blueprint graph content: `Variable Get` nodes and their links, plus some reroutes during distribution. It does **not** define a new variable type, insert a runtime function or store a custom Sweep asset in the Content Browser.

## Distribute at a glance

Sweep finds the real consumer input pins, groups them by destination node, spawns matching Gets, positions them near their consumers, reconnects the wires, then removes only disconnected original nodes and orphaned reroutes.

## Consolidate at a glance

Sweep checks that all selected Gets refer to the same variable and matching context, keeps the clicked Get and moves the other Gets' outgoing connections to it. Redundant Gets are deleted after successful transfers.

## Where layout decisions happen

The generated Gets are placed with a bounded search around estimated destination positions. Sweep never rearranges existing graph nodes automatically, so very dense graphs can still need manual polish.

## Where failures are handled

Connections go through Unreal's K2 graph schema. When an individual consolidation transfer fails, Sweep attempts to restore the source's original links. Changes occur within normal Undo/Redo transactions.

## Extending the plugin

For contributors, keep variable-reference equivalence, input-context checks, schema connections and transaction behavior separate from UI menu code. New node families would need their own safety analysis and tests.

---

For engine integration details, [read Technical](TECHNICAL.md).
