# The Hollow Crown — Settlement & Legacy Design (I Built This)

> **Status:** Authoritative settlement / kingdom-building *design* source of truth.
> **Companion contract:** [`SettlementSystem.md`](SettlementSystem.md) (building/economy
> implementation). **Substrate:** [`LivingWorld.md`](LivingWorld.md) — the settlement is the
> living world at its most concentrated; this document extends it for *the player's home
> specifically.* **Also depends on:** [`../FactionBible.md`](../FactionBible.md) (external
> politics, trade, world reaction), the corruption framework
> ([`CorruptionSystem.md`](CorruptionSystem.md)), quest threads ([`QuestDesign.md`](QuestDesign.md) §11),
> and the Building/Settlement/Economy subsystems ([`../TechnicalArchitecture.md`](../TechnicalArchitecture.md) §2.7–§2.8, §2.23).
> **Scope:** settlement *design* — not code, not authored content.

---

## 1. Vision — building a legacy, not structures

The player is **not building structures. They are building a legacy** — a home, a reflection of
their decisions, and a living part of the world that will outlast (or outlive) them. **Every
building matters. Every citizen matters. Every decision matters.** By the end, the player should
care about the settlement **as much as any companion**, and leaving it should feel like a loss.

**The anti-city-builder doctrine** (what this is *not*):
- **Not a generic city builder** — there is no grid to optimize, no infinite sprawl, no
  faceless population. The settlement is **bounded and hand-known**; growth is *qualitative*
  (who joins, what you become) far more than quantitative.
- **Not a survival base** — it is a community, not a fort of crafting stations; people, not
  walls, are the point.
- **Not a resource-grind simulator** — resources exist to enable *people and choices*; every
  resource has real sinks (§9), and scarcity creates *decisions*, never busywork.

**Four signature ideas** make it a legacy instead of a builder (each load-bearing throughout):
1. **Every building needs a person.** A structure is dead stone until a named resident runs it
   (§7). Lose the smith and the forge goes cold. Buildings and people are one system.
2. **Growth is a double-edged sword.** Each tier up brings power *and* danger — the world
   notices, factions pressure, raids escalate (§4, §16). The player can *choose* a small loyal
   village over a vulnerable capital, and that is a real strategy.
3. **The settlement is a mirror.** It visibly reflects the player's choices and **corruption**
   (§17) — a place ruled by loyalty looks and behaves nothing like one ruled by dread.
4. **The settlement remembers.** A chronicle and physical memorials record the reign — victories,
   losses, the dead (§18). The town is a monument to what the player did.

---

## 2. Player Experience Goals → systems

| Feeling | Produced by |
|---------|-------------|
| **Ownership** | You *found* it, *recruit* its people, *choose* what it becomes (§3, §6); it is yours, not assigned. |
| **Responsibility** | People depend on you; crime, famine, raids, and disputes demand *your* judgment (§11–§15). |
| **Attachment** | Citizens are full, knowable residents you chose (`LivingWorld.md` §20); specialists are irreplaceable (§8). |
| **Pride** | Growth is earned through hard choices, not grind; the chronicle records it (§18). |
| **Regret** | Permanent death, failed defenses, choices that cost people (§11, §18) — the settlement keeps your mistakes. |
| **Protection** | Defense is real and playable; you stand on the walls for people you know (§11). |
| **Long-term investment** | The settlement persists and evolves across the whole game and into the ending (§19). |

---

## 3. Founding the Settlement

- **Where it begins:** a **dead village in the Weeping Moors**, near where the Crownless wakes
  (Design Bible) — a cluster of rotting timber houses around an abandoned church and a dry well,
  half-claimed by the fen. The starting region's mood (`ArtBible.md`) *is* the settlement's
  first face: fog, grief, ruin.
- **Why it's abandoned:** the Fall. Its people drowned, fled, or were taken when the rot reached
  the Moors (tied to the Bell Keeper's endless toll and the Fen Widow's despair, `BossBible.md`).
  The player is not clearing a blank lot — they are **reclaiming a place that died**, and its
  history is the first thing they uncover (environmental storytelling, `QuestDesign.md` §16).
