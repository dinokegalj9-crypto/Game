# Tools/

Standalone, engine-external tooling (Python / C#): asset auditors, the naming/prefix
linter, importers, and content validators referenced by
[`Docs/ProjectStructure.md`](../Docs/ProjectStructure.md) §6–§7.

These run outside the editor (pre-commit hooks, developer utilities) and in CI. In-editor
utilities (Editor Utility Widgets/Blueprints) live under `Content/Developer/`, not here.

Planned tools:
- `naming_linter` — validates asset names/prefixes against ProjectStructure §3–§4.
- `reference_validator` — fails on `Developer/`/`Testing/` references in shippable content and on cross-region references.
- `redirector_check` / `duplicate_check` — fail on dangling redirectors and duplicate assets.
