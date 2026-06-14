# The Hollow Crown — Feasibility & Risk Analysis (Brutally Honest)

> **Status:** RISK / FEASIBILITY assessment. **Unsentimental by mandate.** Assumes a **solo
> developer, Unreal Engine 5, limited budget, real-world constraints.**
> **This is the counterweight to the design package** ([`DesignBible.md`](DesignBible.md) and
> the ten docs it links). Those describe the *ambition*; this describes the *reality*. Where they
> conflict, **a shipped small game beats an unshipped large one.**
> **Purpose:** identify what can realistically be built — and what will destroy the project.

---

## 0. The One-Sentence Verdict (read this first)

**As designed, The Hollow Crown is a 30–100+ person-year, funded-studio, multi-year AAA project;
a solo developer cannot build it, and attempting the full vision solo has a near-zero chance of
ever shipping.** A deliberately small game that preserves the *identity* (deflect-combat, one
haunted region, one tragic boss, a sliver of a living world) **can** plausibly ship solo. **The
single greatest threat to this project is the design package itself** — and the habit of
designing instead of building (§17).

Everything below supports that verdict. None of it means the design is *bad* — it means the
design is a **studio bible**, not a **solo build plan**, and the two must be separated to ship.

---

## 1. Risk Scale

| Rating | Meaning |
|--------|---------|
| **Low** | A solo dev can build it well with known tools/marketplace; bounded time. |
| **Medium** | Achievable solo, but real time/skill cost; feel/tuning-dependent. |
| **High** | Months of work, hard to get right, large testing surface; a likely scope/time overrun. |
| **Critical** | Realistically beyond solo scope at the designed ambition; a probable project-killer if attempted in full. |

---

## 2. System Risk Register

Ratings are for **the full designed ambition**, solo. The MVV scope (§14) lowers many of these
dramatically — that gap *is* the point.

| System | Feasibility (full design, solo) | Cost | Dev risk | Maint. risk | Scalability | **Rating** |
|--------|-------------------------------|------|----------|-------------|-------------|------------|
| Movement | Yes | Low | Low | Low | Good | **Low** |
| Melee combat core | Yes, with effort | High | High | Med | Good | **High** |
| **Deflect feel** | Yes but hard | High | High | Med | Good | **High** (identity-critical) |
| Guard system | Yes | Med | Med | Low | Good | **Medium** |
| **Momentum system** | Yes but unproven | Med | High | Med | Med | **High — cut candidate** |
| **Boss AI (×12)** | Each yes; *twelve* no | Very High | High | Med | Poor (per-boss) | **Critical** |
| Enemy AI (intelligent) | Partially | High | High | Med | Med | **High** |
| Weapon framework | 1 = yes; data-driven N = hard | Med–High | Med | Med | Good | **Medium→High** |
| Animation production | Bottleneck | Very High | Med | Low | Poor | **Critical (cost)** |
| Camera / lock-on | Yes, fiddly | Med | High | Med | Med | **High** |
| Difficulty balancing | Hard solo | Med | High | High | — | **High** |
| NPC schedules | Small cast yes | Med | Med | Med | Poor w/o Mass | **Medium** |
| NPC memory | Yes, bounded | Med | High | High | Poor | **High** |
| Relationships / families | Rabbit hole | High | Critical | Critical | Poor | **Critical** |
| Settlement simulation (full) | A second game | Very High | Critical | Critical | Poor | **Critical** |
| Emergent events | Unreliable to make *good* | High | Critical | Critical | Med | **Critical** |
| World-state branching consequence | Combinatorial | High | High | Critical | Poor | **High→Critical** |
| Save (full persistence) | Yes, risky | Med–High | High | High | Med | **High** |
| Faction simulation | A strategy game | High | Critical | Critical | Poor | **Critical** |
| Economy / trade | A sim game | High | High | High | Poor | **High→Critical** |
| Corruption (as designed) | Core yes; full reflections no | Med | Med | Med | Med | **Medium→High** |
| Weather system | Yes | Med | Low | Low | Good | **Medium** |
| 6 open-world regions | No (solo) | Very High | High | Med | Poor | **Critical (content)** |
| Multiplayer | No (solo, this scope) | Very High | Critical | Critical | — | **Critical — do not attempt** |
| GAS-scale architecture | Optional; learning cost | Med | Med | Low | Excellent | **Medium (defer)** |