- **Who arrives first:** **one survivor** — the irreplaceable **first resident** (a specialist or
  proto-companion, e.g. the last villager who hid in the church), whose trust the player earns and
  who becomes the seed of the community. The first recruit is *authored and unique*, so ownership
  is personal from the first hour.
- **What threats exist:** the corrupted dead of the Moors, opportunistic bandits, the fen itself
  (disease, flooding), and — once the settlement stirs — the *notice* of the wider world (§16).
  The founding tutorializes the loop: **reclaim → recruit → build one thing → survive one
  night** — and ends with the player *owning* something fragile.

---

## 4. Settlement Progression

A complete path from ruin to power. **Each tier is gated more by *people and stability* than by
raw resources** (anti-grind), and **each tier raises the stakes** — bigger benefits, bigger
risks, more of the world's attention.

| Tier | Population (named residents) | Requirements | Unlocks | Risks | Benefits |
|------|------------------------------|--------------|---------|-------|----------|
| **Abandoned Camp** | 1–2 | The founding (§3) | Campfire, tent, storage; basic crafting | Exposure, wildlife, first raids | A foothold; a place to return to |
| **Refugee Camp** | 3–6 | Shelter + food security + the first recruits | Housing, a workshop, a cook-fire hall | Disease, theft, desperation (low morale) | First specialists; the community forms |
| **Village** | 7–15 | Stable food + water + a defensible core | Blacksmith, market stall, temple shrine, palisade | Bandit raids; the world *notices* (§16) | Production, trade, a real home |
| **Fortified Village** | 15–30 | Walls + a garrison (real guards) + morale floor | Watchtowers, barracks, tavern, hospital | Organized raids, faction interest, crime | Defense; refugees seek you out |
| **Town** | 30–60 | Trade routes + governance + faith stability | Library, harbor (if coastal), guildhalls, town hall | Faction *intervention*, political pressure, conspiracies (§15) | Influence as a power; specialists flock |
| **Stronghold** | 60–100 | Military strength + economic surplus + leadership | Keep, advanced walls, special structures | Sieges, assassination, becoming a *target* | A regional military force |
| **Regional Capital** | 100+ | Dominant influence + alliances + a stable succession | Capital structures, regional authority, monuments | War, the Crown's notice, the burden of rule | A seat that shapes the region and the **ending** (§19) |

**The choice not to grow is valid.** A tight, loyal Village is safer and more intimate than a
sprawling Capital that paints a target on itself. Growth is a *strategy with costs*, never an
assumed goal — the game never punishes a player for keeping a small, beloved home.

---

## 5. Population — the cast, not a number

**Every resident is a full living-world resident** (`LivingWorld.md` §4): Name · Occupation ·
Skills · Relationships · History · Goals · Personality · Loyalty · Fear · Health · Reputation.
**No generic population counts** — the settlement's "population" is a *roster of people the
player can name and know.* Residents form relationships, pursue goals, age, grieve, and can die
permanently (`LivingWorld.md` §8, §12, §13). The settlement is a **cast**, and its story is the
sum of theirs. This is the single most important anti-city-builder commitment.

---

## 6. Recruitment — growth is choosing people

Population grows by **recruiting individuals**, each a deliberate choice (`LivingWorld.md` §14),
through:

| Source | Character |
|--------|-----------|
| **Rescue missions** | Save survivors from the corrupted, bandits, or disaster — they remember it (loyalty). |
| **Faction refugees** | Take in those fleeing a faction's reach — gaining people but the faction's attention (§16, `FactionBible.md`). |
| **Travelers** | Wanderers who choose to stay if the settlement is worth staying for (morale/prosperity, §12). |
| **Quest outcomes** | A Thread's resolution (`QuestDesign.md`) delivers (or costs) a resident. |
| **Political decisions** | A judgment, an alliance, or a mercy that earns a follower. |
| **Special discoveries** | Finding a hidden specialist (a hermit scholar, an exiled smith) — unique, irreplaceable. |

**Some recruits are unique and irreplaceable** — specialists (§8) and would-be companions whose
loss is permanent and felt. Each recruit brings their own traits, relationships, and **problems**
into the settlement, *seeding emergent story* (`LivingWorld.md` §6). You are not hiring units;
you are deciding *who you will be responsible for.*

