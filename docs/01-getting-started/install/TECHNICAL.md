# Installation and Compatibility — Technical

**Sweep v1.0.0 · C++ implementation reference**

## Descriptor facts

`Sweep.uplugin` declares `VersionName: 1.0.0`, `Version: 7`, `EngineVersion: 5.8.0`, `Editor` module type, `PostEngineInit` loading and `Win64` allowlist. The README describes testing/targeting UE 5.8.0–5.8.3; the descriptor itself names the 5.8.0 baseline.

The plugin contains C++ source, resources, packaging scripts and GIF documentation. `CanContainContent` is false, so it does not require a mounted content directory.

## Module dependencies

Build dependencies include `Core`, `CoreUObject`, `Engine`, plus private editor dependencies `Slate`, `SlateCore`, `UnrealEd`, `GraphEditor`, `BlueprintGraph`, `Kismet`.

The editor module registers its extender after normal editor initialization and skips startup in commandlets. This means a successful commandlet load alone does not prove that the context menu exists interactively.

## Troubleshooting by layer

A compiler error in an engine API is a **build compatibility** issue. A missing plugin in Edit → Plugins is an **installation/enablement** issue. A missing node context command may be **eligibility**, selection, graph type, pin right-click or debugging mode, not module failure.

## Support boundary

The source intentionally restricts itself to Blueprint K2 and editor APIs. Do not assume availability on non-Win64 platforms, non-5.8 engine versions or arbitrary graph editors.

---

For the practical workflow, [read Design](DESIGN.md).

**Source:** [SweepModule.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepModule.cpp) · [SweepOperations.cpp](https://github.com/mippi-the-dork/Sweep/blob/main/Source/Sweep/Private/SweepOperations.cpp)
