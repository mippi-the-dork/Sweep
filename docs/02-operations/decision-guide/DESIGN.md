# Choosing the Right Refactor — Design

**Sweep v1.0.0 · User workflow**

## The visual tradeoff

Distribute and Consolidate are opposites in layout, but neither is universally better. **Distribute minimizes wire travel** and makes each local consumer easier to read. **Consolidate minimizes repeated Get nodes** but can introduce longer shared wiring.

## Before you act

| Question | Good choice |
| --- | --- |
| Do long wires cross several unrelated sections? | Distribute |
| Do many duplicate Gets make the graph feel crowded? | Consolidate |
| Are the values read from different target objects? | **Do not consolidate** |
| Do multiple inputs on one node share the same Get? | Distribute still creates **one local Get for that destination node** |
| Do you need to preserve custom reroute layouts exactly? | Consolidate preserves them; Distribute cleans up only orphaned reachable reroutes |

## Example: a combat graph

A `Get CurrentHealth` is read in several distant calculations. Distribute gives each calculation its own local Get. After reviewing the graph, you might consolidate a closely related cluster back to one Get. Sweep lets you choose the shape that makes the logic clearest for the team.

## What Sweep does not decide

Sweep does not measure readability, recommend an automatic layout, infer the architectural importance of a value, or rewrite logic as a function. It offers explicitly requested, narrowly scoped transformations.

## Safety checkpoint

After a substantial edit, review the target-object inputs, compile the Blueprint, and use the editor's Undo/Redo if you need to compare results. Consider running gameplay tests for behavior-sensitive graphs.

---

For source-level behavior, [read Technical](TECHNICAL.md).