---

## 7. Building System — every structure needs a person

Buildings are meaningful, slow, and **tied to people**: a building provides nothing until a
**resident with the right skill runs it**, and a building can be *shuttered by death* — making
both buildings and people matter, and making loss bite twice. Each building has a **purpose,
benefits, upgrade path, the NPC who runs it (and their interactions), and narrative relevance.**
(Placement/construction/destruction tech: `SettlementSystem.md` + Chaos.)

| Building | Purpose / benefit | Runs on | Narrative relevance |
|----------|-------------------|---------|---------------------|
| **Housing** | Population cap; residents need homes | A family | Whose home is whose; grief when one empties (§18) |
| **Blacksmith** | Weapons/armor/repairs; upgrades | A smith (specialist tier, §8) | The smith's craft and story; a forge gone cold reads as loss |
| **Workshop** | Crafting, building materials, tools | An artisan | Production backbone; apprentices and succession |
| **Barracks** | Houses the garrison; trains guards | A Commander (specialist) | Your *real* defenders, who can die (§11) |
| **Temple** | Faith need; rites, funerals, morale | A Priest (specialist) | Religion in the settlement (§14); funerals matter |
| **Market** | Trade; resource conversion; merchants | A merchant | The economic heart; trade routes anchor here (§10) |
| **Hospital** | Treats disease/injury; raises health | An Alchemist/healer | Plague Threads; who gets the scarce cure (§11/§14) |
| **Library** | **Knowledge** resource; lore, research, unlocks | A Scholar (specialist) | The chronicle lives here (§18); lost history (`FactionBible` §12) |
| **Walls / Watchtowers** | Defense rating; early warning | Guards/scouts | Battle-scars left as memorials (§18) |
| **Town Hall / Keep** | Governance; **Influence**; leadership seat | The leader (player or appointee) | Where politics plays out (§15); the seat of legacy |
| **Tavern** | Social hub; morale; news/rumor; recruitment | An Innkeeper | Where attachment is built; conspiracies whispered (§15) |
| **Harbor** | (Coastal) trade, fishing, naval defense | A harbormaster | Ties to the Drowned Brotherhood (`FactionBible`) |
| **Special structures** | Unique, story-gated (a relic shrine, a corruption-fane, a monument) | A specialist/choice | The settlement's *identity* — what makes *this* one yours |

**Upgrades** deepen rather than merely multiply: a Blacksmith → Master Forge unlocks *new craft
and a master's arc*, not just +production. **Buildings reflect the settlement's state** — they
decay when understaffed (`LivingWorld.md` §13), scar in raids, and *sicken visibly under
corruption* (§17).

---

## 8. Specialists — the irreplaceable

Specialists are **unique named NPCs** who unlock content no generic resident can, and whose
**loss is permanent** (high stakes, high attachment): **Master Blacksmith** (legendary
craft/upgrades), **Scholar** (research, lost history, the chronicle), **Alchemist** (medicine,
disease cures, corruption study), **Architect** (advanced/special structures), **Commander**
(a real garrison, defense doctrine), **Priest** (faith, morale, funerals, the stance toward
corruption), **Explorer** (maps, trade-route scouting, discoveries), **Merchant Prince**
(trade empire, Influence, faction deals).

- Each is **recruited through a quest or discovery** (§6) — earning them is a story.
- Each **unlocks unique content** (buildings, abilities, Threads) — a settlement's character
  comes from *which specialists it has*.
- Each is **irreplaceable** — if the Master Blacksmith dies in a raid, that craft tier is *gone*
  (or must be painstakingly rebuilt). Specialists make defense (§11) and judgment (§11/§15)
  genuinely fraught: you are protecting people you cannot replace.

---

## 9. Economy — resources serve people and choices

A grounded economy where **resources matter, trade matters, scarcity matters** — but every
resource has explicit **sources *and* sinks** (Economy framework, architecture §2.23), so there
is **no infinite-stockpile treadmill**. Scarcity exists to force *decisions*, not grinding.

