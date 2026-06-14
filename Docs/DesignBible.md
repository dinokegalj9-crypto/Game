# The Hollow Crown — Design Bible

> *"The world is not dying. It is becoming something else."*

This is the canonical creative document for the project. When a design question arises,
this document is the source of truth. It captures the **why** behind every system; the
technical documents capture the **how**.

---

## 1. Vision

A next-generation dark fantasy action RPG combining open-world exploration, light
survival, kingdom building, meaningful and permanent choices, deep environmental lore,
and unforgettable boss encounters.

We are explicitly **not** making:

- Another generic survival game.
- Another Souls clone.

We **are** making a living world that feels **ancient, mysterious, tragic, and
believable**. Players should constantly ask:

- *What happened here?*
- *Who built this?*
- *Why does this place exist?*
- *Should this creature really die?*

Three promises guide every decision:

- **Every location tells a story.**
- **Every boss feels like a fallen legend.**
- **Every choice leaves permanent consequences.**

---

## 2. Setting

A fictional kingdom inspired by medieval England, Celtic mythology, gothic horror,
ancient folklore, and cosmic dark fantasy. This is **not** historical England. It is a
kingdom that never escaped the Dark Age — trapped beneath a dying sky in permanent
twilight.

- The sun is weak. The stars are wrong.
- The forests are alive.
- The churches are corrupt.
- The dead do not remain dead.
- Reality itself is slowly unraveling.

### The Hollow Crown (central artifact)

Thousands of years before recorded history, a forgotten, non-human civilization made (or
found) an artifact: a crown. The civilization vanished; the crown remained. Centuries
later a king unearthed it beneath an ancient ruin and, believing it a divine gift, wore
it. The moment it touched his skin, the sky darkened, the seasons broke, animals mutated,
people dreamed of impossible places, and the kingdom began to rot.

The twelve greatest rulers, nobles, generals, and saints were corrupted by **fragments**
of the Crown and became immortal monsters. The kingdom collapsed, regions became cursed,
and the King vanished. Only the fragments remain — and the player will collect them.

### The Player — "The Crownless"

No family, no past, no allegiance, no memories. The player awakens in a swamp at the edge
of the kingdom with no explanation and no destiny. They are **not** a chosen one. Their
story emerges through exploration; they become important only through their choices.

---

## 3. Core Pillars

| # | Pillar | Meaning |
|---|--------|---------|
| 1 | **World Exploration** | Reward curiosity. No excessive markers, no hand-holding, no checklists. Locations are discovered naturally. |
| 2 | **Meaningful Progression** | Every upgrade is impactful. Every boss changes gameplay. Every power has advantages *and* drawbacks. |
| 3 | **Kingdom Building** | The player builds not a house but a civilization. |
| 4 | **Living World** | NPCs live independently, creatures migrate, weather matters, regions evolve. |
| 5 | **Consequences** | Actions permanently affect the world. Nothing feels disposable. |

These pillars are the tie-breaker for any design dispute. A feature that violates a
pillar is cut or redesigned.

---

## 4. Core Gameplay Loop

```
Explore → Discover → Fight → Gather → Craft → Build → Recruit →
Expand Settlement → Defeat Boss → World Changes → Unlock New Region → (repeat)
```

The loop is regional. Each region culminates in a boss whose death reshapes the world,
grants a new ability, advances corruption, and opens the path onward.

The narrative engagement layer — how the world's problems become emotionally powerful,
choice-driven, consequential stories (never tasks or filler) — is designed in
[`Systems/QuestDesign.md`](Systems/QuestDesign.md), built atop the simulation in
[`Systems/LivingWorld.md`](Systems/LivingWorld.md).

---

## 5. Visual Direction

**Style: Stylized Dark Realism.** Beautiful but achievable. Avoid cartoon, anime, and
photorealism.

**References:** Bloodborne, Elden Ring, Lies of P, Kingdom Come: Deliverance, A Plague
Tale.

**Visual features:** dense fog, volumetric lighting, strong silhouettes, ancient stone
architecture, ruined cathedrals, dark forests, massive castles, weathered materials,
natural color grading.

**Palette:** black, dark grey, dark green, deep blue, muted gold, copper, silver.
Bright colors are rare and meaningful.

> The full visual identity — color psychology, lighting, architecture, character/enemy/boss
> design, materials, VFX, UI, typography, and per-region mood boards — is the
> [**Art Bible**](ArtBible.md). It is the binding source of truth for all art.

---

## 6. World Regions

| # | Region | Identity | Primary Boss |
|---|--------|----------|--------------|
| 1 | **The Weeping Moors** | Starting wetlands: rotting villages, ancient graveyards, abandoned churches, flooded roads, constant fog. | The Bell Keeper |
| 2 | **Blackwood** | A living forest where trees shift and paths change; creatures stalk travelers. | The Black Stag |
| 3 | **Ashbourne** | A city under endless ash; masked citizens; no one remembers the ash's origin. | Saint Eleanor |
| 4 | **The Drowned Kingdom** | A half-submerged civilization of flooded cathedrals and sunken castles. | The Drowned King |
| 5 | **The Silent Cathedral** | A holy city where silence is law and sound attracts horrors. | The Choir of Thorns |
| 6 | **The Hollow Capital** | The final region; birthplace of the corruption; home of the final king. | (The final king) |

---

## 7. Boss Design Philosophy

