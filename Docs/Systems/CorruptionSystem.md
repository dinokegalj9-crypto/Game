# Corruption System

**Owner type:** `UHCCorruptionComponent` (in `Source/HollowCrown/Corruption/`)
**Pillars:** Meaningful Progression + Consequences. This is the project's **signature
mechanic**.

---

## Design Intent

Power should never be free. Each fragment of the Hollow Crown the player absorbs (by
defeating a major boss) makes them stronger *and* less human. Corruption is the cost that
makes progression a real choice rather than a number that only goes up.

## The Value & Stages

Corruption is a single accumulating value (0–100) mapped to five visual/narrative stages:

| Stage | Threshold | State | World reaction |
|-------|-----------|-------|----------------|
| 1 | 0 | Normal human | None. |
| 2 | 20 | Darkened eyes | Some NPCs uneasy. |
| 3 | 45 | Visible veins | NPCs comment; a few become fearful. |
| 4 | 70 | Monstrous traits | Many NPCs fear or flee; some doors close. |
| 5 | 90 | Almost inhuman | Most NPCs fear the player; monster attraction high; "monstrous" endings open. |

Thresholds are data-driven (tunable), not hardcoded into logic.

## Benefits

- **New abilities** granted per boss (a corruption power tied to that fragment).
- **Enhanced combat** — damage/poise modifiers registered with `UHCCombatComponent`.
- **Special transformations** — temporary or stage-gated forms.
- **New dialogue options** — corruption-gated lines unlock with otherworldly knowledge.

## Drawbacks

- **NPC fear** — `UHCScheduleComponent` reads the player's stage and shifts behavior
  (uneasy → fearful → fleeing). Affects services, recruitment, and prices.
- **Physical mutations** — driven by the stage; mesh/material swaps on the player.
- **Altered endings** — the world-state subsystem records corruption stage at key beats;
  endings branch on it.
- **Increased monster attraction** — higher stages raise hostile spawn/aggression weight.

## Events (delegates)

- `OnCorruptionChanged(float Old, float New)`
- `OnCorruptionStageChanged(EHCCorruptionStage Old, EHCCorruptionStage New)` — the main
  hook; visuals, NPC fear, and audio subscribe.

## Integration & Flow

Corruption sits at the center of the boss-death pipeline (Architecture §5): a boss death
calls `AddCorruption(FragmentAmount)`, which may cross a threshold and broadcast
`OnCorruptionStageChanged`. That single event fans out to player visuals, NPC fear, and
ending state — no system polls corruption directly.

## Optional Mitigation (design space)

Whether corruption can be *reduced* is an open narrative question. Default stance:
corruption is largely **permanent** (reinforcing Consequences), with at most rare, costly,
story-significant ways to shed a fragment — never a routine sink. Decide before M3.
