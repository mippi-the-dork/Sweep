# Installation and Compatibility — Design

**Sweep v1.0.0 · User workflow**

## Supported environment

Sweep v1.0.0 targets **Unreal Engine 5.8.0–5.8.3**, **Windows 64-bit**, as an **Editor** plugin. Use a release built for your particular engine version, or compile from source.

## Install from a release

<!-- Final IMAGE: docs/assets/media/install-folder.png -->
<figure class="doc-media" data-kind="image" data-media-id="install-folder">
  <img src="../../assets/media-placeholder.png" alt="A correct project installation places Sweep.uplugin directly inside the Sweep plugin directory." loading="lazy">
  <figcaption>A correct project installation places Sweep.uplugin directly inside the Sweep plugin directory.<span class="media-capture-instructions"><strong>Capture instructions · Image:</strong> Show File Explorer at YourProject/Plugins/Sweep, with Sweep.uplugin, Source, Config, Resources and Doc visible; include the address bar proving no extra nested Sweep folder.</span></figcaption>
</figure>


1. Close the Unreal Editor.
2. Open the [Sweep Releases](https://github.com/mippi-the-dork/Sweep/releases) page and select a matching ZIP if one is published for your engine.
3. Extract the entire **Sweep** directory into `YourProject/Plugins/`.
4. Confirm `YourProject/Plugins/Sweep/Sweep.uplugin` exists. Avoid nesting another `Sweep` directory inside it.
5. Launch the project. Under **Edit → Plugins**, search for Sweep and enable it if needed.
6. Restart the Editor if prompted; open a Blueprint and right-click a supported Variable Get.

### Install through Fab

If Sweep is available in your Fab library, install it to a compatible engine version through Epic Games Launcher. Enable it in the project Plugins panel if required. Fab availability should be checked at the time of installation rather than assumed.

## Build from GitHub source

Clone [Sweep](https://github.com/mippi-the-dork/Sweep) into `YourProject/Plugins/Sweep`. Install the Unreal-compatible Visual Studio C++ toolchain, generate project files where needed, and build your **Editor** target. Do not build Sweep as a runtime game module.

## Update safely

Close Unreal, replace the **entire** plugin folder for a precompiled release, then restart. With a source clone, pull the desired revision and rebuild. Avoid mixing binaries, source and resources from different versions.

## First troubleshooting checks

If a command does not appear, confirm the plugin is enabled, the graph is a Blueprint K2 graph, the clicked node is a pure Variable Get, and its operation is eligible. The menu is contextual; Sweep does **not** add a global main-toolbar window.

---

For the implementation, [read Technical](TECHNICAL.md).