Every boss must be **visually unique, mechanically unique, emotionally memorable, and
lore-significant**. A boss is a tragic story, not merely an enemy. On death, each boss:

1. **Changes the world** (permanent environmental/world-state shift).
2. **Unlocks a new ability.**
3. **Advances the corruption system.**
4. **Unlocks new areas.**

A boss is only "done" when all four are wired up. See
[`Systems/CombatSystem.md`](Systems/CombatSystem.md) and
[`Systems/CorruptionSystem.md`](Systems/CorruptionSystem.md).

The full roster — **the Twelve Lords**, each a fallen human tragedy with its own visual,
narrative, mechanical, arena, audio, and emotional identity — is the
[**Boss Bible**](BossBible.md).

---

## 8. Corruption System (signature mechanic)

Every major boss grants power **and** increases corruption.

- **Benefits:** new abilities, enhanced combat, special transformations, new dialogue.
- **Drawbacks:** NPC fear, physical mutations, altered endings, increased monster
  attraction.

**Visual progression**

| Stage | State |
|-------|-------|
| 1 | Normal human |
| 2 | Darkened eyes |
| 3 | Visible veins |
| 4 | Monstrous traits |
| 5 | Almost inhuman |

Corruption is the spine of meaningful progression (Pillar 2) and consequence (Pillar 5).
Full mechanics in [`Systems/CorruptionSystem.md`](Systems/CorruptionSystem.md).

---

## 9. Settlement System

Players begin with a **campfire, tent, and storage**, and over time unlock homes,
blacksmiths, churches, walls, towers, markets, barracks, libraries, and castle
structures. A settlement attracts NPCs, generates resources, and can **prosper or
collapse**.

The full settlement-as-legacy design — founding, the progression tiers, buildings that need
people, specialists, morale, crime, internal politics and faith, world reaction, the
corruption mirror, and the legacy chronicle ("I built this") — is in
[`Systems/SettlementDesign.md`](Systems/SettlementDesign.md); the implementation contract is
[`Systems/SettlementSystem.md`](Systems/SettlementSystem.md).

---

## 10. NPC System

Every NPC has a name, age, occupation, schedule, relationships, personality, goals, and
fears. NPCs sleep, eat, work, travel, and react to weather, danger, corruption, and the
player's actions.

The full **living-world** design — the simulation philosophy ("the world exists when I am
not here"), the needs/emergence engine, NPC memory, relationships, permanent death and
grief, settlement evolution, multi-layer reputation, faction simulation, and world memory —
is in [`Systems/LivingWorld.md`](Systems/LivingWorld.md); the per-NPC implementation
contract is [`Systems/NPCSystem.md`](Systems/NPCSystem.md).

---

## 11. Combat System

Combat is **heavy, grounded, and dangerous** — never flashy arcade combat.

Core actions: Light Attack, Heavy Attack, Block, Parry, Dodge, Sprint, Charged Attack,
Execution, and a Stagger system.

Weapon classes: Sword, Axe, Spear, Greatsword, Hammer, Torch (more in later expansions).

The full combat **design** — the three-resource triangle (Health/Stamina/Guard), the
Guard and Poise systems, the Perfect Deflect, the signature **Momentum** mechanic, the Fear
system, boss mastery-exams, and the skill ceiling — is in
[`Systems/CombatDesign.md`](Systems/CombatDesign.md); the implementation contract is
[`Systems/CombatSystem.md`](Systems/CombatSystem.md).

---

## 12. Weather System

Dynamic weather — fog, rain, thunderstorms, strong wind, and rare **Blood Moons** —
affecting visibility, enemy behavior, NPC schedules, exploration, and audio. Full design
in [`Systems/WeatherSystem.md`](Systems/WeatherSystem.md).

---

## 13. Survival System

**Light** survival, not punishing: food, rest, temperature, disease, injury, medicine,
and campfires. Survival creates texture and motivates the settlement loop without
becoming a chore. Full design in [`Systems/SurvivalSystem.md`](Systems/SurvivalSystem.md).

---

## 14. AI Requirements

NPC, enemy, wildlife, boss, faction, and settlement AI must support schedules,
pathfinding, combat, fear, investigation, patrols, and reputation reactions. Built on
Unreal's Behavior Trees, the AI Perception system, and Smart Objects / EQS.

---

## 15. Phase 1 — Vertical Slice

A fully playable **60-minute** experience that convinces players of the project's
potential. Must include:

- The Weeping Moors (a slice of it)
- 1 village, 1 dungeon, 3 side quests
- 1 mini-boss, 1 major boss (The Bell Keeper)
- Basic settlement, combat, inventory, crafting, dialogue, weather
- A working save system
- Polished visuals and professional UI

Target quality: a Steam demo that immediately reads as ambitious and special.

The build-ready production plan for this slice — scope cuts, region/settlement/roster designs,
asset strategy, phases, time estimates, and the definition of done — is
[`VerticalSliceProduction.md`](VerticalSliceProduction.md).

---

## 16. Ultimate Goal

A world players remember years later — ancient, beautiful, tragic, mysterious, and alive.
Every design decision should reinforce those five feelings. When in doubt, choose the
option that makes the world feel more *haunted and more believable*.

The complete **player journey** — the emotional arc from the first five minutes to the final
ending, binding combat, the living world, quests, bosses, factions, settlement, and
corruption into one lived experience — is mapped in [`PlayerJourney.md`](PlayerJourney.md).
It is the spine that keeps every system pulling toward the same feeling.