| Resource | Source | Sink (the decision it forces) |
|----------|--------|-------------------------------|
| **Food** | Farming, hunting (Blackwood Hunters), fishing | Feeds residents; famine forces *who eats* (§11, `LivingWorld`) |
| **Wood** | Foresters | Building, repair, fuel |
| **Stone** | Quarry | Walls, keeps, monuments |
| **Metal** | Mining (corruption-lost sites are a risk/prize) | Arms, tools, upgrades |
| **Rare Materials** | Discovery, dangerous sites, boss remembrances | Special structures, legendary craft |
| **Luxury Goods** | Trade, craft | Morale, faction gifts, prestige |
| **Knowledge** | Library + Scholar | Research, unlocks, uncovering lost history |
| **Influence** | Town Hall, reputation, alliances | Political capital spent on factions, trade, governance (§10, §16) |

**Knowledge and Influence are non-physical resources** that make the economy about *power and
understanding*, not just bricks — Influence in particular is the currency of the political game
(`FactionBible.md`). The economy simulates on the coarse settlement tick even when the player is
away (`SettlementSystem.md`, `LivingWorld.md` §3).

---

## 10. Trade Networks

The settlement is a **node in a regional economy** (`LivingWorld.md` §13, `FactionBible.md` §8).
It **imports and exports** by surplus and need, and trade is a **relationship**, not a
spreadsheet:

- **Roads and rivers matter** — routes can be opened, cut by raids, or *taxed* by whoever holds
  them (House Carrow's roads, the Drowned Brotherhood's rivers, `FactionBible.md`).
- **Security matters** — an unsafe route dies; protecting trade is a defense problem (§11).
- **Politics matters** — trade ties bind the settlement to factions (a deal with the Ashbourne
  Houses brings goods *and* obligation); embargoes are a weapon used *against* the player as they
  grow (§16).
- Prosperous, connected settlements *spawn trade routes* (emergent, `LivingWorld.md` §13) — and a
  thriving market draws merchants and migrants, feeding growth (and risk).

---

## 11. Settlement Defense

**Threats are real and consequential** — raids destroy buildings and *kill named residents,
permanently.* Defense is not an abstract rating; it is people and walls the player fights for.

- **Threats:** bandits, corrupted creatures and monsters, cultists, **political enemies and
  faction raids** (`FactionBible.md` §15), sieges (at higher tiers), and **natural disasters**
  (fire, flood, disease, Blood-Moon surges, `WeatherSystem.md`).
- **Defense systems:** **walls & watchtowers** (Building system; destructible via Chaos), a
  **garrison of recruited guards** (real residents under a **Commander** specialist — they can
  die), **early warning** (scouts/Hunters/towers buy reaction time), and **the player's own
  blade** — major raids are **playable combat events** (`CombatDesign.md`), not menus. The player
  stands on the wall for people they know.
- **Morale governs defense** (§12): a frightened, disloyal settlement folds; a proud one holds.
- **Consequences are permanent:** a lost defense means dead residents, shuttered buildings
  (§7), a scarred town (§18), and morale collapse — a raid the player *fails* becomes one of the
  settlement's defining tragedies (`LivingWorld.md` §12).

---

## 12. Morale

Settlement **morale** is the community's collective spirit, and it touches everything:
**productivity, loyalty, crime, defense, migration, relationships, and quest generation.**

- **Raised by:** safety, prosperity, **just leadership** (how crime and disputes are handled,
  §11/§13/§15), faith stability (§14), victories, festivals, fair treatment of residents.
- **Lowered by:** raids and death, famine/scarcity, crime left unanswered, religious/political
  strife, **the player's corruption** (§17), broken promises, neglect.
- **Effects of low morale:** crime rises (§13), residents desert (migration out), defense
  weakens, conspiracies form (§15), and *dark* Threads generate. **High morale:** growth,
  loyalty that holds under siege, festivals, and hopeful Threads.
- Morale is **managed through leadership decisions, not a slider** — the player earns it by *how
  they rule*, and a single hard choice (an execution, a sacrifice, a mercy) can swing it.

---

## 13. Crime

