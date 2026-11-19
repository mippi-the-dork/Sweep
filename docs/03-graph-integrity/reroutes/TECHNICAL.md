# Reroute Chains — Technical

**Sweep v1.0.0 · Source-verified implementation**

## Directed traversal

`GatherTerminalDestinations` begins at the source `GetValuePin()` and follows `UK2Node_Knot` only when a linked pin is its `GetInputPin()`. It continues from `GetOutputPin()`, guarding visited outputs in `TSet<UEdGraphPin*>`. Non-knot input pins are unique terminal destinations.

## Reachability cleanup

`FSweepAnalysis::ReachableKnots` tracks reroutes encountered from the original Get. `RemoveOrphanedReachableKnots` repeatedly scans this set and destroys a knot **only if** its output exists and has no links. The repeated pass allows an upstream knot to become orphaned after its downstream knot is removed.

This cleanup is called from `SweepSingle` after attempted destination reconnections, **not** from consolidation.

## Consolidation wiring

`TransferGetterLinks` moves direct outgoing links and links to knot inputs onto the survivor output with `Schema->TryCreateConnection`. It does not traverse and collapse the knots.

## Tests worth running

Cover two-deep and branched reroutes, shared reroute input, still-live external connections, cycles and zero-link downstream knots. Verify both the terminal input link sets and which knot objects survive after each operation.

---

For expected workflows, [read Design](DESIGN.md).

**Source:** [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
