# Content/

Authored, in-editor game content. The full, explained hierarchy and the rules that govern
it live in [`Docs/ProjectStructure.md`](../Docs/ProjectStructure.md) §2.

This folder is committed via **Git LFS** (see `.gitattributes`). The category folders are
scaffolded with `.gitkeep` so *everything has a place from day one*. Two worked examples
show the repeatable patterns:

- `Regions/WeepingMoors/` — the self-contained **region** layout (see ProjectStructure §8).
- `Bosses/BellKeeper/` — the self-contained **boss** layout (see ProjectStructure §9).

Conventions (enforced by the asset validator, ProjectStructure §7):

- One correct folder per asset; **no duplication** — shared assets are referenced, not copied.
- `_`-prefixed folders (`_Shared`, `_Definitions`, `_DevMaps`) are shared/source-of-truth.
- `Developer/` and `Testing/` are **never** referenced by shippable content.
- Heavy assets are **soft-referenced** via the Asset Manager; nothing hard-loads meshes/audio.
