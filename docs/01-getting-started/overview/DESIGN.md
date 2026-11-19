# What Sweep Does — Design

**Sweep v1.0.0 · User workflow**

## Why Sweep exists

A perfectly valid Blueprint can become difficult to read when one Variable Get sends long wires across many unrelated nodes. Recreating those Gets by hand is repetitive, and manually consolidating copies can be equally tedious. **Sweep changes the graph’s presentation, not the intended value being read.**

Sweep gives you two complementary refactors: **Distribute** turns one heavily shared Get into local Gets beside its consumers; **Consolidate** connects several equivalent Gets to one chosen survivor.

## Choose an operation

| Your problem | Use | Expected result |
| --- | --- | --- |
| A shared variable wire stretches across the graph | **Distribute Variable Get** | A new Get near each destination node |
| Many repeated Gets make the graph cluttered | **Consolidate Selected Variable Gets** | Connections moved to the Get you right-click |
| Several sources each have long wires | **Distribute Selected Variable Gets** | Process eligible selected sources together |

## What's protected

Sweep is intentionally conservative. It works with **pure Blueprint Variable Get nodes**, not arbitrary pure expressions, Set nodes, execution wiring or other graph languages. Consolidation demands the same real variable reference and equivalent input context; matching visible names alone is insufficient.

Distribution can follow reroutes to find the actual consumers. Consolidation preserves existing reroutes and rewires them to the surviving Get.

## Where to find it

Open a Blueprint K2 graph, right-click an eligible Variable Get node, and look for the **Sweep** section in its context menu. Availability depends on the selection and the required operation, so an ineligible node may not show a Sweep command.

## Editor-only

Sweep adds no Actor, Component, asset format, gameplay system or packaged-game module. It updates Blueprint graph authoring data in the Unreal Editor.

**Continue:** [Install Sweep](../install/DESIGN.md) or [Distribute Variable Gets](../../02-operations/distribute/DESIGN.md).

---

For the implementation, [read Technical](TECHNICAL.md).