---

## 3. Core Gameplay Analysis

- **Movement — Low.** Solved by UE + a marketplace locomotion set. Tuning, not risk.
- **Combat core — High.** A grounded melee system is *months* of iteration; the difference between
  "functional" and "feels like Lies of P" is enormous and is the entire value proposition.
- **Deflect — High, identity-critical.** Frame-timing + readable telegraphs + animation sync +
  feedback (hit-stop/VFX/haptics) is genuinely hard. **If this isn't excellent, the game has no
  reason to exist.** It must be prototyped *first* and the project gated on it (§13.2).
- **Guard — Medium.** Floats + states are simple; the risk is *feel*, shared with deflect.
- **Momentum — High, and the first thing to cut.** It adds combat complexity, a tuning burden, and
  UI, is unproven, and is **not needed to prove the identity.** A textbook "beloved feature that
  endangers shipping." Cut for MVV; revisit only if the core is shipped and great.
- **Boss AI — Critical.** Each good boss is a mini-project (moveset, telegraphs, phases, arena,
  tuning). The Bell Keeper alone is weeks-to-months. **Twelve is 1.5–3 years of boss work by
  itself** — the largest single sink in the project.
- **Enemy AI — High.** "Enemies that pressure, flank, punish, feel intelligent" is a bar most
  *studios* miss. Achievable in a simplified form; the designed sophistication is a time sink.
- **Weapon framework — Medium→High.** One weapon: fine. The data-driven multi-class moveset system
  multiplies animation and tuning cost (see Animation).
- **Animation — Critical (cost).** *The* production bottleneck for a solo combat game. Even with
  retargeting and bought packs, combat anims that *feel* right require heavy editing. Bespoke
  per-boss/per-weapon animation is where months vanish.
- **Camera/lock-on — High.** Lock-on across tight crypts and giant bosses (collisions, framing,
  target-switching) reliably eats more time than budgeted. A known solo pain point.
- **Difficulty balancing — High.** A solo dev *cannot* playtest a soulslike enough alone; the
  designer's skill is not the player distribution. Requires external testers early or the balance
  will be wrong.

---

## 4. Living World Analysis — realistic scope

The living-world design (`LivingWorld.md`) is the most *over-scoped* part of the project for a
solo dev. Brutal truth: **emergent simulation is the hardest thing in games to make reliably
good, and it is where solo projects disappear for years with little to show.**

| Feature | Reality | Realistic solo scope |
|---------|---------|----------------------|
| NPC schedules | OK for a small cast | **Build:** ~6–12 named NPCs, time-of-day StateTree |
| NPC memory | Feels great, bugs easily, bloats saves | **Build minimal:** a few flags ("you saved me / killed my kin") |
| Relationships / families | A simulation rabbit hole with infinite edge cases | **Mostly fake:** author key relationships by hand; no live social graph |
| Settlement simulation | A full colony-sim genre | **Reduce drastically** (§5) |
| Emergent events | Usually produces noise or bugs, not stories | **Cut the generator; hand-author "emergent-feeling" events** |
| Permanent consequences | Combinatorial QA explosion | **Bound to a handful of consequential flags** |
| World persistence | Real, valuable, risky | **Build, but keep the state set small** (§7) |

**Verdict:** ship a world that is *hand-authored to feel alive* (a few deep NPCs, scripted
"living" moments, permanent death of one or two characters) rather than a *simulated* world. The
player cannot tell the difference in a short experience — and the simulated version may never
ship at all.

---

## 5. Settlement Analysis — the "second game" problem

The full settlement design (`SettlementDesign.md`) is, honestly, **a second game** — a colony
sim with population dynamics, economy, morale, crime, politics, and legacy. Bolting a colony sim
onto a soulslike action-RPG, solo, is two full productions.

| Feature | Rating | Solo reality |
|---------|--------|--------------|
| Construction (free placement) | High | **Cut to fixed reclaim slots** (repair, not place) |
| Population growth | High | **Cut to hand-placed recruits** |
| Economy | High→Critical | **Cut** to a few pickup resources |
| Defense | Med | **Keep** as a scripted raid beat |
| Politics / crime / morale (sim) | Critical | **Cut** the simulations; use scripted events |
| Specialists | Med | **Keep** 1–2 as authored characters |
| Legacy / chronicle | Med | **Keep** a *cosmetic* version (memorials appear) |

