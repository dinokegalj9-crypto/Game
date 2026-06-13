# CLAUDE.md — The Hollow Crown

Guidance for AI assistants and developers working in this repository.

## What this is

*The Hollow Crown* is a dark fantasy action RPG for **Unreal Engine 5.6** (C++ core +
Blueprint content). This repo currently holds the **foundation**: project skeleton, engine
config, design docs, and C++ scaffolding for the core systems. Binary content (maps,
meshes, materials) is authored in-editor and tracked via Git LFS.

## Where things live

- **Creative source of truth:** [`Docs/DesignBible.md`](Docs/DesignBible.md)
- **Technical source of truth:** [`Docs/Architecture.md`](Docs/Architecture.md) (overview)
  → [`Docs/TechnicalArchitecture.md`](Docs/TechnicalArchitecture.md) (full AAA spec)
- **What to build next:** [`Docs/Roadmap.md`](Docs/Roadmap.md)
- **Per-system design:** [`Docs/Systems/`](Docs/Systems)
- **Code:** [`Source/HollowCrown/`](Source/HollowCrown) (one folder per domain)

## Conventions (do not break)

- **Composition over inheritance.** Gameplay lives in `UActorComponent`s; actors assemble
  them. Global services are `UWorldSubsystem` / `UGameInstanceSubsystem`.
- **C++ for systems, Blueprint for content.** Expose `BlueprintCallable` / assignable
  delegates / `BlueprintImplementableEvent` seams rather than hardcoding content.
- **Data-driven.** New items, weapons, recipes, buildings, bosses, NPCs, and weather are
  data assets or data-table rows, not new C++ branches.
- **Event-driven decoupling.** Systems broadcast multicast delegates; the
  `UHCWorldStateSubsystem` is the hub for permanent world changes. Don't add hard
  cross-system references.
- **Naming:** `HC` prefix after the Unreal type prefix (`AHCCharacter`,
  `UHCCombatComponent`, `EHCAttackType`). Content uses `BP_`, `WBP_`, `DA_`, `L_`, `M_`,
  `T_`, `SK_`, `SM_`, `AM_`, `NS_`.

## Building

Requires a local UE 5.6 install (not available in the cloud session that scaffolded this):
generate project files from `HollowCrown.uproject`, then build the `HollowCrown` editor
target. First-compile fixups against the engine headers are expected and are part of
roadmap milestone M0.

## Before adding a system

Write or update its doc under `Docs/Systems/` and confirm it respects the five pillars in
the Design Bible. Every boss must satisfy the four death guarantees (Design Bible §7) —
see `AHCBossBase` for the reference wiring.
