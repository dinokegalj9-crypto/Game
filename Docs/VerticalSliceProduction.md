# The Hollow Crown — Vertical Slice Production Blueprint

> **Status:** PRODUCTION document — not design, not vision. It turns the design package into an
> **achievable solo build**. Assumes: **solo developer, Unreal Engine 5, no team, limited
> budget, maximum efficiency.**
> **Design sources it implements (read for *what*, this doc is *how/when*):** [`DesignBible.md`](DesignBible.md),
> [`PlayerJourney.md`](PlayerJourney.md), [`Systems/CombatDesign.md`](Systems/CombatDesign.md),
> [`Systems/LivingWorld.md`](Systems/LivingWorld.md), [`Systems/SettlementDesign.md`](Systems/SettlementDesign.md),
> [`BossBible.md`](BossBible.md), [`ArtBible.md`](ArtBible.md), [`TechnicalArchitecture.md`](TechnicalArchitecture.md),
> [`ProjectStructure.md`](ProjectStructure.md). Supersedes the slice portion of [`Roadmap.md`](Roadmap.md).
> **Goal:** detailed enough that **development can begin the day this is read.**

---

## 0. Producer's Note — the scoping mandate

The design package describes a multi-year AAA game. **This blueprint exists to cut it to a
provable 60-minute core.** Three rules govern every decision here:

1. **The slice proves the *identity*, not the *breadth*.** It must demonstrate that the combat
   feels like *The Hollow Crown*, the world feels alive, and the loop (explore → fight → boss →
   the world changes) lands. It does **not** demonstrate twelve bosses, six regions, faction war,
   or full simulation. *One of everything, polished* — never *many of everything, rough*.
2. **Buy, don't build, everything that isn't the identity.** A solo dev's scarcest resource is
   time. Environment, characters, base animations, audio, and VFX are **acquired and adapted**
   (Fab/Quixel/MetaHuman/Mixamo/marketplace); time is spent only on what makes the game *itself*:
   combat feel, the Bell Keeper, the mood, and the loop. (§8–§10 specify acquire-vs-make per asset.)
3. **Cut ruthlessly; defer honestly.** Every system ships in a **minimal "slice version"**
   (§2); the full design waits for post-slice. A feature that isn't on the critical path to the
   60 minutes is *out*, no matter how beloved.

**What the slice deliberately does NOT include:** GAS migration, the Mass crowd system, the
emergent Story Director, faction simulation, the economy/trade network, building placement
freedom, more than one region, more than one weapon class, multiplayer, and full corruption
staging. All are designed; none are sliced.

---

## 1. The Slice in One Paragraph

