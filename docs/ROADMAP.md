# Sweep Roadmap

**Current documented release:** Sweep **v1.0.0** · Unreal Engine 5.8.0–5.8.3 · Win64 · Editor-only.  
**Roadmap status:** No additional Sweep releases, delivery dates or future feature commitments were provided by the plugin author. The ideas below are **considerations for discussion**, not promised work.

## History

<!-- Final IMAGE: docs/assets/media/roadmap-history.png -->
<figure class="doc-media" data-kind="image" data-media-id="roadmap-history">
  <img src="assets/media-placeholder.png" alt="Sweep v1.0.0 establishes conservative Variable Get refactoring while later ideas remain uncommitted." loading="lazy">
  <figcaption>Sweep v1.0.0 establishes conservative Variable Get refactoring while later ideas remain uncommitted.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a timeline with v1.0.0 Released (Distribute, Consolidate, reroutes, batch Undo), then clearly distinct Future Research (not planned) for eligibility messages, additional safe node types and performance validation.</span></figcaption>
</figure>


### v1.0.0 — Variable Get refactoring (released)

Sweep launched with two focused operations:

| Capability | Released in v1.0.0 |
| --- | --- |
| **Distribute Variable Get** | Create local equivalent Gets near real consumers of a shared source |
| **Consolidate Selected Variable Gets** | Keep one selected anchor Get and transfer outgoing links from equivalent Gets |
| **Reroute awareness** | Follow knots for distribution, remove truly unused reachable knots, preserve topology in consolidation |
| **Multi-selection** | Selected source distribution, pre-menu selection snapshots and transactional Undo/Redo |
| **Context safety** | Same variable reference and equivalent input-context checks |
| **Placement** | Approximate destination-based positioning with bounded overlap avoidance |
| **Editor integration** | Native Blueprint K2 node context menu; no packaged runtime module |

This history is grounded in the current v1.0.0 README and source. It does not imply unspecified earlier public releases.

## Future considerations — not committed

Sweep should remain useful for one problem: **making Blueprint graphs easier to read without silently changing their meaning**. Potential areas to investigate, if there is user demand, include:

| Possible direction | Problem worth researching | Gate before it becomes a plan |
| --- | --- | --- |
| **Broader safe refactors** | Whether additional pure node families could be distributed or consolidated | Type-specific identity and context safety, precise graph semantics and regression tests |
| **More authoring control** | Cases where the automatic destination placement needs manual guidance | Proven usability improvement without turning Sweep into a full layout editor |
| **Improved diagnostics** | Users may not know why a given selection is ineligible | Actionable explanations for eligibility and failure paths |
| **Validation and performance** | Large graphs, selection snapshots and complex reroutes deserve coverage | Measured UE editor tests and reproducible graph fixtures |

**No versions are assigned to these ideas.** They are research topics only; none should appear as an existing command or shipped capability.

## Criteria for a future release

Any new transformation should document:

1. Exactly which Blueprint graph/node types and pin contexts are supported.
2. How variable/reference identity and connected target context are preserved.
3. How wires, reroutes, existing nodes and graph layout are affected.
4. What happens on an Unreal K2 schema failure, and whether rollback is per source or whole batch.
5. Native Unreal Undo/Redo and automated before/after link-integrity tests.
6. New Design and Technical documentation with authentic screenshots/GIFs.

## What is explicitly outside the current v1.0.0 scope

General graph auto-layout, arbitrary pure function rewrites, execution-pin refactoring, Material/Niagara/MetaSound/Behavior Tree graphs, and packaged runtime behavior are **not currently supported**. Listing them here does not mean they are scheduled.

[Current operations](02-operations/README.md) · [Graph safety](03-graph-integrity/README.md) · [Verification matrix](VERIFICATION_MATRIX.md)
