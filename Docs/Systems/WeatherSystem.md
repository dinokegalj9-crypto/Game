# Weather System

**Owner type:** `UHCWeatherSubsystem` (`UWorldSubsystem`, in `Source/HollowCrown/World/`)
**Pillar:** Living World. **Mood:** the world sits in permanent twilight; weather is how it
breathes.

---

## Design Intent

Weather is atmosphere first and mechanic second, but it must be *both*. Fog is the
signature state of the Weeping Moors; a Blood Moon should be a dreaded, rare event that
reshapes a night of play.

## Weather Types

| Type | Character | Gameplay effect |
|------|-----------|-----------------|
| Clear (twilight) | The weak-sun default. | Baseline. |
| Fog | Dense, signature. | Reduced visibility; enemies detect later; ambush risk. |
| Rain | Steady, cold. | Lower temperature; muffled audio; reduced torch range. |
| Thunderstorm | Violent. | Rain effects + lightning; NPCs shelter; loud cover for the player. |
| Strong Wind | Gusting. | Affects projectiles, fire/torch, ambient audio. |
| **Blood Moon** | Rare, dreaded. | Aggressive/empowered enemies; high monster attraction; altered spawns. Strongly amplified by player corruption. |

Each type is a `UHCWeatherProfile` data asset (visual params + gameplay modifiers + audio
bank).

## Transitions

The subsystem owns the active state and runs weighted, time-and-region-aware transitions
(e.g. the Moors favor fog; storms build rather than snap on). Transitions are smooth
blends of fog density, sky, post-process, and audio. Designers can force a state for
scripted moments.

## Events (delegates)

- `OnWeatherChanged(EHCWeatherType Old, EHCWeatherType New)`
- `OnBloodMoonStarted()` / `OnBloodMoonEnded()`

## Integration

- **Combat:** modifiers affect traction, torch range, visibility-based detection.
- **AI/NPC:** schedules react (shelter in storms; avoid Blood Moons).
- **Survival:** temperature reads the active profile.
- **Corruption:** high corruption increases Blood Moon frequency/severity and monster
  attraction.
- **Audio:** each profile swaps the ambient bank.
