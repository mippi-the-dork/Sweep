# Maintaining Sweep Documentation

## Source of truth

Verify shipped behavior against Sweep's actual C++ code, descriptor and relevant tests. The README introduces the plugin but is not a substitute for the implementation. Clearly distinguish tested behavior from static source review.

## Keep Design and Technical separate

Each topic has a Design guide for exact user actions, outcomes, examples and common failures, and a Technical page for C++ classes/functions, eligibility, pin graph semantics, transactions and limitations. Avoid copying the same material into both.

## Adding or changing a feature

1. Inspect the changed code and native UE graph behavior.
2. Update the paired `DESIGN.md` and `TECHNICAL.md` and their category table, preserving the structure.
3. Add useful before/after screenshots or short GIFs when the feature involves visual interaction.
4. Verify relative links, search indexing, Design/Technical switching, source links, mobile width and accessibility.
5. Add native automated tests where feasible, or record manual tests with evidence in [Verification Matrix](VERIFICATION_MATRIX.md).
6. Update [Roadmap](ROADMAP.md) only when a direction has been decided; uncommitted candidates remain explicitly hypothetical.

## Images and GIFs

[Media Inventory](MEDIA_INVENTORY.md) lists all placeholder and real examples. New placeholders use the supplied neutral image, a public-facing explanatory caption and a distinct **Capture instructions · Image/GIF** line with specific creation guidance. Replace the placeholder with a real Unreal Editor capture at the designated path when available; do not fabricate screenshots.

## Publishing

The site is hosted from `main` → `/docs` through GitHub Pages. Configure it under repository **Settings → Pages** if needed, then verify the actual deployment at `https://mippi-the-dork.github.io/Sweep/`. The actual Pages setting and deployed browser behavior are separate from merging documentation source.

## Version maintenance

Update `site-manifest.json`, home, roadmap and relevant topic pages when a new Sweep release ships. For historical implementation citations, pin source links to a release tag or commit rather than a moving `main` branch.
