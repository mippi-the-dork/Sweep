# 03. Graph Integrity

Sweep deliberately limits what it changes. Its purpose is to improve graph readability while preserving which variable is read and how that value reaches its consumers.

### Three safety rules

<!-- Final IMAGE: docs/assets/media/integrity-summary.png -->
<figure class="doc-media" data-kind="image" data-media-id="integrity-summary">
  <img src="../assets/media-placeholder.png" alt="Sweep validates variable identity, handles reroutes deliberately and uses Unreal K2 schema connections." loading="lazy">
  <figcaption>Sweep validates variable identity, handles reroutes deliberately and uses Unreal K2 schema connections.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create three labeled technical illustrations: identical VariableReference and context, reroute chains that remain or become unused, and K2 schema validating a new wire.</span></figcaption>
</figure>


**Actual variable identity matters.** Two `Health` Gets targeting different objects cannot safely be combined.

**Reroute behavior depends on the command.** Distribute may delete source-reachable reroutes whose outputs have become unused. Consolidate retains reroute topology while transferring source connections.

**The K2 schema owns connections.** Sweep requests connections through Unreal’s schema, allowing existing compatibility checks to accept or reject each link.

### How placement works

Generated Gets are placed near target inputs with a bounded overlap search. Existing nodes stay where they are. Dense graphs can still require manual spacing.

### Recovery

The entire edit is in an Unreal transaction, supporting Undo/Redo. Consolidation tries to restore links when an individual source transfer fails; that is not a whole-batch guarantee. Compile and test the resulting Blueprint before relying on it.

## Topics in this section

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **Reroute Chains** | Different cleanup behavior for distribution and consolidation | [Design](reroutes/DESIGN.md) | [Technical](reroutes/TECHNICAL.md) |
| **Equivalent Variable Gets** | Variable identity and target context safeguards | [Design](equivalence/DESIGN.md) | [Technical](equivalence/TECHNICAL.md) |
| **Node Placement and Readability** | How local Gets are positioned without moving other nodes | [Design](placement/DESIGN.md) | [Technical](placement/TECHNICAL.md) |
| **Transactions and Safe Reconnection** | Undo/Redo, schema validation and failure handling | [Design](undo-redo/DESIGN.md) | [Technical](undo-redo/TECHNICAL.md) |

**Reading guide:** Design explains what to do and what to expect; Technical explains the source implementation and boundaries.
