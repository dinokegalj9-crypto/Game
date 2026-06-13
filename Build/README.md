# Build/

**Tracked** packaging and platform build resources (see
[`Docs/ProjectStructure.md`](../Docs/ProjectStructure.md) §1, §5) — application icons,
splash screens, platform entitlements, signing config, and packaging scripts.

Per-platform subfolders (e.g. `Build/Windows/Resources/`). Generated build output
(`Build/Receipts/`, cooked/staged payloads) is git-ignored; only authored resources are
committed here. Cooked builds and staged packages are produced into `Saved/` and are never
committed.