As the settlement grows and morale strains, **realistic social problems** emerge (from the
`LivingWorld.md` emergence engine): **theft, corruption, smuggling, murder, faction
infiltration, and political conspiracies** (§15). Drivers: low morale + resident traits
(Greedy/Deceptive) + unmet need + **faction espionage** (`FactionBible.md` §13 — rivals plant
agents).

**The player must respond**, and *how* defines the settlement: harsh justice raises order but
can lower morale and harden the town (toward a fearful, corruption-friendly place); mercy can
raise loyalty but embolden crime; ignoring it lets rot spread. Every crime is a **moral-ambiguity
Thread** (`QuestDesign.md` §8 — the thief is starving; the murderer was wronged) with no clean
answer, and the player's pattern of judgment becomes the settlement's *character*.

---

## 14. Religion Inside the Settlement

Citizens **have beliefs** (the faiths of `FactionBible.md` §4–§5), and faith **influences
behavior and morale.** A **Temple** + a **Priest** specialist anchor it.

- **Religious conflict may occur** — orthodox Church faithful vs. doubters vs. heretics; a
  divided congregation lowers morale and breeds Threads.
- **Pilgrims may arrive** (the settlement on a pilgrimage route, `FactionBible.md`) — bringing
  alms, news, and tension.
- **Heresies may spread** — especially the **Crown-Touched Creed** under a corrupting player
  (§17): the Cult infiltrates the faithful, and the player must decide whether to suppress,
  tolerate, or *embrace* it.
- The player's **stance toward faith** (champion the Church, tolerate all, embrace heresy/the
  Cult) is a major identity choice that shapes which residents stay, which factions deal with the
  settlement (`FactionBible.md`), and the ending (§19).

---

## 15. Politics Inside the Settlement

**Power struggles emerge naturally** — a settlement is a small polity. Residents (especially
**Ambitious** ones, `LivingWorld.md` §5) may **disagree, compete, conspire, demand reforms, seek
leadership, or challenge the player's authority.** External factions try to **install proxies**
or turn residents (`FactionBible.md` espionage).

- The player is the **leader** (or appoints one) — but leadership is **contested**, not assumed.
  Rivals gather support when morale is low (§12) or the player is absent/corrupt (§17).
- The player **governs** through judgments, appointments, reforms, and the occasional necessary
  ruthlessness — each feeding morale, loyalty, reputation, and corruption.
- Internal politics is **faction politics in miniature** — the same grey, no-clean-answer design
  (`FactionBible.md` §1): the resident demanding reform may be right *and* a threat.

---

## 16. World Reaction — growth is visibility

**The world reacts to the settlement's growth** (`LivingWorld.md` world reaction;
`FactionBible.md` §15) — the central tension of progression (§4):

- **Merchants arrive** as prosperity and routes grow (§10); **refugees arrive** seeking safety,
  offering people but straining resources.
- **Enemies notice** — bandit raids escalate into organized assaults; the corrupted are *drawn*
  to a thriving (or corrupt, §17) settlement; a Stronghold invites sieges.
- **Factions intervene** — they court the player (alliance, trade), **pressure** them (tribute,
  demands), try to **absorb** the settlement into their power, or move to **crush** a rising
  rival. A Regional Capital becomes a *piece on the political board* (`FactionBible.md`).
- **Political pressure increases** with every tier — the bigger the legacy, the more the world
  contends for or against it. **You cannot grow quietly.**

---

## 17. Corruption & the Settlement (the mirror)

The settlement **visibly reflects the player's corruption stage** (the mirror, §1; Art Bible's
muted-gold "becoming") — the place itself changes as the Crownless does:

- **Citizens become fearful** — the faithful, the timid, and many specialists grow afraid; some
  **flee** (lost forever, lowering morale and capability).
- **Some citizens become loyal** — the corruption-drawn, the desperate, and **Crown-Touched Cult**
  adherents *flock* to a corrupting lord; the settlement's population *shifts in character*.
- **Mutations emerge** — corrupted residents, gold-veined structures; the town's very fabric
  sickens beautifully (`ArtBible.md`).
- **New opportunities appear** — Cult trade and corruption-powered special structures/abilities
  open *only* to the corrupt (`FactionBible.md` §16).
- **New dangers appear** — corruption raises monster attraction (more, worse raids,
  `WeatherSystem.md` Blood Moons) and turns the Church, Crownsworn, and Hunters hostile.

