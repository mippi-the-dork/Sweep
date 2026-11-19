# Updates and Support — Design

**Sweep v1.0.0 · User guide**

## Current documented version

The repository currently identifies Sweep as **v1.0.0**, an editor-only plugin for **Unreal Engine 5.8.0–5.8.3** on **Win64**.

## Install or update

Use a compatible version from [GitHub Releases](https://github.com/mippi-the-dork/Sweep/releases), Fab if published for your engine, or the [Sweep source](https://github.com/mippi-the-dork/Sweep). Close the editor before replacing a precompiled plugin. Replace its whole directory rather than overlaying old and new files.

If using Git source, update the desired revision and rebuild the Editor target.

## Report bugs or suggest improvements

Use [GitHub Issues](https://github.com/mippi-the-dork/Sweep/issues). Specify the underlying graph readability or refactoring problem, supported/unsupported Get types, expected before/after wiring, and steps to reproduce.

## Contributing

The plugin is intentionally conservative. New refactoring operations should specify exact eligibility rules, what data may be changed, how connections are validated, and how failures and Undo are handled.

## Licensing

Refer to the repository [LICENSE](https://github.com/mippi-the-dork/Sweep/blob/main/LICENSE) for the applicable terms.

## Future plans

The [Roadmap](../../ROADMAP.md) distinguishes the current release from possible directions. No future release date or specific additional transformation is committed.

---

For engine integration details, [read Technical](TECHNICAL.md).
