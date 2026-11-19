# 05. Support and Troubleshooting

The fastest way to diagnose Sweep is to identify **where the operation stopped**: was the command missing, the selection different than expected, a source ineligible, a connection rejected, or the generated Get simply not where you wanted it?

### Start with these checks

<!-- Final IMAGE: docs/assets/media/support-flow.png -->
<figure class="doc-media" data-kind="image" data-media-id="support-flow">
  <img src="../assets/media-placeholder.png" alt="Sweep issues can usually be narrowed to menu availability, eligibility, selection or graph reconnection." loading="lazy">
  <figcaption>Sweep issues can usually be narrowed to menu availability, eligibility, selection or graph reconnection.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Create a simple troubleshooting flowchart with plugin enabled, K2 pure Get node body, valid terminal count or equivalent selection, then connection and layout outcomes; link branches to the manual.</span></figcaption>
</figure>


| Symptom | Likely check |
| --- | --- |
| No Sweep menu | Enabled Editor plugin, Blueprint K2 graph, pure Get node body, not a pin |
| Distribute absent | At least two terminal consuming input pins |
| Consolidate absent | Two equivalent selected Gets; clicked survivor included |
| Only one Get processed | The clicked node was outside the old selection or other Gets were ineligible |
| Reroute disappeared | It became orphaned during Distribute |
| New Get overlaps | Bounded estimate; adjust manually or Undo |
| Compilation differs | Undo and capture exact before/after pin links and diagnostics |

### Reproduction details

When reporting an issue, include the Sweep and UE versions, graph type, source variable reference, connected object context, selected nodes and reroutes. Before/after screenshots are particularly useful. Reports go to [Sweep Issues](https://github.com/mippi-the-dork/Sweep/issues).

### Evidence

The [Verification Matrix](../VERIFICATION_MATRIX.md) separates source-review facts from Unreal Editor and website tests that have actually been run.

## Topics in this section

| Topic | Covers | Design | Technical |
| --- | --- | --- | --- |
| **Frequently Asked Questions** | Quick answers about commands, selection and reroutes | [Design](faq/DESIGN.md) | [Technical](faq/TECHNICAL.md) |
| **Troubleshooting and Recovery** | Resolve missing commands and unexpected graph changes | [Design](troubleshooting/DESIGN.md) | [Technical](troubleshooting/TECHNICAL.md) |
| **Updates and Support** | Version compatibility and reporting actionable issues | [Design](updates/DESIGN.md) | [Technical](updates/TECHNICAL.md) |

**Reading guide:** Design explains what to do and what to expect; Technical explains the source implementation and boundaries.
