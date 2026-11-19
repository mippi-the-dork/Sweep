# Algorithms and Data Ownership — Technical

**Sweep v1.0.0 · Source-reviewed technical reference**

## Source organization

<!-- Final IMAGE: docs/assets/media/data-ownership.png -->
<figure class="doc-media" data-kind="image" data-media-id="data-ownership">
  <img src="../../assets/media-placeholder.png" alt="Sweep changes ordinary UEdGraph nodes and pin links rather than creating custom asset or runtime data." loading="lazy">
  <figcaption>Sweep changes ordinary UEdGraph nodes and pin links rather than creating custom asset or runtime data.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a source ownership diagram showing SweepModule.cpp menu and snapshots, SweepOperations.cpp graph edit/transactions, and UEdGraph/UK2Node_VariableGet stored in Blueprint package; Editor-only module.</span></figcaption>
</figure>


| File | Responsibility |
| --- | --- |
| `SweepModule.cpp` | Context-menu registration, selection snapshots and action gating |
| `SweepOperations.cpp` | K2 Variable Get analysis, context equivalence, graph rewiring, placement, reroute cleanup, transactions |
| `SweepOperations.h` | Internal operations declarations |
| `SweepModule.h` | Editor module and snapshot storage |
| `Sweep.Build.cs` | Runtime core plus editor-only module dependencies |
| `Sweep.uplugin` | Version, loading phase, editor-only type and Win64 platform target |

## Analysis structures

`FSweepAnalysis` owns `DestinationPins` and `ReachableKnots`. Terminal traversal prevents repeated visits by storing `UEdGraphPin*` outputs already examined. Distribution groups terminals by destination `UEdGraphNode`.

## Context copying

`SpawnMatchingGetter` uses `FEdGraphSchemaAction_K2NewNode::SpawnNode<UK2Node_VariableGet>`; it copies `VariableReference` and `SelfContextInfo`. `CopyInputContext` matches pins by name, copies defaults, and attempts context connections through schema calls.

## Lifecycle and ownership

The active Blueprint and graph use `Modify()` inside `FScopedTransaction`. New Get nodes belong to the existing `UEdGraph`. There is no separate Sweep-owned asset schema or serialization layer. `MarkBlueprintAsModified` and `NotifyGraphChanged` run after changes.

## Important implementation caveats

The placement heuristic ignores comment boxes as collision obstacles and falls back to desired location if no candidate is clear. Consolidation rolls back failed transfers **per source**, not across an entire multi-Get batch. These details belong in technical documentation because they set correct expectations for automated validation and new features.

---

For use cases and troubleshooting, [read Design](DESIGN.md).

**Source:** [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp) · [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
