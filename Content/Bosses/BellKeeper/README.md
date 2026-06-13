# Bosses/BellKeeper/ — boss folder template

The reference layout for a **fully self-contained** major boss. Copy this folder shape for
every boss; the workflow is [`Docs/ProjectStructure.md`](../../../Docs/ProjectStructure.md) §9.

| Folder | Holds |
|--------|-------|
| `Blueprints/` | `BP_BellKeeper` (derives `BP_BossBase` → `AHCBossBase`), phase/component BPs |
| `Animations/` | `A_`/`AM_` attacks & phase transitions, `ABP_BellKeeper` |
| `Abilities/` | `GA_`/`GE_`/`GC_` + `AS_BellKeeper_Phase1/2` (per-phase ability sets) |
| `Audio/` | `SFX_BellKeeper_*`, `MUS_BellKeeper` phase states |
| `VFX/` | `NS_BellKeeper_*` telegraphs & signature effects |
| `Data/` | `DA_Boss_BellKeeper` — phases + the four death guarantees + rewards |
| `UI/` | boss-specific `WBP_` overrides |
| `Arena/` | `AHCBossArena` setup (bounds, fog wall, camera, music state) |
| `Cutscenes/` | `LS_BellKeeper_Intro/_PhaseX/_Death` |

A boss is added with **zero new engineering**: author `DA_Boss_BellKeeper` first, then
StateTrees, montages, and this folder. The death pipeline (grant ability set + corruption,
set world flag, unlock regions, broadcast world change) is handled by the framework — the
boss only supplies data. See [`Systems/CombatSystem.md`](../../../Docs/Systems/CombatSystem.md)
and the Design Bible's four death guarantees (§7).
