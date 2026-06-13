# Automation/

CI/CD and automated quality gates (see [`Docs/ProjectStructure.md`](../Docs/ProjectStructure.md)
§7, §10).

Holds the build graph, automated test suites, and the asset-validation jobs that gate
merges and nightly cooks:

- **Pre-commit (fast):** naming/prefix lint, missing-reference scan, "no Developer refs".
- **Nightly (full):** full asset validation, cook of `dev`, and **functional tests** on the
  gym maps in `Content/Testing/`.
- **Performance gates:** Unreal Insights traces + budget checks (TechnicalArchitecture §9).

A red validation or a broken cook blocks promotion to `main`.
