# Updates and Support — Technical

**Sweep v1.0.0 · Source-reviewed technical reference**

## Version metadata

`Sweep.uplugin`: `Version: 7`, `VersionName: 1.0.0`, `EngineVersion: 5.8.0`, `Editor` module, `PostEngineInit` loading and `Win64` platform allowlist.

`Sweep.Build.cs` includes editor-only dependencies and must not be referenced from runtime targets.

## Compatibility discipline

The README currently lists UE 5.8.0 through 5.8.3 as its supported range. An engine descriptor version is a baseline, not evidence of testing across every patch and toolchain. Additional versions and platforms require explicit support verification.

## Upgrade safety

Close the editor, replace the complete plugin folder for prebuilt releases, and ensure the version-specific binaries and sources match. For source checkouts regenerate project files and rebuild the Editor target as appropriate.

## Reporting technical failures

Include exact engine/plugin versions, line-level log or Blueprint compiler error, graph class/schema, variable reference identity, incoming context pins, output connections, reroutes, selection state and actual result. A reproducible copy of the graph or a small throwaway project is more useful than an isolated screenshot of a menu.

## Documentation maintenance

For future code changes, update the affected Design and Technical page as a pair. Keep the [roadmap](../../ROADMAP.md) clearly marked where it describes unimplemented ideas. Record hands-on test evidence separately from source review.

---

For use cases and troubleshooting, [read Design](DESIGN.md).

**Source:** [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp) · [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