**Verdict:** the settlement should be an **emotional set-piece you reclaim and a few people you
save**, not a simulation. That preserves "I built this" at ~5% of the engineering cost.

---

## 6. World State Analysis

The world-state hub (`UHCWorldStateSubsystem`) is **architecturally sound and should be built** —
it's cheap and central. The *risk* is not the system but **how much branching you hang on it.**
"The world reacts years later across factions/quests/regions" is a **combinatorial QA nightmare**
no solo dev can test. **Build the hub; keep the consequence web to a few flags with visible,
local effects.** Branching is a content-and-testing cost, not a tech feature.

---

## 7. Save System Analysis

Record-based persistence (`Save/`) is the right design, but it carries real risk:

- **Save bloat:** persisting every NPC, building, settlement, faction, and world flag grows
  unbounded. Mitigation: **bound the saved set** (don't persist ambient actors; store deltas, not
  the world); the MVV's small state set sidesteps this entirely.
- **Save/load bugs are project-fatal:** corrupted saves or lost progress kill trust and reviews.
  Mitigation: **keep state small, version from day one, autosave + backup slot, and test
  relentlessly** (the most under-tested system in solo projects).
- **World Partition reconciliation** (restoring per-cell actor state on stream-in) is genuinely
  hard. Mitigation: the MVV uses **a single small level** — no streaming reconciliation needed.

**Rating: High** at full scope, **Medium** at MVV scope. Optimization = *store less*, not *store
cleverly*.

---

## 8. AI Analysis

The dominant AI risk is **engineering time, not runtime performance.** Mass + StateTree + Smart
Objects + EQS + perception + group coordination + 12 bespoke boss brains is a multi-year AI
effort. Runtime perf (100+ NPCs) is solvable with Mass/significance — *if the dev has time to
learn and build Mass*, which is itself a High-risk time sink for a solo dev. **Bottleneck: the dev
learning and maintaining advanced AI, not the CPU.** MVV: a handful of BT/StateTree enemies + one
boss + simple scheduled NPCs — no Mass, no emergence.

---

## 9. Content Creation Analysis — the real killer

**Tech is not what kills this project. Content is.** Even if every system worked perfectly, a solo
dev cannot *fill* the designed world. Rough solo person-time (judgment, asset-leveraged):

| Content | Rough solo cost | Notes |
|---------|-----------------|-------|
| Combat to "feels great" | 3–6 months | Front-loaded, unavoidable |
| One small atmospheric region | 2–4 months | With kits/Megascans |
| **One bespoke boss (Bell Keeper tier)** | 1–3 months | Model, anims, AI, arena, music, VFX |
| **All 12 bosses** | **1.5–3 years** | The largest single sink |
| **6 open-world regions** | **3–6+ years** | Flatly infeasible solo |
| 100+ living NPCs | 6–18 months | Even with MetaHuman |
| Hand-authored quests (quality) | Months, ongoing | Writing + scripting + testing |
| Animation (full game) | Continuous bottleneck | Thousands of clips |
| Full audio + VO | A studio audio dept. | VO especially |
| Cinematics | Days–weeks each | |

**Full-vision content: conservatively 30–100+ person-years.** That is a funded studio for years,
not a person. **Bottleneck ranking:** (1) bosses, (2) regions, (3) animation, (4) NPC/quest
content, (5) audio/VO.

---

## 10. Art Analysis

Here is the **good news**, and it's real: **"Stylized Dark Realism" is one of the best possible
solo art directions.** Fog, darkness, and restraint (`ArtBible.md`) *hide* limitations, atmosphere
covers asset gaps, and the palette forgives. Combined with **Quixel Megascans (free), MetaHuman,
Fab kits, and AI-generated concept/UI**, the *environment* art is feasible solo.

- **Stylized Dark Realism: feasible** — atmosphere over fidelity is a solo superpower.
- **Environment pipeline: feasible** — Megascans + modular kits + fog.
- **Character pipeline: feasible** — MetaHuman + bought outfits; **bosses are the bespoke cost.**
- **Animation: the bottleneck** (see §9) — buy/retarget, minimize bespoke, accept "good enough."
- **VFX: feasible** — Niagara + packs; grounded style means *fewer* effects.
- **Asset reuse: essential and feasible** — one or two enemy skeletons reskinned, modular kits,
  shared materials. This is the strategy that makes the art shippable at all.

