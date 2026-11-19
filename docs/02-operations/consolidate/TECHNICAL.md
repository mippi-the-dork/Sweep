# Consolidate Variable Gets — Technical

**Sweep v1.0.0 · C++ implementation reference**

## Conservative eligibility

`CanConsolidate` checks that the clicked anchor is supported, at least two input Gets are provided, all unique supported selected Gets pass `AreEquivalentGetters`, and the clicked anchor is in that set.

`AreEquivalentGetters` requires both Gets in the same graph, both pure, matching `VariableReference.IsSameReference`, and `HaveEquivalentInputContext`, which compares `SelfContextInfo`, the number and names of input pins, default value, default UObject, default text, and the **exact same linked input-pin references** (order-insensitive).

## Surviving anchor

`ConsolidateMany` obtains the graph, K2 schema and Blueprint, starts a single `FScopedTransaction`, calls `Modify` on Blueprint, graph and anchor, then iterates the other eligible Gets.

`TransferGetterLinks` snapshots each source's value-output links, breaks individual source links and uses `Schema->TryCreateConnection(AnchorValuePin, LinkedPin)`. A redundant source is destroyed only after all of its links were transferred.

## Failure rollback per source

If a schema connection unexpectedly fails, the operation tries to restore that source's original link and any earlier links already transferred from that source before returning false. Other source Gets may already have been consolidated during the same batch; this is **per-source rollback**, not an absolute whole-batch rollback guarantee.

## Reroute guarantee

No explicit reroute cleanup is called from consolidation; existing outgoing reroute paths connect to the surviving Get. Compare the before/after graph and Blueprint compilation when maintaining this algorithm.

---

For practical use, [read Design](DESIGN.md).

**Source:** [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp) · [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp)
