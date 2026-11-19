# 04. Implementation

Sweep is a small, native Unreal Editor module rather than a separate graph engine. Its visible interface is a contextual menu; the underlying implementation edits standard Blueprint graph data.

### Two C++ responsibilities

<!-- Final IMAGE: docs/assets/media/architecture-intro.png -->
<figure class="doc-media" data-kind="image" data-media-id="architecture-intro">
  <img src="../assets/media-placeholder.png" alt="Sweep separates user-facing menu integration from the code that edits Blueprint graphs." loading="lazy">
  <figcaption>Sweep separates user-facing menu integration from the code that edits Blueprint graphs.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Diagram FSweepModule (context menus and selection snapshots) beside SweepOperations (analysis, equivalence, placement, rewiring), both connected to Unreal Blueprint graph and K2 schema.</span></figcaption>
</figure>


**`FSweepModule`** registers context-menu actions, snapshots selected nodes, and determines which command can be offered. **`SweepOperations`** validates the graph, traces terminal consumers, checks equivalence and uses Unreal’s schema to modify nodes and links.

### Data ownership

Variable Get nodes and their connections remain in the original `UEdGraph` and Blueprint package. Sweep creates no custom graph asset and no packaged runtime system.

### Constraints worth knowing

Selection snapshots are refreshed by a core ticker. Placement uses estimated graph dimensions and a bounded search, not live Slate geometry. Consolidation has per-source rollback on schema failure, not unconditional atomicity across an entire selected group.

### For contributors

Review the paired Technical pages and the exact source when extending Sweep. Do not expand eligibility to other node families without explicit equivalence, wiring, Undo and regression-test guarantees.

## Topics in this section

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **Editor Integration** | Native graph-context menus and selection snapshots | [Design](integration/DESIGN.md) | [Technical](integration/TECHNICAL.md) |
| **Algorithms and Data Ownership** | Graph traversal, node creation, links, transactions and source map | [Design](algorithms/DESIGN.md) | [Technical](algorithms/TECHNICAL.md) |

**Reading guide:** Design explains what to do and what to expect; Technical explains the source implementation and boundaries.
