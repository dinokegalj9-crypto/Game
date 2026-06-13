# Combat System

**Owner type:** `UHCCombatComponent` (in `Source/HollowCrown/Combat/`)
**Pillar:** Meaningful Progression. **Feel:** heavy, grounded, dangerous — never arcade.

> **This page is the implementation contract** (components, data, events). The combat
> *design* source of truth — feel, rules, the three-resource triangle, Guard/Poise,
> Perfect Deflect, Momentum, Fear, boss exams, skill ceiling — is
> [**CombatDesign.md**](CombatDesign.md). Where the two differ, the design doc defines the
> target and this contract is updated to match it.

---

## Design Intent

Combat should make every swing feel committed and every hit feel earned. The player is
mortal; positioning, stamina, and reading the enemy matter more than reflexes alone. This
is closer to a deliberate soulslike than a character-action game.

## Core Actions

| Action | Description | Cost |
|--------|-------------|------|
| Light Attack | Fast, chainable into a combo string. | Low stamina |
| Heavy Attack | Slow, high damage, high poise damage. | High stamina |
| Charged Attack | Held heavy; unblockable at full charge. | High stamina |
| Block | Reduces incoming damage; drains stamina on hit. | Stamina on impact |
| Parry | Timed block; on success, opens enemy to a riposte. | Small stamina |
| Dodge / Roll | I-frames; direction from movement input. | Medium stamina |
| Sprint | Faster movement; enables running attacks. | Drains stamina |
| Execution | Finisher on a staggered/opened enemy. | None; cinematic |

## Stagger & Poise

Every combatant has **poise** (on `UHCAttributeComponent`). Heavy and charged attacks
deal poise damage; when poise breaks, the target enters **Stagger**, a window in which an
**Execution** is available. Poise regenerates over time when not being hit. This is the
loop that rewards aggression without removing danger.

## Weapon Classes

Sword, Axe, Spear, Greatsword, Hammer, Torch. (More in later expansions.) Each class is a
`UHCWeaponData` data asset defining damage, stamina costs, poise damage, range, and the
animation montages for its moveset. Swapping weapons swaps movesets — no per-weapon code.

The **Torch** is dual-purpose: a weak weapon and a light/utility tool (fog, certain
enemies fear fire), reinforcing the survival and exploration pillars.

## State Machine

The component runs a small attack state machine: `Idle → Windup → Active → Recovery`,
with `Blocking`, `Parrying`, `Dodging`, and `Staggered` as parallel/overriding states.
Hit detection occurs only during `Active` via weapon traces on the `HCWeapon` collision
profile. Animation notifies drive the Active window so visuals and hits stay in sync.

## Events (delegates)

- `OnAttackStateChanged(EHCAttackState)`
- `OnHitLanded(AActor* Target, const FHCHitResult&)`
- `OnParrySuccess(AActor* Attacker)`
- `OnStaggered()` / `OnExecuted()`
- `OnDeath()` — consumed by the world-state pipeline for bosses (see Architecture §5).

## Integration

- **Stamina/poise:** read and modified through `UHCAttributeComponent`.
- **Corruption:** corruption-granted abilities extend the moveset or add power attacks;
  `UHCCorruptionComponent` registers modifiers the combat component queries.
- **Weather:** rain/wind can reduce traction or torch effectiveness via weather modifiers.
- **Bosses:** boss AI uses the same component; boss death triggers the world-change
  pipeline.
