# Equivalent Variable Gets — Technical

**Sweep v1.0.0 · Source-verified implementation**

## Comparison implementation

`AreEquivalentGetters` rejects graph mismatch, impure nodes and differing `VariableReference.IsSameReference`. It then calls `HaveEquivalentInputContext`.

That comparison first checks `SelfContextInfo`, collects every `EGPD_Input` pin on both nodes, and requires identical input-pin counts. For each source input, it finds a target input **by PinName**, then requires matching `DefaultValue`, `DefaultObject`, `DefaultTextValue.EqualTo`, and equivalent incoming links.

## Linked-context semantics

`HaveSameLinkedPins` checks link count and set membership of actual `UEdGraphPin*` references, not display names or node positions. Pin order is not used as an equivalence criterion.

## Selection-level contract

`CanConsolidate` requires at least two unique supported Gets and checks every selected supported Get against the anchor. A single mismatching supported Get makes the proposed batch ineligible.

## Limitation

These are exact implementation checks, not an engine-wide formal proof of purity or value identity. Provider-specific graph semantics outside supported K2 Variable Get behavior are not part of Sweep v1.0.0.

## Regression test scenarios

Different target pins, same variable names but different variable owner/reference, different pin defaults, differently ordered equivalent input lists, duplicate selection pointers and different Blueprint graphs should have explicit expected outcomes.

---

For expected workflows, [read Design](DESIGN.md).

**Source:** [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
