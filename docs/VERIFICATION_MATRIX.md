# Sweep v1.0.0 Verification Matrix

**Target:** UE 5.8.0–5.8.3, Win64 Editor. All test status entries below are **Not run** unless stated otherwise. Source inspection does not constitute an executed editor test.

## Environment to record

Record the exact UE patch, Sweep commit/release, project/Blueprint type, machine/platform, tester, date, Output Log location and any screenshot, video, automated test command or test report. Preserve failures and blockers alongside passing results.

## Editor behavior

| ID | Test | Expected result | Status |
| --- | --- | --- | --- |
| SWP-01 | Enable plugin, right-click pure Get in K2 graph | Sweep section appears when action eligible | Not run |
| SWP-02 | Right-click pin, non-K2 graph or during debugging | Sweep extender omitted | Not run |
| SWP-03 | Get with one terminal consumer through multiple reroutes | Distribute not offered | Not run |
| SWP-04 | Get feeding 2+ distinct terminal inputs on 2+ nodes | New local Gets near destinations | Not run |
| SWP-05 | Same Get feeds several inputs on one destination | Only one local Get for that destination node | Not run |
| SWP-06 | Distribute two-deep, branched and shared reroute chains | Terminal links preserved; only orphaned reachable knots removed | Not run |
| SWP-07 | Distribute with crowded nodes and comment box | Best-effort placement, existing nodes unchanged, comment boxes allowed | Not run |
| SWP-08 | Distribute several selected eligible Gets | Batch processed in one transaction | Not run |
| SWP-09 | Right-click a Get outside a multi-selection | Only clicked Get considered | Not run |
| SWP-10 | Mix selected Gets with unrelated node types | Unsupported types ignored for Distribute | Not run |
| SWP-11 | Consolidate 2+ equivalent Gets and selected anchor | Clicked Get survives, outgoing links transferred | Not run |
| SWP-12 | Consolidate with existing reroutes | Reroutes remain in their prior topology | Not run |
| SWP-13 | Same visible name but different variable references | Consolidation rejected | Not run |
| SWP-14 | Same variable with different linked object context | Consolidation rejected | Not run |
| SWP-15 | Different defaults, context pin count or graph | Consolidation rejected | Not run |
| SWP-16 | Schema rejection during one source transfer | Source links restored where possible, source not destroyed | Not run |
| SWP-17 | Multi-source consolidation where later source transfer fails | Earlier successful work is explicit and Undo restores batch | Not run |
| SWP-18 | Undo/Redo distribution, consolidation and batch | Original and new graph topology restored as expected | Not run |
| SWP-19 | Compile Blueprint before/after each successful operation | No unintended graph errors or variable-context changes | Not run |
| SWP-20 | Several open Blueprint editors and large selected graphs | Selection snapshot handles correct focused graph with acceptable editor cost | Not run |
| SWP-21 | Disable plugin and restart editor | Menu extender/ticker released, no stale UI | Not run |

## Documentation website

| ID | Test | Expected result | Status |
| --- | --- | --- | --- |
| DOC-01 | Navigate five categories and sixteen topic pairs | Correct links and Design/Technical switch | Not run |
| DOC-02 | Search title then an internal term (“terminal consumer”) | Title immediate, body result after index loads | Not run |
| DOC-03 | Keyboard search, arrow selection, Enter and Escape | Usable without mouse | Not run |
| DOC-04 | Desktop, tablet and 320–400px mobile viewport | Article, tables, sidebar and TOC remain usable | Not run |
| DOC-05 | Load Sweep hero and real Distribute/Consolidate/Multi-Select GIFs | Media renders within article width | Not run |
| DOC-06 | Load all placeholder figures and capture instructions | Type, caption, alt text and relative paths correct | Not run |
| DOC-07 | View roadmap | Released v1.0.0 distinct from uncommitted possibilities | Not run |
| DOC-08 | Back/forward, anchors and source links | Stable navigation without broken routes | Not run |

## Recording evidence

Use **Passed**, **Failed**, **Blocked** or **Not applicable** only after exercising the test. Include the exact editor or browser environment, reproduction steps, observed result and evidence. If a case fails, link a tracked issue rather than quietly dropping it.

The documentation does not assert that these tests already passed. Prefer native Unreal Automation Framework tests for repeatable graph invariants as plugin development continues.

[Documentation Audit](DOCUMENTATION_AUDIT.md) · [Operations](02-operations/README.md)
