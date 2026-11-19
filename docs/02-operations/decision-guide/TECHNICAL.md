# Choosing the Right Refactor — Technical

**Sweep v1.0.0 · C++ implementation reference**

## Two distinct transformation models

**Distribution:** analyze actual terminal pins, group by destination node, create matching Gets, reconnect each destination, prune only orphaned reachable knot nodes, and destroy the source only if disconnected.

**Consolidation:** validate identity and input-context equivalence, retain one selected anchor, transfer the other Gets' output connections through the K2 schema, retain reroutes, and delete a source only when all its links are successfully transferred.

## Determinism and interaction

The menu selection and clicked anchor are read from graph state. Source `UK2Node_VariableGet` references and `FGraphPanelSelectionSet` snapshots are weakly tracked; schema `TryCreateConnection` determines whether a connection is permitted.

## Semantic limits

This plugin is not static analysis or formal proof of equivalence. It checks the precise variable reference and input context for consolidation, but project-specific Blueprint behavior should be verified through compilation and tests. The code intentionally does not generalize into arbitrary pure function or impure node rewrites.

## Recommended validation

For both operations, construct graph fixtures with multiple consumers, reroutes, differing target contexts, shared destinations and schema rejection cases. Check exact pin link sets plus compile state, not merely node counts or screenshots.

---

For practical use, [read Design](DESIGN.md).

**Source:** [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp) · [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp)