The Crownless wakes in the fog-drowned **Weeping Moors**, learns to move and fight against the
corrupted dead, and reaches **Mourn's End** — a dead village they reclaim as a first home,
meeting its lone survivor. A simple quest (*silence the bell that won't let the dead rest*) leads
out along a flooded causeway (exploration, a secret, **miniboss 1**), down into the **flooded
undercroft** beneath the church (a compact dungeon, environmental story, **miniboss 2**, a relic
key), back to a brief **raid on the village** (**miniboss 3**, a defense beat with one
permanent-stakes NPC), and finally up the leaning bell-tower to **The Bell Keeper** (major
boss). His fall grants the **first Crown fragment** — a corruption *choice* — the fog thins, a
path west opens, and a final vision hooks the next region. **~45 minutes**, hitting every
required beat: introduction, exploration, combat, NPC interaction, settlement interaction, quest,
one dungeon, three minibosses, one major boss, ending hook.

---

## 2. Scope Discipline — the Slice Version of Every System

The producer's core table: each designed system mapped to its **minimal sliceable subset** and
what is **deferred**.

| System | Full design | **SLICE version (build this)** | Deferred (do NOT build) |
|--------|-------------|--------------------------------|--------------------------|
| **Combat** | GAS, Momentum, directional, Poise+Guard, weights | Component-based (use repo scaffold): light/heavy/dodge/**deflect**/guard/stamina/execution; **1 weapon (sword)**; Guard+poise as simple floats | GAS, Momentum, directional attacks, multi-weapon, perilous-answer suite |
| **Player** | Full ability sets, corruption visuals | One character, fixed loadout, 2 corruption visual states | Equipment swapping, full stages |
| **Living world** | Mass + significance, emergence, memory, relationships | **8–10 hand-authored NPCs**, simple time-of-day schedules, 1 fear reaction to corruption | Mass, emergent Director, social graph, statistical sim |
| **Settlement** | 7 tiers, building placement, economy | Reclaim Mourn's End; **2 fixed reclaimable buildings** (light up on repair); 1 recruit | Free placement, tiers, economy, morale/crime sim |
| **Quests** | Story Director, branching, consequence latency | **3 hand-authored threads** (1 main, 2 side), simple flag-gated | Emergent generation, deep branching |
| **Bosses** | 12 Lords, 4 death guarantees | **The Bell Keeper** only, full quality; 3 reskinned minibosses | The other 11, Phase-4 tech |
| **Corruption** | 5 stages, ability sets, social/ending reflection | A meter + **1 fragment choice** + 1 visual shift + 1 NPC reaction | Stage abilities, faction inversion, endings |
| **Weather** | Subsystem, profiles, Blood Moon | **Baked fog + one scripted rain shift** for mood | Dynamic system, Blood Moon |
| **Save** | Record-based, WP-aware, versioned | **One autosave slot**, the §12 minimal set | Multi-slot, full reconciliation |
| **Audio** | MetaSounds, director, cues | Acquired SFX + 2 music tracks + 1 ambient bed; simple triggers | MetaSound graphs, dynamic mix |
| **UI** | Common UI suite, manuscript style | HUD + interaction prompt + 1 dialogue widget + boss bar + pause | Inventory/map/quest-log/settlement UIs |

If it isn't in the middle column, it is not in the slice.

---

## 3. Region Design — "Mourn's Reach" (a slice of the Weeping Moors)

A **small, dense, hand-crafted** slice — *not* an open world. Built as a **single streamed level
(or one small World Partition map)** to avoid streaming complexity at slice scale.

- **Name:** Mourn's Reach (the playable slice of the Weeping Moors).
- **Size:** ~**300 × 300 m** of *usable* play space, mostly linear-with-pockets — a critical-path
  causeway with 3–4 explorable side pockets. Fog limits sightlines, which **hides the small size**
  (a deliberate efficiency win the Art Bible already justifies).
- **Landmarks (orienting silhouettes through the fog):** the leaning **bell-tower** (the goal,
  visible from everywhere — the destination the player walks toward), the **ruined church** of
  Mourn's End, a **broken causeway bridge**, a **drowned standing-stone circle** (secret).
- **Village:** Mourn's End (§4) — the hub, near the start.
- **Roads:** one main **flooded causeway** spine connecting start → village → crypt → tower, with
  branch planks to the pockets.
- **Secrets (3, reward curiosity):** a sunken offering-cache in the stone circle (a relic), a
  hanged-man gibbet with a readable note (lore + a consumable), a submerged door to an optional
  mini-arena.
- **Dungeon location:** the **flooded undercroft** beneath the church (entrance in the village) —
  a compact 8–12 minute crypt.
- **Environmental storytelling beats:** the barred church door (survivors hid), drag-marks into
  the fen, a child's boat in a tree (the Bell Keeper's drowned child — `BossBible.md`), tally-marks
  counting the dead.
- **Progression path (gated, ~45 min):** Wake/tutorial fen → Mourn's End (NPC + settlement +
  quest) → causeway (explore + **miniboss 1**) → undercroft dungeon (**miniboss 2** + relic key) →
  return raid on village (**miniboss 3** + defense beat) → bell-tower → **Bell Keeper** → fragment
  + corruption choice → ending hook.

---

## 4. Settlement Design — "Mourn's End"

The dead village the player reclaims — the slice's proof that *settlement matters*.