**Art is the *least* of the project's risks** — *if* the dev buys instead of builds. The risk is
re-introduced the moment they try to author bespoke art at scale.

---

## 11. Performance Analysis

Real but secondary (time > perf). Quick reads:

- **GPU:** Lumen/Nanite/fog on a limited target is a tuning job; the small MVV region helps; **Low–Med**.
- **CPU:** the full simulation (NPCs/Mass/AI/settlement tick) is the real CPU risk — **Med–High at full scope**, **Low at MVV**.
- **Memory:** soft-reference everything via Asset Manager (already in the architecture) — **Medium**.
- **Streaming:** World Partition is a learning + bug surface — **Medium**; MVV avoids it with one level.
- **Save:** bloat (§7) — **High at scope, Medium MVV**.
- **AI/Simulation:** the costliest at full scope; **MVV removes it.**

**Verdict:** performance is solvable; do not let it distract from the actual killers (scope and content).

---

## 12. Solo Developer Reality

| Verdict | Systems |
|---------|---------|
| **Keep (build well)** | Deflect/guard/stamina combat, lock-on, 1 weapon, ~6–12 NPCs w/ schedules, 1 great boss, 1 small region, reclaim-a-settlement set-piece, corruption *hook*, bounded save, the mood (art/audio) |
| **Simplify** | Enemy AI (fewer behaviors), world-state (few flags), weapon framework (1–2 weapons), corruption (1–2 visible stages) |
| **Delay (post-ship/team)** | More bosses & regions, faction reputation, weather system, more NPCs/quests, GAS migration |
| **Remove (for solo)** | Momentum, full living-world simulation, emergent event generator, settlement economy/politics/crime sim, faction *simulation*, economy/trade network, 12 bosses, 6 open regions, multiple complex endings, **multiplayer** |

---

## 13. Top Ten Project Killers (with mitigation)

