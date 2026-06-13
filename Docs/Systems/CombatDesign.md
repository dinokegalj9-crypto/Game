# The Hollow Crown — Combat Design (The Duelist's Pressure)

> **Status:** Authoritative combat *design* source of truth (feel, rules, intent).
> **Companion:** [`CombatSystem.md`](CombatSystem.md) is the implementation contract
> (components, data, events); where the two differ, **this document defines the target**
> and the implementation doc is updated to match. Creative tone: [`DesignBible.md`](../DesignBible.md) §11.
> **Scope:** combat design only — not code, not content.

> **Tuning numbers in this document are first-pass targets** to be validated in the combat
> gym (per the project's "numbers before code" rule). They define *intent and ratio*, not
> final values.

---

## 1. Vision — "Every attack is a decision."

Combat is a **dangerous duel**, not a damage race and not a rhythm-button-press. The player
should feel **vulnerable, powerful, skilled, intelligent, focused, and — earned —
victorious.** Victory comes from *understanding*, never from statistics.

**The law of no free actions.** Every action carries four properties; if any is missing,
the action is broken and must be redesigned:

| Property | Meaning |
|----------|---------|
| **Risk** | It exposes you to something. |
| **Commitment** | It takes time you can't take back (wind-up + recovery). |
| **Opportunity cost** | Doing it means *not* doing something else (resource, tempo). |
| **Counterplay** | A skilled opponent (or player) can punish it. |

Therefore: **no action is free, spammable, or universally correct.** The deflect costs
timing-nerve; the dodge costs stamina and a direction read; the heavy costs commitment; even
the heal costs a window of total vulnerability.

**What makes it *not* a generic Soulslike (the identity):** most soulslikes resolve around
*stamina + i-frame rolls + chip damage*. The Hollow Crown resolves around a **three-resource
triangle (Health / Stamina / Guard)** with **two distinct break states (Guard break and
Poise break)**, a **deflect-centric defense** where the *best* defense costs no stamina, a
**directional commitment layer** (the KCD influence) that makes angle and spacing real
decisions, and a **Momentum dominance meter** — a wholly Hollow-Crown mechanic that turns
skilled play into a tangible, escalating in-fight advantage and, at its peak, a *Flow State*
of mastery. It is **70% the precision and aggression of Sekiro, 20% the spacing and weight
of Elden Ring, 10% the directional realism of Kingdom Come** — fused into something that is
none of them.

---

## 2. The Core Combat Loop

```
Observe → Analyze → Position → Defend → Create Opening → Punish → Recover → Adapt → (repeat)
```

- **Observe** the enemy's tells (anticipation frames, §15) and current state (guard angle, stance, morale).
- **Analyze** which win-condition is open: *chip Health*, *collapse Guard*, or *break Poise*.
- **Position** for reach and angle (flank = bonus, §8–9).
- **Defend** by the right tool: perfect deflect (cheap, aggressive), block (safe, costly), dodge (spatial, directional), or perilous-answer.
- **Create Opening** via Guard pressure, a Poise-breaking heavy on over-commitment, or a deflect chain.
- **Punish** the opening proportionally (don't get greedy — greed is the cardinal sin the system punishes).
- **Recover** — re-establish neutral, let resources breathe.
- **Adapt** — the enemy is learning you too (§7, §11).

The loop is **resource-and-read driven**, not combo-memorization driven.

---

## 3. The Three-Resource Triangle

Every encounter is a negotiation between three meters. The interplay — not any single bar —
is the game.

| Resource | Fiction | Drained by | Restored by | Empty =|
|----------|---------|-----------|-------------|--------|
| **Health (Vigour)** | Life force | Unblocked / partially-blocked hits, perilous mistakes | Limited, committal healing; rest | Death |
| **Stamina (Breath)** | Physical exertion | Attacking, dashing, sprinting, *blocking under pressure*, perilous-answers | Time in neutral (faster at higher Momentum) | **Winded** — brief total vulnerability (the real punish for over-exertion) |
| **Guard (Composure)** | Balance + defensive structure + mental pressure | Being attacked (esp. heavy), and **massively by deflects landed against you** | Slow regen when not pressured (rate scales with Momentum & stance) | **Guard Break** — massive stagger + execution window |

**The central decision the triangle forces, every exchange:** *Do I spend to deal Health
damage, or do I invest to collapse their Guard?* Guard break is usually the bigger payoff
(execution-tier), but it demands aggressive, deflect-heavy, riskier play. A patient chipper
and an aggressive Guard-breaker are both viable, and the *enemy's* state should tip which is
correct moment to moment. **Often, destroying Guard matters more than dealing damage** — and
the player should feel that tension constantly.

**Key asymmetry that defines the feel:** a **perfect deflect costs no stamina and deals
heavy Guard damage**, while a **normal block costs stamina and chips your own Guard.** Skill
is *literally cheaper* than safety. This single rule pulls players up the mastery curve.

---

## 4. The Guard System (central pillar)

Both player and enemies have **Guard**. It is the spine of the whole system.

- **Guard damage sources (ascending):** chip from a blocked hit < landing a light attack on a guarding enemy < landing a heavy < a **perfect deflect against them** (the biggest single source) < a perilous-answer counter.
- **Guard regen:** does not regen while under pressure (being attacked or attacking into a block); regenerates after a short lull. Regen **rate scales with Momentum** (dominant players recover composure faster) and with **stance** (a defensive stance trades offense for faster Guard recovery).
- **Guard Break state:** at zero Guard the target is flung into a long, readable **stagger** with an **execution window** (§17). For the player, Guard Break is a near-death moment that the enemy AI will try to convert — losing your Guard must feel *terrifying*, the way breaking theirs feels triumphant.

**The standing question:** every moment you ask *"deal damage, or break Guard?"* The answer
shifts with the enemy's Guard level, your Momentum, your Stamina, and how committed their
current action is. That ongoing recalculation **is** the gameplay.

---

## 5. The Perfect Deflect System (the heart of mastery)

> Blocking is easy. Deflecting is hard. The skill gap between them is where The Hollow
> Crown's combat lives.

| | Normal Block | **Perfect Deflect** |
|---|---|---|
| Input | Hold guard | Tap guard in a tight window as the blow lands |
| Window | — | ~**90–120 ms** at Momentum 0 (widens slightly with Momentum, §6) |
| Damage taken | Reduced, some chip | **None** |
| Stamina | **Costs** stamina | **Free** |
| Your Guard | Chipped | Untouched |
| Their Guard | Minor | **Heavy damage** |
| Momentum | None / slight loss | **Builds** (§6) |
| Extra | — | May **interrupt** certain enemy attacks; chains into deflect-strings |

A perfect deflect is **defense as offense**: you take nothing, spend nothing, hurt their
Guard, and build dominance. A run of deflects against a combo melts an enemy's Guard and is
the cleanest path to a Guard Break. The risk: mistime it and you eat the hit (and if you
were *trying* to deflect a perilous attack that can't be deflected, you're punished harder).

**Perilous attacks (the read layer):** certain attacks are marked perilous (a flash + a
distinct audio sting, §16) and **cannot be deflected normally** — each demands a specific
answer:
- **Thrusts** → a directional **step-deflect / counter** (read the line, beat it aside).
- **Sweeps (low)** → must **jump/step**, not deflect.
- **Crushers (heavy overhead)** → must **dodge** (deflecting only delays the Guard damage).
- **Grabs** → must **create distance**; unblockable, undeflectable.

This converts "block everything" into "**read which answer this attack demands**," which is
the core observation skill the whole game teaches.

### Deflect feedback (must feel incredible)

A successful deflect is the game's signature sensation. Required, every time:
- **Distinct metallic impact** — a specific, recognizable timbre (sharper/brighter than a block).
- **Brief time dilation** — a very short hit-stop / micro-slow (~60–110 ms) on contact.
- **Powerful spark** — a sharp, *small* (not noisy) burst of sparks at the contact point, cold-white with a muted-gold edge.
- **Camera reaction** — a tight kick/shake, subtle push-in.
- **Enemy reaction** — a real flinch/recoil proportional to Guard damage dealt.
- **Controller feedback** — a crisp haptic "tick" + trigger pulse.

The player must know they nailed it **before they consciously process it** — the feedback
*is* the teacher.

---

## 6. The Momentum System (the unique Hollow Crown mechanic)

**Momentum is combat dominance made tangible** — the meter that makes *skill*, not stats,
the source of power. It rises and falls **within a single fight** and resets between
encounters.

**Rises with skillful aggression:** perfect deflects, perfect dodges, Guard Breaks,
executions, accurate offensive pressure, varied (non-repetitive) play.

**Falls with mistakes and timidity:** taking damage, **panic-rolling** (spam-dodging),
whiffed attacks, prolonged passive/turtle play, getting Winded.

| Level | Name | Effect (sharpened capability — never magic) |
|-------|------|---------------------------------------------|
| **0** | Neutral | Baseline. |
| **1** | Composed | Minor: slightly faster Stamina & Guard regen. |
| **2** | Pressing | Faster Stamina recovery; modestly wider deflect window; +Guard damage. |
| **3** | Dominant | Opens **special opportunities**: deflect-counters, follow-up cancels, harder Poise/Guard damage; enemies more likely to break morale (§10). |
| **4** | **Combat Flow** | A brief **state of mastery**: heightened clarity (subtle world-focus and telegraph emphasis), maximal deflect leniency, near-free Stamina, fastest Guard pressure. **Not supernatural — focus, not sorcery.** Decays steadily; sustained only by continued flawless play. |

**Design intent:** Momentum rewards the player for *playing well right now* and viscerally
punishes panic. It is the mechanical engine of the experience curve (§19) — the same inputs
feel weak at Momentum 0 and devastating at Flow, so a 50-hour master *looks superhuman* on
identical stats. Crucially it is **earned live and can be lost in one greedy mistake**, so it
never becomes a passive power buff.

> **Corruption note:** corruption (the meta-progression) may *re-flavor* Flow visually
> (gold creeping into the world-focus) but must **not** replace the skill requirement.
> Power that bypasses skill violates the combat vision.

---

## 7. The Anti-Spam System

Repetition is boredom and the death of mastery. Two layers discourage it:

1. **Diminishing returns (mechanical):** repeating the *same* action back-to-back
   (same-direction dodge, identical light string, held block) yields **less Momentum, rising
   Stamina cost, and reduced effect** (e.g. consecutive identical dodges shed i-frames). Variety
   is mechanically efficient; spam is self-punishing.
2. **Enemy reading (AI, §11):** opponents **recognize patterns** and adapt — three dodges
   in one direction and the enemy delay-attacks to catch the roll; persistent turtling draws a
   Guard-break or grab; predictable combo timing gets deflected or interrupted. Predictability
   is punished *by the world*, not just by a meter.

The lesson the player internalizes: **adapt, or be read.**

---

## 8. Positioning & Spacing

Position is a resource. The player constantly weighs **distance, angle, timing, enemy
orientation, and terrain.**

- **Distance / reach:** each weapon owns an ideal band (§12 weight). Fighting inside or
  outside your band is a mistake the enemy exploits; **footswork** (step-in/out, circle) is a
  first-class action.
- **Terrain:** high ground, chokes (fight groups one-at-a-time), hazards, walls behind you
  (no dodge room) — all read by both sides.
- **Enemy orientation:** enemies guard a **facing arc**; getting *off* that arc is the
  spatial goal of every exchange (§9).

Spacing mistakes are punished as hard as timing mistakes — this is the Elden Ring 20%.

---

## 9. Directional Combat (the KCD layer)

Attacks originate from **Left, Right, Overhead, or Thrust**, and defense is directional too.

- **Attacking:** direction is chosen by stick/aim + input; mixing directions is how you
  pressure a defending enemy and bait their guard the wrong way.
- **Enemy guard has an angle.** Striking *into* their guarded line is heavily reduced;
  striking the **exposed angle**, or **flanking** (side/rear, off their facing arc), deals
  **bonus Guard and Poise damage and can bypass deflect** entirely. Some enemies telegraph a
  specific exposed weakness by angle — reading it is the puzzle.
- **Defending:** **timing is king** (a well-timed deflect works regardless of direction), but
  **matching the deflect direction to the incoming line** grants a **bonus** (extra Guard
  damage, wider effective window, enables deflect-counters at Momentum ≥3). Directional
  perilous-answers (the step-deflect vs a thrust) are pure read+direction.

Flanking is rewarded; turning your back is punished; group fights become **spatial puzzles**
of keeping enemies in front and in your weapon's band.

---

## 10. Poise — separate from Guard

**Guard ≠ Poise.** They are two different break states with two different counters, and
keeping them distinct is essential (no redundancy):

| | **Guard** | **Poise** |
|---|---|---|
| Represents | Defensive structure / mental pressure / stability | Physical mass / resistance to being interrupted |
| Built down by | Sustained pressure + **deflects** (many exchanges) | **Single heavy/charged blows**, esp. into a committed action (a burst) |
| Time scale | Cumulative over an exchange | Within a short window (a burst breaks it or it resets) |
| Break result | Long stagger + **execution** | Stagger / stumble + **opening** (shorter than Guard break) |
| Who has lots | Everyone (universal pressure system) | **Heavy enemies** (high Poise, low mobility, high commitment) |

- **High-Poise heavies** don't flinch from light hits — you *cannot* light-spam them into a
  stumble. You must either invest heavy/charged commitment to **burst their Poise**, or out-last
  them by deflecting their big swings to collapse their **Guard**. Two valid routes, different
  risk profiles.
- **Poise also gates trades:** an enemy mid-heavy with high Poise will *not* be interrupted by
  your light — so trading is a real, sometimes losing, decision.

This gives the roster texture: nimble low-Poise foes are deflect/Guard duels; armored
high-Poise foes are commitment/Poise puzzles.

---

## 11. Weight System

Every weapon must **feel physically real.** Mass is the master stat that touches everything:

| Weapon mass | Attack speed | Recovery | Move speed | Stamina/swing | Poise damage | Guard damage |
|-------------|-------------|----------|-----------|---------------|--------------|--------------|
| **Light** (dagger, arming sword) | Fast | Fast | Fast | Low | Low | Low–med |
| **Medium** (longsword, axe, spear) | Moderate | Moderate | Moderate | Moderate | Medium | Medium |
| **Heavy** (greatsword, hammer) | Slow | Slow (long, punishable) | Slow | High | **High** | **High** |

The player should **feel the mass** in the animation weight (§15), the camera, the haptics,
and the commitment. A hammer's overhead is a *decision you live with for a second*; a dagger's
flurry is cheap but barely dents a heavy's Poise. Weapon choice is a playstyle thesis, not a
stat upgrade.

---

## 12. Enemy Intelligence

Enemies **do not wait their turn.** They behave like thinking opponents:

- **Pressure** — close distance, deny your Stamina recovery, contest neutral.
- **Flank & surround** — work your angles, attack off your facing (the player's own §9 used against them).
- **Retreat & re-engage** — bait whiffs, reset to their preferred band.
- **Ambush** — use terrain and the fog (the world's signature) to open fights on their terms.
- **Defend allies & coordinate** — see group rules below.
- **Punish the universal sins:** healing (they rush a heal animation), **panic** (they catch the roll), and **predictability** (they deflect/feint your repeated patterns, §7).
- **Feint** — wind up, cancel, and catch an early deflect; the highest-tier human enemies bait your deflect timing.

**Group fairness via attack tokens (hard but fair):** a shared pool limits how many enemies
may *commit* an attack at once; others pressure, reposition, and threaten so the fight feels
relentless without being a cheap gang-stun. Backstabbers still threaten — the answer is *your*
positioning (§8), not enemy politeness.

---

## 13. The Fear / Morale System (combat feels alive)

Many human/animal enemies have **morale** and visibly move through states: **Aggressive →
Nervous → Fearful → Panicked.**

- **Triggers (toward fear):** their **leader's death**, witnessing an **execution**, **fire/torch**, being **outnumbered or flanked**, taking heavy losses, *your* high Momentum/Flow.
- **Behaviors by state:** nervous foes hesitate and over-defend (openings); fearful foes give ground and **call for allies**; panicked foes **make mistakes**, **flee**, or surrender.
- **Psychological play is real play:** a brutal execution can **break a whole group**; a torch can hold back nervous fodder; killing the leader first can rout the rest. The player wields *pressure* as a weapon.
- **Exceptions:** bosses, the corrupted, undead, and Crown-touched are **immune or inverted** (some grow *more* aggressive as they fail) — fearless enemies feel categorically different and more dreadful.

Morale turns group combat from a math problem into a **living, reactive engagement.**

---

## 14. Boss Design — Mastery Exams

Bosses are **exams, not health sponges.** Each teaches Observation, Timing, Adaptation, and
Patience, and each owns a **unique rhythm** the player learns like choreography.

**Three-phase structure (escalation of *understanding*, not just stats):**

| Phase | Purpose | Player is doing |
|-------|---------|-----------------|
| **1 — Learning** | Introduce the boss's rhythm & core tells | Observing, pattern recognition, surviving |
| **2 — Pressure** | Add mix-ups, perilous variants, faster strings | Adapting, punishing greed, managing resources |
| **3 — Mastery Check** | Combine everything; demand the learned dance | Demonstrating understanding — clean reads, confident punishes |

A boss should feel **impossible → predictable → manageable → beautiful.** Victory should feel
like a **dance you finally know**, achieved because *you* improved — not because numbers did.
Bosses are designed deflect-and-read-first (the Sekiro 70%): their pressure makes the Guard
duel and perilous-answers the path, and greed (one extra hit) is the death you'll replay in
your head.

### Worked example — The Bell Keeper

*(Mechanics only; lore in the Design Bible.)* **Themes:** madness, isolation, faith.
**Combat philosophy: control space, control rhythm, punish greed.**

- **Rhythm:** ponderous, tidal — long **toll-and-slam** beats with a heavy, readable cadence.
  The whole fight has a *metronome* the player must internalize; the bell's toll is both threat
  and timing cue.
- **Space:** expanding **bell shock-rings** force constant repositioning (§8) — you cannot
  stand and trade. The arena's geometry and the rings teach spacing.
- **Reads:** mixes deflectable swings (build to a Guard break), **perilous crushers** (must
  dodge), and **perilous sweeps** (must step) — the encounter is a live exam in §5's
  perilous-answer system.
- **Greed punish:** after a big slam there's a *tempting* but *too-short* opening; greedy
  players who take the extra hit get caught by the recovery toll. Patience and the correct
  *single* punish are rewarded.
- **The curve:** at first the bell is chaos; then you hear the rhythm; then you deflect the
  string, dodge the crusher, land the one clean punish, and break his Guard for the execution.
  The ideal final victory is **silent, certain, and looks effortless** — a dance.

---

## 15. Combat Camera (camera is a mechanic)

- **Excellent visibility, minimal obstruction** — the camera never costs the player a read.
- **Smooth, intelligent lock-on** with easy target switching; soft target priority for the threat that's *committing*.
- **Boss scaling** — auto-frames large bosses so tells stay visible; pulls out for shock-ring/AoE awareness.
- **Indoor & outdoor support** — collision-aware framing in tight crypts and corridors (no clipping, no blind walls); wide composure outdoors.
- **Dynamic framing** — subtle push-in on deflects/executions, controlled shake on impacts (never disorienting), brief widen at phase changes.
- **Multi-enemy awareness** — when locked in a group, the camera and an off-screen-threat indicator keep flankers legible (supports §8/§12).

If the camera hides a tell, the system has failed — readability is sacred.

---

## 16. Audio Requirements (understandable by sound alone)

Combat must be **legible with eyes closed.** Each state owns a **distinct, learnable audio
signature** — the player learns to fight *by ear* as much as by eye:

| Event | Audio identity |
|-------|----------------|
| Guard damage (theirs/yours) | Dull, stacking impacts that "tighten" as Guard nears break |
| **Guard Break** | A decisive shattering/collapse sting — unmistakable, triumphant or dreadful |
| Poise Break | A heavy stagger thud — mass giving way |
| **Perfect Deflect** | The signature bright metallic *ring* (the sound players will chase) |
| Perfect Dodge | A sharp cloth/air *whip* + faint time-dilation swell |
| Execution | A brutal, final, low hit + silence |
| Boss phase change | A musical/diegetic shift (the bell re-tunes) — the exam escalates |
| Momentum gain / Flow | A rising tonal layer; at Flow, the mix focuses (world dampens, heartbeat clarity) |
| **Perilous attack** | A unique, instantly-recognizable warning sting (distinct per answer-type) |

Audio is the **second teacher** beside animation; the two must always agree.

---

## 17. Execution System

Executions are **earned, brutal, fast, impactful — and rare.**

- **Earned only by** a **Guard Break** or a **Poise Break** (or specific scripted openings) —
  never spammable, never a default finisher on full-Guard enemies.
- **Feel:** decisive, weighty, grounded violence (no flashy excess, per the Art Bible);
  brief, readable, with a beat of silence after.
- **Tactical weight:** an execution **restores a little composure/Momentum**, and — critically
  — **terrifies witnesses** (§13 Fear). It is both a reward and a psychological weapon in group
  fights.
- **Restraint:** kept rare so it stays special; overuse is a design failure.

---

## 18. Animation Requirements

Combat quality *is* animation quality. Every attack (player and enemy) must read its
intention through the four-beat language so the player **learns visually**:

1. **Anticipation** (wind-up) — telegraphs *what, from where, and how perilous* before it lands. The longer/heavier the attack, the clearer the tell.
2. **Impact** — the moment of contact, sold by hit-stop, camera, and FX.
3. **Follow-through** — honest continuation that conveys force and mass.
4. **Recovery** — the punishable tail; its length is the attack's opportunity cost made visible.

Plus **momentum and weight** in every motion (heavy weapons *settle*; light weapons *snap*).
**An attack the player cannot read before it lands is a bug**, not difficulty. Directional
attacks (§9) must telegraph their *line*; perilous attacks must be unmistakable.

---

## 19. The Experience Curve & Skill Ceiling

The systems are tuned to produce this arc **without changing stats**:

| Time | Experience | Which systems produce it |
|------|------------|--------------------------|
| **First hour** | Struggle, panic, *barely* survive | Vulnerability of the triangle (§3); deflect windows feel tight; everything is a threat |
| **~10 hours** | Understanding; beginning to master enemies | Reading tells (§18), perilous-answers (§5), Guard-vs-Poise routing (§10), Momentum basics (§6) |
| **~50 hours** | Looks **unstoppable — looks superhuman** | Living in Momentum/Flow (§6), flawless deflect chains, perfect spacing/flanking (§8–9), psychological control of groups (§13) — *all skill, no stat inflation* |

**The skill ceiling is deliberately very high.** Average players finish the game by patient,
correct play. Masters look almost superhuman because they: sustain Flow, deflect-chain entire
combos, answer perilous attacks on reaction, flank to bypass guards, never panic-roll, and
punish with perfect economy. **The gap between average and master is pure skill — not level,
gear, or statistics.** That is the promise.

**The defining feeling, start to finish:**
> Early: *"I lost because I made mistakes."*
> Later: *"I won because I became better."*

If a player ever feels they lost to the *system* rather than to their own mistake — or won by
*stats* rather than skill — the design has failed.

---

## 20. Design Guardrails (what this system must never become)

- **Not a generic Soulslike:** defense is deflect-first and *cheaper than safety*; two break
  states, not one posture bar; Momentum and directional/flanking layers are core, not garnish.
- **Not hack-and-slash:** no free DPS; light-spam can't break heavies; greed is punished.
- **Not button-mashing:** anti-spam (§7) + enemy reading make repetition strictly worse than reading.
- **Power is skill, never stats:** progression and corruption may add *options and flavor*,
  never bypass the read/deflect/spacing skill that defines mastery.
- **Readability is sacred:** camera (§15), animation (§18), and audio (§16) must always let a
  fair player see the loss coming. Difficulty comes from *demanding execution of a readable
  challenge*, never from hiding information.