- **Population (slice):** **4 named NPCs** present + the player; 1 recruitable during the slice.
- **Key NPCs:** **Aldith** (the lone survivor hiding in the church — the irreplaceable first
  resident, quest-giver, becomes the recruit); **Cob** (a wounded man the player can save in the
  raid — the permanent-stakes NPC who *can die*); **Maeve** (a frightened elder who reacts to the
  player's corruption choice); **Wat** (a half-mad bell-folk villager who hints at the Bell Keeper).
- **Buildings:** the **campfire** (rest/save/cook — the hub), **storage** (chest), and **2
  reclaimable structures** (the **well**, repaired → clean water → a morale beat; the **shrine**,
  repaired → a small blessing) that *visibly light up / clean up* on repair — proving "building
  matters" without a placement system.
- **Services:** rest & save at the campfire; basic crafting (1–2 recipes: a torch, a bandage);
  Aldith offers the main quest and, post-recruit, a stash.
- **Economy (slice):** none simulated — a handful of pickable resources (wood, cloth, herbs) feed
  the 2 recipes. That is all.
- **Quest hooks:** the main thread (the bell), one side thread (save Cob → he joins/survives), one
  side thread (find the offering in the stone circle for Maeve).
- **Future expansion potential (documented, not built):** the well/shrine slots show where tiers,
  more buildings, and recruits will grow post-slice (`SettlementDesign.md`).

---

## 5. NPC Requirements — exact roster

**Total: ~9 NPCs.** All hand-authored; none simulated by Mass.

| Role | Count | Who / purpose |
|------|-------|---------------|
| **Priority (quest/named)** | 4 | Aldith (survivor/recruit/quest), Cob (rescuable, mortal), Maeve (corruption reactor), Wat (lore) |
| **Specialist** | 1 | Aldith doubles as the proto-specialist (a healer) — proves the specialist hook |
| **Quest NPC** | (covered) | Aldith (main), Maeve (side), Cob (side) |
| **Merchant** | 0–1 | *Optional:* a passing peddler at the campfire (cut if time-pressed) |
| **Guard** | 1 | A single corrupted-but-not-yet-hostile watchman who turns in the raid (a tragedy beat) |
| **Civilian / background** | 2–3 | Mute/ambient villagers post-recruit to make the village feel inhabited |

**Cut line:** if behind, the slice works with **Aldith + Cob + the Bell Keeper's story alone** —
two living NPCs is the floor that still proves "NPCs feel like people + attachment + loss."

---

## 6. Enemy Requirements — roster & learning progression

A **tight roster built from one or two base skeletons**, reskinned/retuned for efficiency.

| Tier | Enemy | Teaches | Build cost |
|------|-------|---------|------------|
| **Basic** | **Corrupted Villager** (shambler) | Light attacks, dodging, the first kill (tragic) | Base humanoid |
| **Basic v2** | **Corrupted Villager (lunger)** | Spacing, when *not* to greed | Retune of base |
| **Elite** | **Drowned Watchman** (armored, shielded) | **Guard/deflect** vs a defended foe; poise | Base + shield + retune |
| **Ranged** | **Plague-Caster** (throws fen-bile) | Positioning, closing distance, cover | Base + projectile |
| **Special** | **Fen Stalker** (fast, ambush from water) | Awareness, lock-on, reaction | Base + speed/AI tweak |
| **Miniboss 1** (causeway) | **The Drowned Sergeant** | Deflect timing (a duel) | Elite + unique moveset montage |
| **Miniboss 2** (undercroft) | **The Choirless Acolyte** | Patience + ranged pressure in tight space | Caster + arena |
| **Miniboss 3** (raid) | **The Tithe-Collector** | Crowd + priority (fights with adds) | Base + adds + retune |
| **Major boss** | **The Bell Keeper** | The full exam: rhythm, spacing, anti-greed (`BossBible.md` I) | **Bespoke — the slice's biggest task** |

**Learning progression:** basics teach attack/dodge → elite/ranged teach guard/deflect/spacing →
minibosses each isolate one boss-skill → the Bell Keeper demands all of them. By design, every
mechanic the boss needs has been taught before the player reaches him.

---

## 7. Combat Requirements (the slice's identity — build with the most care)

Slice scope per system (built on the repo's component scaffold, `Source/HollowCrown/Combat/`; **no
GAS for the slice**):

| System | Slice scope |
|--------|-------------|
| **Movement** | Walk/sprint, sprint costs stamina, dodge-roll with i-frames; responsive, weighty |
| **Lock-on** | Single-target lock, switch targets, camera framing (the hardest camera work) |
| **Dodging** | Directional roll, i-frame window, stamina cost, anti-spam (rising cost) |
| **Deflecting** | The **heart** — tight timing window, no-stamina, big Guard damage, full feedback (hit-stop, spark, metallic ring, haptic) per `CombatDesign.md` §5 |
| **Guard** | A float on attacker & target; deflect/heavy damage it; zero → Guard Break + execution window |
| **Stamina** | Attacks/dodge/sprint cost; regen on neutral; "winded" punish |
| **Executions** | One per Guard Break / Poise Break; 1–2 animations; brutal, rare |
| **Weapon handling** | **One weapon (an arming sword)**: light combo, heavy, charged; AnimNotify weapon traces |
| **Enemy AI** | Behavior Tree/StateTree: approach, attack with telegraph, react to hit, group attack-token (fairness) |
| **Boss AI** | The Bell Keeper's phase StateTree: telegraphed slam, shock-ring, sweep; 3 phases; the bulk of the AI work |

**This section is where 40%+ of the slice's engineering time goes. Protect it.**

---

## 8. Art Requirements — acquire-vs-make asset list

**Default = ACQUIRE.** Make only what defines identity. (Sources: Fab/UE Marketplace, Quixel
Megascans (free), MetaHuman, AI-generated concept/UI via the proven Higgsfield pipeline. Verify
commercial licensing on every acquired asset.)

| Category | Strategy | Notes |
|----------|----------|-------|
| **Player character** | **MetaHuman** base + acquired hooded-wanderer outfit | Retarget animations to it |
| **Enemies** | 1–2 acquired humanoid bases + material/retune variants | All enemies from 1–2 skeletons (§6) |
| **Bell Keeper** | **MAKE** (kitbash + sculpt the bell/silhouette) | The one bespoke character; its silhouette is identity |
| **Weapons** | Acquired sword (the one weapon) | |
| **Armor/outfits** | Acquired modular medieval kit | Reuse across NPCs/enemies |
| **Buildings** | Acquired medieval/ruined village kit (e.g. modular) | Mourn's End + church + tower |
| **Props / set dressing** | Quixel Megascans + acquired prop packs | Gravestones, barrels, debris |
| **Environment (terrain/foliage/water)** | Megascans + UE water + foliage kit | The fen, causeway, fog |
| **VFX** | UE Niagara starter + acquired packs; tune to grounded style | Deflect spark, fog, bell shock-ring (make this one) |
| **UI assets** | **AI-generate** (manuscript style, `ArtBible.md` §15) | HUD frame, crown sigil, icons |
| **Icons** | AI-generate / acquired icon pack, restyle | Few needed for the slice |
| **Materials** | Acquired master materials + Megascans; one corruption MPC (make) | Corruption gold creep = make |
| **Textures** | Megascans + acquired | Almost none authored |
| **Animations** | §9 | The other big make/acquire decision |

**Make-list (the only bespoke art):** the Bell Keeper, the corruption material effect, the deflect
spark + bell shock-ring VFX, the UI manuscript skin, and the player's signature attack montages.
Everything else is bought and dressed.

---

## 9. Animation Requirements

**Acquire a soulslike/combat animation pack + Mixamo for the base; make only the signature
montages.** Retarget everything to the MetaHuman/UE Mannequin skeleton.

| Set | Animations | Source |
|-----|------------|--------|
| **Player locomotion** | idle, walk, run, sprint, dodge-roll (4-dir), turn, hurt, death | Acquired pack (Motion Matching optional; can defer to blendspaces) |
| **Player combat** | light combo (3), heavy, charged, **deflect**, block, guard-hit, parry-success, execution (1–2) | **Mostly MAKE/heavily edit** — feel is identity |
| **NPC** | idle, sit, work (2), walk, talk gesture, flee, sleep | Mixamo/acquired |
| **Basic enemies** | idle, walk, 2 attacks, hit react, stagger, death | Acquired + edit |
| **Elite/ranged/special** | + block, + throw, + lunge | Acquired + edit |
| **Minibosses** | a unique signature attack each (1–2) | Edit acquired |
| **Bell Keeper** | idle, walk, slam, shock-ring cast, sweep, phase transition, stagger, **death** | **MAKE/edit heavily** — the bespoke set |
| **Interactions** | open/loot, repair, rest at campfire, talk | Acquired/simple |
| **Settlement activities** | the NPC work/sit/sleep set (above) | Mixamo |
| **Cinematics** | intro (wake), Bell Keeper intro, fragment/ending-hook beat | Sequencer + reused anims; minimal bespoke |

**Cut line:** Motion Matching, layered weapon anim layers, and facial animation are **deferred** —
blendspaces + montages are enough for the slice.

---

## 10. Audio Requirements

**Acquire/generate everything; author no MetaSound graphs for the slice.**

| Category | Slice scope | Source |
|----------|-------------|--------|
| **Ambience** | 1 fen ambient bed (fog, water, distant bell) | Generate (proven pipeline) / acquired |
| **Combat SFX** | swing, hit-flesh, hit-block, **deflect ring**, dodge, stamina-empty | Acquired SFX library |
| **Enemy SFX** | 2–3 vocal sets, footsteps, death | Acquired |
| **Boss SFX** | Bell Keeper: the bell toll, slam, roar, death | Generate + acquired |
| **Weather** | rain layer for the scripted shift | Acquired |
| **UI** | select, confirm, back, corruption sting | Acquired/generate |
| **Music** | 1 exploration ambient track + 1 Bell Keeper boss track | **Generate** (Higgsfield) + edit |
| **Dialogue** | text + barks; **no full VO** for the slice (text + a few generated stingers) | Text-first |

**Cut line:** full voice acting and a dynamic music system are deferred; text dialogue + 2 tracks
+ a SFX library is the slice floor.

---

## 11. Programming Requirements — Critical / Important / Optional + order

Build in dependency order. **Do not start content (§3–§4) until Critical combat + interaction
work.**

**CRITICAL (no slice without these) — build first, in this order:**
1. Player controller + Enhanced Input + third-person camera (repo scaffold exists).
2. Attribute component (health/stamina/guard) + death.
3. Combat core: light/heavy/dodge, weapon trace, hit reactions (repo scaffold exists).
4. **Deflect + Guard + Guard-break + execution** (the identity — get the *feel* right here).
5. Lock-on + camera.
6. Enemy AI (BT/StateTree, perception, telegraphed attacks, group token).
7. Interaction component (talk/loot/repair/rest).
8. Save system (the §12 minimal set).
9. **Bell Keeper boss AI + phases** (the largest single task).

**IMPORTANT (the slice is hollow without these, but they follow Critical):**
10. Dialogue (data-driven, 1 widget). 11. Simple NPC schedule component (time-of-day). 12.
Settlement reclaim/repair + recruit. 13. Quest/flag tracking (3 threads). 14. Corruption meter +
fragment choice + 1 visual + 1 NPC reaction. 15. HUD + boss bar + pause + ending-hook sequence.

**OPTIONAL (cut first under time pressure):** crafting (2 recipes), the peddler merchant, the
optional secret mini-arena, the scripted weather shift, ambient civilian NPCs.

---

## 12. Save System — minimum requirements

**One autosave slot**, written at the campfire and on major beats; uses the repo's record-based
`UHCSaveSubsystem` approach (`Save/`). Minimum captured set:

- **World state:** which minibosses/Bell Keeper are dead; which gates/areas opened; the corruption
  fragment choice.
- **NPC state:** who is alive (esp. Cob), who is recruited (Aldith), corruption-reaction flags.
- **Quest state:** the 3 threads' progress flags.
- **Settlement state:** which of the 2 buildings are repaired.
- **Boss state:** Bell Keeper defeated flag (drives the ending hook).
- **Inventory state:** items, the relic key, the fragment.

No streaming reconciliation needed at slice scale (single level). Defer multi-slot/versioning.

---

## 13. Technical Risks

| Risk | Difficulty | Mitigation |
|------|-----------|------------|
| **Deflect/combat *feel*** (the whole identity) | **High** | Prototype it *first* (Phase 1) in a gym; iterate on feel before any content; budget the most time here |
| **Bell Keeper boss AI** (phases, telegraphs, fairness) | **High** | Build last in Core phase, on a proven enemy-AI base; reuse miniboss AI; keep to 3 readable attacks |
| **Solo scope creep** | **High** | This blueprint's §2 cut-table is law; review every new idea against "does the 60 min need it?" |
| **First-time UE5 depth** (if applicable) | Med–High | Lean on marketplace templates/tutorials; the architecture allows starting simple (components, no GAS) |
| **Asset-coherence** (bought assets clashing) | Medium | One palette/LUT + the Art Bible §18 checklist; restyle materials to the formula; reject clashers |
| **Lock-on camera** (collisions, framing) | Medium | Use a proven camera approach early; test in the crypt (tight space) |
| **Performance** (fog/foliage/water on a solo budget) | Medium | Bake what's static; Nanite/HLOD; profile early; the small region helps |
| **Burnout / momentum loss** | **High (solo)** | Phase gates with playable milestones; the gym is fun by week 4; ship the slice, not perfection |

---

## 14. Production Phases (detailed objectives + exit criteria)

**Phase 1 — Prototype (the feel).** *Objective:* prove the combat identity in a gray-box gym.
Player moves, dodges, **deflects**; one dummy enemy fights back; guard/stamina/execution work;
lock-on works. No art, no content. **Exit:** deflecting a basic enemy *feels good* to a tester —
the single most important gate in the project. If this isn't fun, stop and fix it.

**Phase 2 — Core Gameplay (the systems).** *Objective:* all CRITICAL + IMPORTANT systems (§11)
functional in gray-box: enemy roster AI, interaction, dialogue, NPC schedules, settlement
reclaim, quests, corruption meter, save, HUD, and a **gray-box Bell Keeper** with 3 phases.
**Exit:** the full 45-minute loop is *playable start-to-hook in gray-box* — ugly but complete.

**Phase 3 — Content Creation (the dressing).** *Objective:* build Mourn's Reach and Mourn's End
with acquired assets; make the Bell Keeper; place NPCs/enemies/secrets; wire the 3 quests and the
cinematics; add audio. **Exit:** the slice is *visually and sonically the game*, content-complete.

**Phase 4 — Polish.** *Objective:* combat feel pass (hit-stop, VFX, haptics, camera), boss
tuning, mood/lighting/fog pass to the Art Bible, audio mix, UI polish, performance to 60 fps.
**Exit:** the slice is *presentable* — it reads as a real game, not a prototype.

**Phase 5 — Testing.** *Objective:* external playtesting (does the identity land? does anyone
*care* / *grieve*?), balance the Bell Keeper and minibosses, fix bugs, verify save/load and the
60-minute pacing. **Exit:** the Success Criteria (§16) are met.

---

## 15. Time Estimation (solo, full-time)

**Heavily caveated:** depends enormously on the developer's UE5/combat experience and how
strictly §2 is obeyed. A *first-time* UE dev should multiply these; a part-time dev should
roughly double calendar time. Asset-leveraging (§8–§10) is assumed — building bespoke art instead
would multiply everything.

| Case | Duration (full-time solo) | Assumes |
|------|---------------------------|---------|
| **Best** | **~5–6 months** | Experienced UE/combat dev, disciplined scope, assets bought, deflect feel clicks fast |
| **Realistic** | **~9–12 months** | Competent UE dev, normal iteration on combat feel + boss, some scope fights |
| **Worst** | **~18–24 months** | Learning UE alongside, combat feel struggles, scope creep, bespoke art drift |

Rough phase split (realistic case): Prototype ~1mo · Core ~4mo · Content ~3mo · Polish ~2mo ·
Testing ~1mo (overlapping). **The combat feel + Bell Keeper alone are ~40% of the engineering.**

---

## 16. Success Criteria — the definition of done

The Vertical Slice is **complete** when **all** are true:

- [ ] A new player can play **start → ending hook in 30–60 minutes** without getting lost or stuck.
- [ ] **Combat works and feels like the identity:** deflecting feels great; guard-break→execution
      lands; stamina/dodge matter; a tester says it feels *deliberate and dangerous*.
- [ ] **Exploration works:** the player navigates Mourn's Reach by landmarks/fog (no marker
      hand-holding) and finds at least one secret naturally.
