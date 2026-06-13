# Save System

**Owner types:** `UHCSaveSubsystem` (`UGameInstanceSubsystem`) + `UHCSaveGame`
(in `Source/HollowCrown/Save/`)
**Pillar:** Consequences — *if nothing persists, nothing matters.*

---

## Design Intent

Because the world remembers the player's choices, the save system is not an afterthought —
it is the durable record of every permanent consequence: dead bosses, unlocked regions,
corruption stage, settlement state, and progression. The vertical slice ships with a
working save/load.

## What Is Saved

| Domain | Source | Contents |
|--------|--------|----------|
| World state | `UHCWorldStateSubsystem` | Boss-defeated flags, unlocked regions, permanent choice flags. |
| Player | `AHCCharacter` components | Attributes, corruption value/stage, equipment, position, abilities. |
| Inventory | `UHCInventoryComponent` | Items, quantities, storage contents. |
| Survival | `UHCSurvivalComponent` | Current need values, diseases, injuries. |
| Settlement | `UHCSettlementSubsystem` | Placed buildings, prosperity, residents. |
| Meta | subsystem | Save version, timestamp, region, playtime. |

## Flow

```
Save:  UHCSaveSubsystem::SaveGame(slot)
        → gathers state from each subsystem/component into a UHCSaveGame
        → UGameplayStatics::SaveGameToSlot

Load:  UHCSaveSubsystem::LoadGame(slot)
        → UGameplayStatics::LoadGameFromSlot
        → distributes state back to subsystems/components
        → broadcasts OnGameLoaded so systems refresh visuals/AI
```

Each savable system exposes a `CaptureState`/`RestoreState` seam so the subsystem stays
the orchestrator and individual systems own their own serialization shape.

## Versioning

`UHCSaveGame` carries a `SaveVersion`. On load, older versions are migrated forward so
in-development saves don't hard-break across milestones. Unknown future versions are
rejected gracefully.

## Events (delegates)

- `OnGameSaved(FString Slot)`
- `OnGameLoaded(FString Slot)`
- `OnSaveError(EHCSaveError)`

## Design Notes

- The slice uses explicit save slots (campfire/rest as natural save points fits the tone).
  Autosave-on-major-event (boss death, region unlock) is a planned addition.
- Saving never blocks gameplay perceptibly; large captures can move to an async task if
  needed.