1. **Scope (the #1 killer).** The design is ~100× a solo budget. → **Mitigation:** commit to the
   MVV (§14); treat the bibles as a *someday-with-a-team* roadmap, not a build plan.
2. **Combat feel never clicking.** No identity if deflect isn't great. → **Prototype it first;
   gate the whole project on a "is this fun?" test in month one** (the production blueprint's Day-One).
3. **The 12 bespoke bosses.** A 1.5–3 year sink. → **Ship with 1–3 bosses;** design the framework
   for reuse; add bosses only post-success.
4. **The living-world / emergence simulation.** An engineering rabbit hole that may never produce
   *good* output. → **Cut the generator; hand-author "alive" moments;** fake it small.
5. **The settlement full-sim (a second game).** → **Reduce to a reclaim set-piece + a few recruits**
   (§5).
6. **World-state branching consequences.** Combinatorial QA no solo can test. → **Bound to a few
   flags** with local effects (§6).
7. **Animation production.** The art bottleneck. → **Buy/retarget; minimize bespoke; accept
   "good enough"** outside the signature moves.
8. **Save bugs / bloat.** Lost progress is fatal to trust. → **Keep state small, version early,
   autosave+backup, test relentlessly** (§7).
9. **Solo burnout & infinite design** — *the meta-killer this very document exists to flag.*
   Twelve design docs and an unbuilt game is the warning sign. → **Stop designing; start building;
   ship the slice; let momentum (a playable thing) sustain morale** (§17).
10. **No playtesting (solo soulslike balance).** → **Get external testers from the prototype on;**
    do not balance to your own skill.

---

## 14. Minimum Viable Version — the smallest Hollow Crown that is still The Hollow Crown

A **polished 1–3 hour "short game" / premium demo** — essentially the vertical slice extended into
a complete, shippable experience. **This is the product.** It is solo-achievable in ~**12–24
months full-time** and preserves the identity.

| Tier | Contents |
|------|----------|
| **MUST HAVE (the identity)** | Excellent **deflect-combat** (guard/stamina/execution, 1 weapon); **1 haunted region** (the Weeping Moors slice); **1 tragic boss** (the Bell Keeper) + 2–3 reskinned minibosses; **~6 hand-authored NPCs** with a sliver of life and **one permanent death** that hurts; a **reclaim-a-settlement** set-piece; **corruption as a single meaningful choice**; **save/load**; the **mood** (fog, audio, art direction) |
| **SHOULD HAVE** | A 2nd boss + small 2nd area; a few more NPCs/quests; basic crafting; 1–2 corruption visual stages |
| **NICE TO HAVE** | A 3rd boss; light cosmetic settlement growth; the weather mood-shift; a 2nd weapon |
| **REMOVE (solo)** | Momentum, living-world sim, emergence, settlement economy/politics/crime, faction sim, economy/trade, 12 bosses, 6 regions, complex multi-ending matrix, multiplayer, GAS-scale architecture |

If the MUST-HAVE ships and is *good*, the game exists and has an identity. Everything else is
upside.

---

## 15. Phased Expansion Plan (ship-first)

The critical reframe: **the full vision is a POST-SUCCESS, funded-team ambition — reached only by
shipping the small game first.** Do not invert this.

| Phase | What exists | Goal |
|-------|-------------|------|
| **Prototype** | The combat gym: deflect feels great | Prove the identity is fun (gate the project) |
| **Vertical Slice** | The 45–60 min slice (`VerticalSliceProduction.md`) | Prove the loop + mood; a shareable demo |
| **Alpha** | The **MVV** content-complete (the 1–3 hr short game) | All MUST-HAVE built, rough |
| **Beta** | MVV polished, balanced, externally tested | Shippable quality |
| **Launch** | **Ship the MVV** (Steam premium demo / short game / wishlisting hook) | *A finished, real product* — and proof to funders/players |
| **Post-Launch** | *If it succeeds:* raise funds / build a small team → **then** expand toward the bibles (more bosses, regions, the living world, factions) | Grow the shipped game toward the vision *with resources* |

The bibles are not wasted — they become the **funded-team roadmap** the moment the small game
proves the concept and pays for help. That is the realistic path from these documents to the full
Hollow Crown: **ship small, earn the right to build big.**

---

## 16. Final Verdict

**Can the project realistically be built?**
- **The full designed game, solo: No.** It is a funded-studio, multi-year, 30–100+ person-year
  effort. Attempting it solo will not ship.
- **The MVV / focused short game, solo: Yes, plausibly** — with hard scope discipline and external
  playtesting.

**Probabilities (informed judgment, not precision — and most ambitious solo projects never ship):**
- Ship the **full designed vision** solo: **< 2%.**
- Ship the **combat prototype**: **~70%** (but that is not a game).
- Ship a **polished vertical slice / demo**: **~40–50%.**
- Ship the **MVV short game**: **~25–35%.**
- Build toward the **full vision with a funded team after a successful MVV**: realistic, on a
  multi-year horizon.

**What most improves the odds (in order):**
1. **Cut to the MVV (§14) and commit.** Single biggest factor.
2. **Prototype and gate on combat feel before anything else.**
3. **Stop designing; start building** (§17).
4. **Buy assets; build only the identity.**
5. **External playtesting from the prototype onward.**
6. **Treat the bibles as the someday-with-a-team roadmap, not the solo plan.**

The project is **not hopeless** — the identity is clear and marketable, the art direction is
solo-friendly, the foundation and a playable web slice already exist, and the design is a genuine
asset *for a funded team*. It becomes feasible the instant its scope is honest.

---

## 17. The Meta-Risk — stop designing, start building

This must be said plainly, because it is the highest-probability failure mode and the reason this
document was commissioned: **the project currently has twelve polished design documents and not
one minute of the actual game built.** That ratio is the classic signature of a project that
*designs forever and ships never.* Design is comfortable, infinite, and feels like progress;
building is hard, finite, and is the only thing that ships a game.

**The next action that most increases the probability of success is not another document.** It is
opening Unreal Engine and answering, in week one, the one question the whole project rests on:
*does deflecting a corrupted villager in a foggy gym already feel like The Hollow Crown?* Build to
answer that. Then build the slice. Then ship the MVV. The bibles will be waiting when there is a
team to build them.

> Ambition designed this game. Only discipline will ship it.