A settlement under a **human** leader is held by **loyalty and hope**; one under a **corrupted**
leader is held by **dread and the Cult**. Both are viable; both are *visibly different homes*.
The settlement is the clearest mirror the game holds up to the player's choices.

---

## 18. The Legacy / Chronicle System (the settlement remembers)

This is the **emotional core** — the system that turns a base into a legacy. The settlement
**records its history**, physically and in a chronicle:

- **A Chronicle** (kept in the Library/Town Hall) records **major victories, major losses, boss
  kills (`BossBible.md`), disasters, leadership decisions, and important citizens** — readable as
  the story of the player's reign.
- **Physical memory:** **memorials** for the dead (`LivingWorld.md` §12), **monuments** to
  victories, **battle-scars left unrepaired** as deliberate remembrance, statues of fallen
  specialists. The town's *appearance tells its history* — a player can read their own reign in
  the streets.
- **Living memory:** residents *reference past events* in dialogue ("since the night the walls
  broke…"), name children after the dead, and tell newcomers the settlement's legends — the
  player's deeds become the community's lore.
- The intent: the player looks at the settlement and sees **everything they did and lost** — the
  raid they barely held, the smith who died defending the gate, the famine winter, the boss whose
  fall is carved on the monument. **"I built this," and "this world will remember me."**

---

## 19. Endgame Settlement

Near the endgame, the settlement is no longer a project but a **power and a stake** that shapes
the conclusion (tying to the faction endings, `FactionBible.md` §18):

- **The kingdom:** a Regional Capital is a genuine force in Aldermark — it can shelter the
  desperate, anchor a region against the Dusk, or stand as the last free place.
- **The factions:** the settlement can become a **faction's seat or ally**, a *neutral
  third power* the factions must reckon with, or a **rival** they unite to destroy — the player's
  alliances and stance (§14–§16) decide which.
- **The ending:** the settlement's **fate is part of the ending** — it can prosper into the
  future, fall in the finale, be **sacrificed** for a greater outcome (no perfect ending,
  `FactionBible.md` §18), be inherited by a chosen successor, or become a **corrupted bastion** of
  the player's "becoming" (§17). Leaving it — or losing it — is meant to be **emotional**.
- **The future of the world:** more than any boss kill, the settlement is what the player
  *leaves behind* — the seed of what comes after the Crown. The game's final images should let
  the player see what their legacy became.

---

## 20. Honesty, Production & Phasing

- **Scope reality:** a settlement sim of this depth, fully integrated with the living world,
  factions, and corruption, is years of work; this bible is the **target and framework.**
- **Phasing (maps to the roadmap):** the **vertical slice realizes the founding loop** in the
  first Moors village — reclaim the dead village, recruit **3–6 named residents** (one unique
  specialist), build a **handful of people-run buildings**, survive **one scripted raid** with
  permanent stakes, and feel **ownership and one loss.** Prove the four signature ideas (§1) land
  *small* before scaling tiers, world reaction, and the chronicle.
- **The risk to watch:** drifting toward a city-builder under feature pressure — adding sliders,
  faceless population, or grind. Mitigation: hold the four signature ideas (§1) as gates, and
  keep the population a *named cast* (§5) no matter the tier.

---

## 21. Guardrails

- **Not a city builder, survival base, or grind sim** (§1) — if a feature optimizes a grid,
  faces a faceless crowd, or creates a stockpile treadmill, it is redesigned.
- **Every building needs a person** (§7) — no productive structure runs on nobody.
- **Every citizen is named and knowable** (§5) — there are no population numbers, only people.
- **Growth has real risk** (§4, §16) — power always raises the stakes; staying small is valid.
- **The settlement reflects the player** (§17) — corruption and choices visibly change the home.
- **The settlement remembers** (§18) — victories, losses, and the dead are recorded and seen.
- **Loss is permanent** — dead residents, lost specialists, and razed buildings do not respawn.

> The player should defend the settlement not because the game rewards it, but because the
> people on the wall have names. And at the end, looking back at what they built — and what it
> cost — they should feel they left a mark the world will not forget.
