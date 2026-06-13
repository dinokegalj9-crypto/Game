# Survival System

**Owner type:** `UHCSurvivalComponent` (in `Source/HollowCrown/Survival/`)
**Pillar:** Living World (supporting). **Tone:** *light, not punishing.*

---

## Design Intent

Survival adds texture and motivates exploration, crafting, and the settlement loop —
without becoming a chore. It should make a warm campfire feel meaningful, not make the
player babysit meters. Decay is slow; consequences are gradual, never sudden death from a
neglected bar (except disease/injury left fully untreated).

## Tracked Needs

| Need | Behavior | Neglect effect |
|------|----------|----------------|
| **Food** | Slowly depletes; restored by eating. | Reduced stamina regen, then max-health penalty. |
| **Rest** | Depletes while active; restored by sleeping (tent/home). | Reduced stamina max; perception haze. |
| **Temperature** | Driven by weather + environment; campfires/clothing warm. | Cold slows stamina regen; severe cold damages. |
| **Disease** | Contracted from hazards (swamp water, corpses). | Stacking debuffs until cured. |
| **Injury** | From combat/falls; distinct from HP loss. | Lingering movement/attack penalties until treated. |

## Recovery

- **Food:** consumables from the inventory/crafting system.
- **Rest:** sleeping at a tent, home, or safe campfire advances time and restores rest.
- **Temperature:** campfires, shelter, and clothing.
- **Medicine:** crafted remedies cure disease and treat injury.
- **Campfires** are the survival hub: warmth, cooking, rest, and basic crafting in one.

## Events (delegates)

- `OnNeedChanged(EHCSurvivalNeed Need, float Value)`
- `OnNeedCritical(EHCSurvivalNeed Need)`
- `OnDiseaseContracted(...)` / `OnInjurySustained(...)`

## Integration

- **Combat:** survival penalties modify stamina/poise via `UHCAttributeComponent`.
- **Weather:** temperature reads the active weather profile.
- **Inventory/Crafting:** food and medicine are items/recipes.
- **Settlement:** homes and campfires are the primary recovery points.
- **Save:** current need values persist.
