# Sweep Documentation Audit

**Baseline:** v1.0.0 · Source-reviewed against `Sweep.uplugin`, `README.md`, `SweepModule.cpp` and `SweepOperations.cpp`.  
**This document is a quality checklist**, not a report of completed Unreal Editor or website tests.

## What is covered

- Five practical documentation categories and **16 paired Design/Technical topics**.
- Precise supported operation steps and the clicked-anchor consolidation rule.
- Terminal consumer counting, one Get per destination node, reroute behavior, exact variable/context equivalence, placement heuristics and Undo.
- Installation and support boundaries for UE 5.8.0–5.8.3 on Win64.
- The plugin's genuine v1.0.0 hero and operation GIFs.
- Planned screenshots/diagrams/GIFs with real-reader captions and explicit capture directions.

## Remaining quality work

| Priority | Gap | Required improvement | Status |
| --- | --- | --- | --- |
| **P1** | Many specialized screenshots are not captured yet | Replace the supplied neutral placeholders with authentic UE Blueprint captures and readable diagrams | Awaiting captures |
| **P1** | Source review has not been independently exercised in UE | Run the [Verification Matrix](VERIFICATION_MATRIX.md) and record actual versions, results and evidence | Not run |
| **P1** | Site layout and search need live-browser verification | Check navigation, full-text search, images, GIFs, tables, responsive widths and keyboard usage | Not run |
| **P1** | Connection failure corner cases need concrete tests | Test preservation of original links, partial batch results and Undo/Redo | Not run |
| P2 | Technical source links point to moving `main` | Link code to a release tag/commit when version references are maintained | Pending |
| P2 | Accessibility beyond keyboard needs testing | Confirm contrast, focus visibility, alt text and mobile usability | Pending |
| P2 | Search relevance may need refinement | Try real queries such as “right click,” “different target,” “reroute,” and “one Undo” | Pending |

## Document-writing requirements

The **Design** guide should answer what a user does, what they see, when a command is available and how to recover. The paired **Technical** page should explain classes, algorithms, schema rules, ownership and implementation limits. Avoid copying the same README paragraph into both.

Images must teach one meaningful feature or decision. The supplied placeholder is deliberately neutral. The **first caption** is for readers and describes the future authentic visual; the **second line** identifies exactly what the screenshot or GIF should show. Replace that production instruction once the final media is available if it no longer belongs on the public-facing site.

## Safety claims

Do **not** describe Sweep as an automatic guarantee that every Blueprint remains semantically identical. The code deliberately conserves the variable reference and context and uses native schema connections; users still need to compile and test after edits. Do not describe consolidation's per-source restoration as unconditional all-or-nothing batch atomicity.

## Release readiness for documentation

Once media is captured, perform browser/mobile verification, run relevant Unreal test cases and publish actual results. Update this audit and the [Media Inventory](MEDIA_INVENTORY.md) when placeholders are replaced.

[Roadmap](ROADMAP.md) · [Media Inventory](MEDIA_INVENTORY.md) · [Verification Matrix](VERIFICATION_MATRIX.md)