- [ ] **NPC systems work:** NPCs have names, schedules, and react to the player; at least one
      (Cob) **can die permanently** and the world acknowledges it.
- [ ] **Settlement works:** the player reclaims Mourn's End, repairs a building (visible change),
      and recruits Aldith.
- [ ] **The boss works:** the Bell Keeper is a **memorable, fair, 3-phase fight** that teaches its
      rhythm; victory feels *earned and tragic*; it grants the fragment and a corruption choice.
- [ ] **The world feels alive:** fog/audio/NPCs/environmental story make the Moors feel haunted
      and real.
- [ ] **The identity is clear:** a stranger who plays it can describe what kind of game *The
      Hollow Crown* is — dark, deliberate, tragic, alive.
- [ ] **It saves/loads** correctly across the §12 set, and runs at **60 fps** on the target machine.
- [ ] **Playtesters care:** the slice makes at least some testers *feel* something at Cob's fate or
      the Bell Keeper's death (the `PlayerJourney.md` emotional proof).

When the last box is checked, the slice is a **demo that proves the game** — the Phase 1 goal of
the whole project.

---

## 17. Day One — start immediately

1. Install UE 5.6; generate project files from `HollowCrown.uproject`; build the editor target
   (resolve the M0 first-compile fixups, `Roadmap.md`).
2. Create the **combat gym** map (`Content/Testing/Maps/L_Test_CombatGym`).
3. Acquire the **base animation pack + a humanoid enemy + the sword** (§8–§9) so the gym has
   something to feel.
4. Wire the player controller + attribute + combat component (repo scaffold) and **start
   iterating on the deflect** — Phase 1's single gate.
5. Do **not** touch the region, the village, or art until the deflect feels good.

> The whole project's risk lives in one question, answered in week one: *does deflecting a corrupted
> villager in a foggy gym already feel like The Hollow Crown?* Build to answer that first;
> everything else in this blueprint is downstream of "yes."
