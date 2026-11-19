# Sweep Documentation Media Inventory

Sweep already contains the real **Sweep-Hero.png**, **Sweep-Distribute.gif**, **Sweep-Consolidate.gif**, and **Sweep-MultiSelect.gif** in its repository `docs/assets/` directory, with published-site copies in `docs/assets/`. These are reused where they illustrate shipped behavior.

The **32 planned visual placements** use the supplied neutral placeholder until authentic screenshots, diagrams, and recordings can be produced. Every placeholder has two lines below it: a reader-facing caption explaining the eventual visual, and a separate **Capture instructions · Image/GIF** line explaining exactly what to create.

## Planned images and GIFs

| Documentation page | Media | Final asset |
| --- | --- | --- |
| [01-getting-started/overview/DESIGN.md](01-getting-started/overview/DESIGN.md) | IMAGE | `overview-graph.png` |
| [01-getting-started/overview/TECHNICAL.md](01-getting-started/overview/TECHNICAL.md) | IMAGE | `overview-components.png` |
| [01-getting-started/install/DESIGN.md](01-getting-started/install/DESIGN.md) | IMAGE | `install-folder.png` |
| [01-getting-started/first-use/DESIGN.md](01-getting-started/first-use/DESIGN.md) | GIF | `first-run.gif` |
| [02-operations/README.md](02-operations/README.md) | IMAGE | `operations-overview.png` |
| [02-operations/distribute/DESIGN.md](02-operations/distribute/DESIGN.md) | IMAGE | `distribute-before-after.png` |
| [02-operations/distribute/TECHNICAL.md](02-operations/distribute/TECHNICAL.md) | IMAGE | `distribute-traversal.png` |
| [02-operations/consolidate/DESIGN.md](02-operations/consolidate/DESIGN.md) | IMAGE | `consolidate-survivor.png` |
| [02-operations/consolidate/TECHNICAL.md](02-operations/consolidate/TECHNICAL.md) | IMAGE | `consolidate-transfer.png` |
| [02-operations/multi-selection/DESIGN.md](02-operations/multi-selection/DESIGN.md) | IMAGE | `selection-context.png` |
| [02-operations/multi-selection/TECHNICAL.md](02-operations/multi-selection/TECHNICAL.md) | IMAGE | `selection-snapshot.png` |
| [02-operations/decision-guide/DESIGN.md](02-operations/decision-guide/DESIGN.md) | IMAGE | `readability-choice.png` |
| [03-graph-integrity/README.md](03-graph-integrity/README.md) | IMAGE | `integrity-summary.png` |
| [03-graph-integrity/reroutes/DESIGN.md](03-graph-integrity/reroutes/DESIGN.md) | GIF | `reroutes-demo.gif` |
| [03-graph-integrity/reroutes/TECHNICAL.md](03-graph-integrity/reroutes/TECHNICAL.md) | IMAGE | `reroutes-algorithm.png` |
| [03-graph-integrity/equivalence/DESIGN.md](03-graph-integrity/equivalence/DESIGN.md) | IMAGE | `context-comparison.png` |
| [03-graph-integrity/equivalence/TECHNICAL.md](03-graph-integrity/equivalence/TECHNICAL.md) | IMAGE | `equivalence-checks.png` |
| [03-graph-integrity/placement/DESIGN.md](03-graph-integrity/placement/DESIGN.md) | GIF | `placement-demo.gif` |
| [03-graph-integrity/placement/TECHNICAL.md](03-graph-integrity/placement/TECHNICAL.md) | IMAGE | `placement-search.png` |
| [03-graph-integrity/undo-redo/DESIGN.md](03-graph-integrity/undo-redo/DESIGN.md) | GIF | `undo-redo.gif` |
| [03-graph-integrity/undo-redo/TECHNICAL.md](03-graph-integrity/undo-redo/TECHNICAL.md) | IMAGE | `transaction-boundary.png` |
| [04-implementation/README.md](04-implementation/README.md) | IMAGE | `architecture-intro.png` |
| [04-implementation/integration/DESIGN.md](04-implementation/integration/DESIGN.md) | IMAGE | `context-menu.png` |
| [04-implementation/integration/TECHNICAL.md](04-implementation/integration/TECHNICAL.md) | IMAGE | `editor-registration.png` |
| [04-implementation/algorithms/DESIGN.md](04-implementation/algorithms/DESIGN.md) | IMAGE | `algorithms-compare.png` |
| [04-implementation/algorithms/TECHNICAL.md](04-implementation/algorithms/TECHNICAL.md) | IMAGE | `data-ownership.png` |
| [05-support/README.md](05-support/README.md) | IMAGE | `support-flow.png` |
| [05-support/faq/DESIGN.md](05-support/faq/DESIGN.md) | IMAGE | `faq-different-target.png` |
| [05-support/troubleshooting/DESIGN.md](05-support/troubleshooting/DESIGN.md) | IMAGE | `troubleshoot-menu.png` |
| [05-support/troubleshooting/TECHNICAL.md](05-support/troubleshooting/TECHNICAL.md) | IMAGE | `triage-layers.png` |
| [05-support/updates/DESIGN.md](05-support/updates/DESIGN.md) | IMAGE | `update-folder.png` |
| [ROADMAP.md](ROADMAP.md) | IMAGE | `roadmap-history.png` |

## Replacing the placeholder

Read the precise instructions beneath the placeholder or in [media-slots.json](assets/media-slots.json). Capture the actual running Blueprint editor or create the described accurate technical diagram, save it to `docs/assets/media/<media-id>.png` or `.gif`, and update the figure's image URL. Keep its natural-language caption and alt description accurate. Do not introduce fabricated UI imagery.

The extra capture instructions are intentionally visible during documentation production. Once an asset is approved they may be removed from the published page.

[Documentation Audit](DOCUMENTATION_AUDIT.md) · [Verification Matrix](VERIFICATION_MATRIX.md)
