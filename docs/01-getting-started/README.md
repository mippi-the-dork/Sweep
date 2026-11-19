# 01. Getting Started

Sweep makes Blueprint graph cleanup a deliberate, reversible editing operation. There is no special Sweep asset or editor window: work directly in a Blueprint K2 graph.

### Start with a known graph

Create a disposable Blueprint with one pure Get feeding three separate nodes. Right-click the **Get node body**, choose **Sweep → Distribute Variable Get**, then Undo. After that, try Consolidate with two equivalent Gets and right-click whichever Get you want to keep.

### What is a supported node?

A pure Blueprint Variable Get with a value output in a K2 graph. Sweep v1.0.0 does not operate on arbitrary pure functions, execution nodes, Set nodes, Materials or other graph systems.

### Save and safety

Sweep uses normal Unreal Editor transactions. Compile after a refactor and use Undo/Redo to inspect the changes. Use [Graph Integrity](../03-graph-integrity/README.md) for the specific rules about reroutes, context matching and placement.

## Topics in this section

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **What Sweep Does** | Plugin purpose, supported scope and the two operations | [Design](overview/DESIGN.md) | [Technical](overview/TECHNICAL.md) |
| **Installation and Compatibility** | Fab, releases, source and supported environment | [Design](install/DESIGN.md) | [Technical](install/TECHNICAL.md) |
| **First Refactor** | A complete Distribute and Consolidate example | [Design](first-use/DESIGN.md) | [Technical](first-use/TECHNICAL.md) |

**Reading guide:** Design explains what to do and what to expect; Technical explains the source implementation and boundaries.
