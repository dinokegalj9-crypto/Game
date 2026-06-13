# NPC System

**Owner types:** `AHCNPCBase` + `UHCScheduleComponent` (in `Source/HollowCrown/AI/`)
**Pillar:** Living World — *NPCs live independently.*

---

## Design Intent

NPCs should feel like residents of a real, troubled place, not quest dispensers. The
player should be able to learn a villager's routine, notice when they're missing, and feel
the village change as corruption spreads or a boss falls.

## NPC Identity

Every NPC is described by a `UHCNPCProfile` data asset:

- Name, age, occupation
- Personality, goals, fears
- Relationships (links to other NPC profiles)
- A schedule template

## Daily Life

NPCs **sleep, eat, work, and travel** on a schedule driven by `UHCScheduleComponent` and
the in-game clock. The schedule is a list of time-blocked tasks bound to world locations
(home, workplace, market, church). Behavior Trees execute the active task; the schedule
component decides *what* the current task is.

## Reactions

NPCs react to:

| Stimulus | Reaction |
|----------|----------|
| Weather | Seek shelter in rain/storm; alter routine in fog/Blood Moon. |
| Danger | Flee or hide from enemies; raise alarm. |
| Corruption | Unease → fear → fleeing, scaled to the player's corruption stage. |
| Player actions | Reputation-driven warmth or hostility; remember significant acts. |

Reaction state is computed from perception + world-state, not scripted per encounter.

## AI Stack

- **Behavior Trees** for task execution.
- **AI Perception** (sight/hearing) for danger and player detection.
- **EQS / Smart Objects** for choosing where to work, shelter, or flee.
- `UHCScheduleComponent` as the high-level "director" feeding the BT a current goal.

This shared stack also backs enemy, wildlife, boss, and (later) faction AI; only the
goals and BTs differ.

## Events (delegates)

- `OnTaskChanged(FName NewTask)`
- `OnFearStateChanged(EHCFearState)`
- `OnNPCDied()` / `OnNPCFled()`

## Integration

- **Settlement:** residents anchor their schedules to settlement buildings.
- **Corruption:** fear scaling reads the player's `UHCCorruptionComponent` stage.
- **Save:** NPC location, relationship, and fear state persist where relevant.
