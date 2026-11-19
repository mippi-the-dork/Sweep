# Node Placement and Readability — Technical

**Sweep v1.0.0 · Source-verified implementation**

## Estimated destination positions

`ApproximateDestinationPinY` uses node `NodePosY`, an estimated header offset and the index of the destination's input pin. `DesiredGetterLocation` targets a horizontal offset of **220 graph units left** of the destination and uses the mean target-input Y for a multi-input destination.

## Collision checking

`GetEstimatedNodeSize` prefers stored `NodeWidth` / `NodeHeight`, falling back to K2 schema size estimates. `WouldOverlapGraph` tests neighboring graph nodes with **18 units of clearance**, ignoring the source and chosen destination and skipping `UEdGraphNode_Comment` containers.

## Search strategy

`FindAndApplyClearPlacement` tries the desired location, then vertical offsets in **56-unit steps**, alternating downward/upward for up to **eight attempts per direction**. If no candidate is clear, it uses the desired position anyway. The result is rounded and snapped to a **16-unit grid**.

## Boundaries

This is bounded, cheap heuristic placement, not Slate geometry sampling or full automatic graph layout. It does not move existing nodes. It does not guarantee no overlap when every candidate is occupied.

## Maintenance note

Changing constants can affect the visual result and may break users' screenshots; keep before/after graph fixtures to verify clear placement and comment-container behavior.

---

For expected workflows, [read Design](DESIGN.md).

**Source:** [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
