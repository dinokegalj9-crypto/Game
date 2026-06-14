# Settlement System

**Owner type:** `UHCSettlementSubsystem` (`UWorldSubsystem`) + `AHCBuilding`
(in `Source/HollowCrown/Settlement/`)
**Pillar:** Kingdom Building — *the player builds a civilization, not a house.*

> The *living* side of settlements — population dynamics, recruitment of people (not units),
> emergent events, death & grief, prosperity/decline, and attachment — is designed in
> [**LivingWorld.md**](LivingWorld.md). The settlement-as-home/legacy design — founding,
> progression tiers, buildings-need-people, specialists, morale, crime, internal politics &
> faith, world reaction, the corruption mirror, and the legacy chronicle — is
> [**SettlementDesign.md**](SettlementDesign.md). This page covers the building/economy structure.

---

## Design Intent

The settlement is the player's stake in a dying world: a place that can grow into
something hopeful or rot like everything else. It should feel earned, fragile, and
responsive — NPCs arrive because the player made somewhere worth coming to.

## Progression

**Start:** Campfire, Tent, Storage.

**Unlocks over time:** Homes, Blacksmiths, Churches, Walls, Towers, Markets, Barracks,
Libraries, Castle structures.

Each building is a `UHCBuildingDefinition` data asset (cost, footprint, resource output,
prerequisites). Placement spawns an `AHCBuilding`; the subsystem tracks all placed
buildings and aggregates their effects.

## Prosperity & Collapse

The settlement has a **prosperity** score derived from population, building quality,
defenses, and resource balance. High prosperity attracts NPCs and unlocks higher-tier
buildings; neglect, raids, disease, or a high-corruption player can drive **collapse**
(NPCs leave, buildings fall into disrepair). Prosperity is part of world-state and is
saved.

## What Buildings Do

| Building | Effect |
|----------|--------|
| Campfire | Rest/cook; survival recovery; basic crafting station. |
| Storage | Shared item storage. |
| Home | Houses a resident NPC; raises population cap. |
| Blacksmith | Weapon/armor crafting & upgrades; attracts a smith NPC. |
| Church | Morale; corruption-related services. |
| Walls / Towers | Defense rating; reduce raid losses. |
| Market | Trade; resource conversion. |
| Barracks | Houses recruits / guards. |
| Library | Lore, research, unlocks. |
| Castle | Capstone; major prosperity and identity. |

## Integration

- **NPCs:** the subsystem requests residents from the NPC system as homes open; NPCs'
  schedules anchor to settlement buildings.
- **Resources:** buildings feed the inventory/crafting economy.
- **Corruption:** a highly corrupted player suppresses prosperity and recruitment.
- **Save:** building list, placement, and prosperity serialize through `UHCSaveSubsystem`.

## Events (delegates)

- `OnBuildingPlaced(AHCBuilding*)` / `OnBuildingRemoved(...)`
- `OnProsperityChanged(int32 Old, int32 New)`
- `OnSettlementCollapsed()`
