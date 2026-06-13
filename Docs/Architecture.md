# Technical Architecture

This document describes how *The Hollow Crown*'s code is organized and the principles that
keep it scalable. It is the counterpart to the [Design Bible](DesignBible.md): the bible
says *what* and *why*; this says *how*.

---

## 1. Guiding Principles

1. **Composition over inheritance.** Gameplay behavior lives in `UActorComponent`s
   (combat, corruption, survival, inventory, attributes) so it can be attached to the
   player, NPCs, and enemies alike. Actors are thin assemblies of components.
2. **C++ for systems, Blueprint for content.** Core logic, data structures, and
   performance-sensitive code live in C++ with `BlueprintCallable`/`BlueprintImplementableEvent`
   seams. Designers build encounters, tune data assets, and wire UI in Blueprint.
3. **Data-driven.** Items, weapons, recipes, NPC profiles, buildings, bosses, and weather
   states are described by `UDataAsset`s / `UPrimaryDataAsset`s and `FTableRowBase` rows,
   not hardcoded.
4. **Event-driven decoupling.** Systems communicate through multicast delegates and a
   lightweight game-event channel rather than direct references. Corruption changes,
   boss deaths, and weather shifts broadcast; interested systems subscribe.
5. **Subsystems for global services.** World-spanning services (save, weather, settlement,
   world-state/flags) are `UGameInstanceSubsystem` or `UWorldSubsystem` — discoverable,
   lifetime-managed, and free of singletons.

---

## 2. Module Map

The runtime module `HollowCrown` is organized by domain:

| Folder | Responsibility | Key types |
|--------|----------------|-----------|
| `Core/` | Game framework glue | `AHCGameMode`, `UHCGameInstance`, `AHCGameState`, `UHCWorldStateSubsystem` |
| `Player/` | The Crownless | `AHCCharacter`, `AHCPlayerController` |
| `Stats/` | Shared vitals | `UHCAttributeComponent` (health, stamina, poise) |
| `Combat/` | Heavy melee combat | `UHCCombatComponent`, `FHCWeaponData`, `EHCAttackType` |
| `Corruption/` | Signature mechanic | `UHCCorruptionComponent`, `EHCCorruptionStage` |
| `Survival/` | Light survival | `UHCSurvivalComponent` |
| `Inventory/` | Items & crafting | `UHCInventoryComponent`, `UHCItemDefinition`, `FHCCraftingRecipe` |
| `AI/` | NPCs & schedules | `AHCNPCBase`, `UHCScheduleComponent` |
| `Settlement/` | Kingdom building | `UHCSettlementSubsystem`, `AHCBuilding` |
| `World/` | Dynamic weather | `UHCWeatherSubsystem`, `EHCWeatherType` |
| `Save/` | Persistence | `UHCSaveGame`, `UHCSaveSubsystem` |

Future content modules (e.g. `HollowCrownEditor`, region DLC) attach without touching the
core module.

---

## 3. Ownership & Composition

```
AHCCharacter (The Crownless)
├── UHCAttributeComponent   health / stamina / poise
├── UHCCombatComponent      attack state machine, weapon data, hit detection
├── UHCCorruptionComponent  corruption value, stage, ability unlocks
├── UHCSurvivalComponent    hunger / rest / temperature / disease
└── UHCInventoryComponent   items, equipment, crafting

AHCNPCBase (villagers, enemies)
├── UHCAttributeComponent   (enemies use poise for stagger)
├── UHCScheduleComponent    daily routine, reactions
└── UHCCombatComponent      (combatant NPCs only)
```

Components never assume which actor owns them; they query for sibling components through
`GetOwner()` and broadcast events outward.

---

## 4. Global Services (Subsystems)

- **`UHCWorldStateSubsystem`** (`UWorldSubsystem`) — the authoritative set of world flags:
  which bosses are dead, which regions are unlocked, which permanent choices were made.
  Everything that "changes the world" routes through here, and it is what the save system
  serializes.
- **`UHCWeatherSubsystem`** (`UWorldSubsystem`) — drives the active weather state and
  broadcasts transitions; combat, AI, and audio subscribe.
- **`UHCSettlementSubsystem`** (`UWorldSubsystem`) — tracks buildings, prosperity, and
  resident NPCs for the active settlement.
- **`UHCSaveSubsystem`** (`UGameInstanceSubsystem`) — orchestrates save/load by collecting
  state from the world-state, settlement, and player components into a `UHCSaveGame`.

---

## 5. Event Flow: "Defeat Boss → World Changes"

The boss-death pipeline ties the systems together and exercises the architecture:

```
Boss HP reaches 0
   └─ UHCCombatComponent broadcasts OnDeath
        └─ Boss actor reports its FHCBossId to UHCWorldStateSubsystem::ReportBossDefeated()
             ├─ WorldState sets bDead flag + unlocks linked regions   (Consequence)
             ├─ UHCCorruptionComponent::AddCorruption(fragmentAmount)  (Corruption)
             │     └─ may cross a stage threshold → OnCorruptionStageChanged
             │            ├─ player mesh/material updates              (Visual progression)
             │            └─ NPC schedule components re-evaluate fear  (Living world)
             ├─ ability granted to player                             (Progression)
             └─ WorldState broadcasts OnWorldStateChanged
                   └─ level streaming / weather / NPCs react          (World changes)
```

No system holds a hard reference to another; the world-state subsystem is the hub.

---

## 6. Data Assets (planned content types)

| Asset | Base | Describes |
|-------|------|-----------|
| `UHCItemDefinition` | `UPrimaryDataAsset` | A single item: id, name, icon, weight, stack size, type |
| `UHCWeaponData` *(asset wrapper)* | `UPrimaryDataAsset` | Weapon class, damage, stamina cost, moveset montage refs |
| `FHCCraftingRecipe` | `FTableRowBase` | Inputs → output, station required |
| `UHCNPCProfile` | `UPrimaryDataAsset` | Name, age, occupation, personality, goals, fears, schedule template |
| `UHCBuildingDefinition` | `UPrimaryDataAsset` | Cost, footprint, resource output, prerequisites |
| `UHCBossDefinition` | `UPrimaryDataAsset` | Boss id, granted ability, corruption gain, regions unlocked |
| `UHCWeatherProfile` | `UPrimaryDataAsset` | Fog/rain/wind params, gameplay modifiers, audio bank |

---

## 7. Naming Conventions

- C++ classes use the `HC` prefix after Unreal's type prefix: `AHCCharacter`,
  `UHCCombatComponent`, `EHCAttackType`, `FHCWeaponData`.
- Content assets use type prefixes: `BP_`, `WBP_` (widgets), `DA_` (data assets),
  `L_` (levels/maps), `M_`/`MI_` (materials), `T_` (textures), `SK_`/`SM_` (meshes),
  `AM_` (anim montages), `NS_` (Niagara).
- One public type per header where practical; implementation in the matching `.cpp`.

---

## 8. Build & Dependencies

The module depends on `Core`, `CoreUObject`, `Engine`, `InputCore`, `EnhancedInput`,
`GameplayTasks`, and `AIModule`. `GameplayAbilities` (GAS) is enabled at the project level
and is the intended long-term home for the ability/corruption-power layer; the current
component-based design is GAS-compatible and can migrate incrementally. See
[`Roadmap.md`](Roadmap.md) for sequencing.
