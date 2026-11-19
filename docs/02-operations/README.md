# 02. Operations

Sweep provides **two complementary graph transformations**. Distribute minimizes long cross-graph wires; Consolidate reduces repeated Get nodes. Neither is automatically better for every Blueprint.

### Choose based on the graph

<!-- Final IMAGE: docs/assets/media/operations-overview.png -->
<figure class="doc-media" data-kind="image" data-media-id="operations-overview">
  <img src="../assets/media-placeholder.png" alt="Distribute favors local sources and Consolidate favors fewer repeated Get nodes." loading="lazy">
  <figcaption>Distribute favors local sources and Consolidate favors fewer repeated Get nodes.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create two side-by-side Blueprint before/after pairs using the same variable: Distribute one shared Get into three local Gets; Consolidate three equivalent Gets into one chosen survivor.</span></figcaption>
</figure>


If one variable value travels to distant sections, **Distribute**. If many local Gets repeat the same variable/context and make the graph crowded, **Consolidate**.

### Distribute eligibility

A pure Variable Get needs at least **two terminal consumer input pins**. Reroute nodes are followed, not counted as terminal consumers. One replacement Get is created for each destination **node**, even when several inputs on that node share the source.

### Consolidate eligibility

Select at least two equivalent Gets in the same graph, then right-click **the Get that should survive**. Sweep requires identical underlying variable references and equivalent context, not merely matching visual names.

### Batch operations

Eligible selected Gets can be distributed together in one Undo transaction. Sweep uses the selection recorded before Unreal opens the context menu, but only when the clicked Get belonged to that selection.

### Before editing production graphs

Review target-object context and wires, compile the Blueprint, and verify Undo/Redo. For detailed connection safety, see [Graph Integrity](../03-graph-integrity/README.md).

## Topics in this section

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **Distribute Variable Gets** | Replace shared long wires with local Gets | [Design](distribute/DESIGN.md) | [Technical](distribute/TECHNICAL.md) |
| **Consolidate Variable Gets** | Merge equivalent selected Gets into one chosen survivor | [Design](consolidate/DESIGN.md) | [Technical](consolidate/TECHNICAL.md) |
| **Batch Operations and Selection** | How selection snapshots support group operations | [Design](multi-selection/DESIGN.md) | [Technical](multi-selection/TECHNICAL.md) |
| **Choosing the Right Refactor** | Decide between local readability and shared wiring | [Design](decision-guide/DESIGN.md) | [Technical](decision-guide/TECHNICAL.md) |

**Reading guide:** Design explains what to do and what to expect; Technical explains the source implementation and boundaries.
