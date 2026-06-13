# The Hollow Crown — Project Structure & Production Pipeline

> **Status:** Authoritative project/pipeline standard. **Engine:** Unreal Engine 5.6.
> **Audience:** Everyone touching the project — engineering, art, design, audio, production.
> **Scope:** *Project structure, conventions, source control, and workflows only.* No
> gameplay design, no lore, no code. For *system* design see
> [`TechnicalArchitecture.md`](TechnicalArchitecture.md); for creative direction see
> [`DesignBible.md`](DesignBible.md).

This is the studio documentation package, organized as the ten requested deliverables:

1. [Top-Level Project Structure](#1-top-level-project-structure)
2. [Content Folder Hierarchy (every folder explained)](#2-content-folder-hierarchy)
3. [Naming Convention Guide](#3-naming-convention-guide)
4. [Asset Prefix Guide](#4-asset-prefix-guide)
5. [Source Control Rules](#5-source-control-rules)
6. [Team Collaboration Rules](#6-team-collaboration-rules)
7. [Content Pipeline Rules](#7-content-pipeline-rules)
8. [Region Development Workflow](#8-region-development-workflow)
9. [Boss Development Workflow](#9-boss-development-workflow)
10. [Long-Term Scalability Plan & AAA Best Practices](#10-long-term-scalability--aaa-best-practices)

**The seven structural laws** (everything below enforces these):

1. **Everything has a place** — there is exactly one correct folder for any asset.
2. **No duplication** — shared assets live in a shared location and are referenced, never copied.
3. **Systems are separated from content** — code in `Source/`/`Plugins/`, content in `Content/`.
4. **Content is separated from code** — designers never need the compiler to add content.
5. **Regions are separated from gameplay systems** — a region is self-contained and removable.
6. **Bosses are fully modular** — one self-contained folder per boss.
7. **Future-proof** — DLC and new features attach as Game Feature plugins without restructuring.

---

## 1. Top-Level Project Structure

```
HollowCrown/
├── HollowCrown.uproject        Project descriptor (modules, plugins)
├── Source/                     C++ — primary game module + target rules
│   ├── HollowCrown/             Thin primary game module (boot/target glue)
│   ├── HollowCrown.Target.cs
│   └── HollowCrownEditor.Target.cs
├── Plugins/                    All code & feature plugins (the real systems)
│   ├── System/                  Code-only systems (Layers 1–3 of the architecture)
│   │   ├── HCCore/  HCAbilities/  HCWorldState/  HCPersistence/  HCContent/
│   │   ├── HCCombat/  HCInventory/  HCEquipment/  HCCrafting/  HCAI/
│   │   ├── HCWeather/  HCDialogue/  HCQuest/  HCFaction/  HCReputation/
│   │   ├── HCCorruption/  HCEconomy/  HCAudioCore/  HCUI/
│   └── GameFeatures/            Game Feature plugins (code + their own Content)
│       ├── HCPlayer/  HCEnemy/  HCBoss/  HCSettlement/  HCBuilding/
│       ├── HCRegion_WeepingMoors/        (region as a feature)
│       └── HCRegion_Blackwood/ …         (DLC pattern — added later)
├── Content/                    Shared/base-game content (see §2)
├── Config/                     .ini configuration (Default*, per-platform)
│   ├── DefaultEngine.ini  DefaultGame.ini  DefaultInput.ini  DefaultEditor.ini
│   ├── Tags/ (GameplayTag .ini sources)  Localization/
│   └── Windows/  Linux/  … (per-platform overrides)
├── Saved/                      LOCAL ONLY — never committed (logs, autosaves, crash)
├── Intermediate/  Binaries/  DerivedDataCache/   LOCAL ONLY — never committed
├── Build/                      Packaging scripts, platform build resources, install dirs
├── Documentation/  (→ Docs/)   Design bible, architecture, this document, system docs
├── Tools/                      Standalone tooling (Python/C#: validators, importers)
├── Automation/                 CI/CD: build graph, test suites, asset-validation jobs
└── .gitignore  .gitattributes  README.md  CLAUDE.md
```

**What each top-level directory is for**

| Dir | Purpose | Source control |
|-----|---------|----------------|
| `Source/` | The thin primary game module only; all real systems live in `Plugins/`. | Tracked (text). |
| `Plugins/System/` | Code-only systems (no/minimal content) — the architecture's Layer 1–3 modules. | Tracked. |
| `Plugins/GameFeatures/` | Self-contained features that carry their **own** `Content/` and can be enabled/shipped as DLC. | Tracked (code text + LFS for content). |
| `Content/` | Shared and base-game content authored in-editor. | Tracked via **LFS** (binary). |
| `Config/` | All `.ini` configuration; gameplay tags sourced here; per-platform overrides. | Tracked (text). |
| `Saved/`, `Intermediate/`, `Binaries/`, `DerivedDataCache/` | Generated/local. | **Ignored.** |
| `Build/` | Packaging/build resources, signing, platform installers. | Tracked (text + small binaries via LFS). |
| `Documentation/` (this repo: `Docs/`) | All living documentation. | Tracked (text). |
| `Tools/` | Editor-external utilities (asset auditors, naming linters, import scripts). | Tracked. |
| `Automation/` | CI graph, automated tests, asset validation, nightly cooks. | Tracked. |

> **Code/content split is physical, not conventional.** Systems are plugins under
> `Plugins/`; content is under `Content/` or inside a feature plugin's own `Content/`.
> Nothing else may sit at the top level.

---

## 2. Content Folder Hierarchy

Base-game/shared content. **Mirror this layout inside any Game Feature plugin's own
`Content/`** so a region/feature is internally identical and self-contained.

```
Content/
├── Core/                  Project-wide, content-side framework assets
│   ├── Framework/          BP_GameMode_*, BP_GameInstance, BP_GameState, BP_PlayerController
│   ├── Subsystems/         Designer-facing config DA_ for subsystems (weather, economy…)
│   ├── Tags/               GameplayTag tables/docs (authoritative source is Config/Tags)
│   ├── GlobalData/         Project-wide DA_ singletons (DA_GameSettings, DA_DamageTypes)
│   ├── Input/              IMC_* (mapping contexts), IA_* (input actions), DA_InputConfig
│   ├── SaveSystem/         Save-related DA_/BP (slot config, save UI hooks)
│   └── MPC/                Material Parameter Collections (MPC_Weather, MPC_Corruption)
│
├── Characters/            Friendly & neutral humans (the player + NPC kit)
│   ├── Player/             Crownless: Mesh/ ABP_/ Materials/ AbilitySets/ BP_PlayerCharacter
│   ├── Shared/             Base BP_NPCBase, shared skeletons, shared montage sets
│   ├── NPCs/               Generic populace
│   │   ├── Citizens/  Merchants/  Guards/  Companions/  Vendors/  QuestCharacters/
│   ├── Animation/          Shared human AnimBP, linked layers, montages, Control Rig
│   ├── Data/               DA_NPCProfile_* , DA_NPCAppearance_*
│   └── Voice/              VO_*  dialogue/bark audio (or referenced from Audio/)
│
├── Enemies/               Hostiles (non-boss)
│   ├── Shared/             BP_EnemyBase, shared StateTrees, shared perception/EQS, shared SFX
│   │   ├── AI/  (ST_/BT_/BB_/EQS_ shared)   Animation/   Audio/   Data/ (archetype base)
│   ├── Wildlife/  Bandits/  Cultists/  Undead/  Monsters/
│   ├── Elite/              Empowered variants (data-driven where possible)
│   └── MiniBosses/         Encounter mini-bosses (lighter than the 12 majors)
│        each type → Mesh/ ABP_/ AI/ Audio/ Data/ (DA_EnemyArchetype) BP_Enemy_<Name>
│
├── Bosses/                The 12 majors — one fully self-contained folder each (§9)
│   ├── _Shared/            BP_BossBase content, shared boss UI/VFX/audio conventions
│   ├── BellKeeper/         Blueprints/ Animations/ Abilities/ Audio/ VFX/ Data/ UI/ Arena/ Cutscenes/
│   ├── BlackStag/          (same internal layout)
│   ├── SaintEleanor/  DrownedKing/  ChoirOfThorns/  …
│
├── World/                 Cross-region world systems & shared environment kit
│   ├── Landscapes/         Landscape layers, layer blends, RVT
│   ├── Foliage/            Foliage types, procedural foliage spawners
│   ├── Weather/            DA_WeatherProfile_*, DA_SeasonProfile_*, weather Niagara
│   ├── WorldState/         DA_ for world-state defaults, region-unlock graphs
│   ├── WorldEvents/        Reusable world-event definitions
│   ├── POI/                Reusable point-of-interest blueprints/kits
│   └── EnvironmentKits/    Shared modular kits: Dungeons/ Villages/ Castles/ Churches/
│                           Roads/ Rivers/ (meshes+materials shared across regions)
│
├── Regions/               One self-contained folder per region (§8) — usually a Feature plugin
│   ├── WeepingMoors/       Environment/ Props/ NPCs/ Quests/ Audio/ Lighting/ Weather/ Maps/
│   ├── Blackwood/  Ashbourne/  DrownedKingdom/  SilentCathedral/  HollowCapital/
│
├── Items/                 Everything carryable
│   ├── _Definitions/       DA_Item_* (the data — Weapons/ Armor/ Consumables/ Resources/
│   │                       Materials/ QuestItems/ Legendary/) — definitions kept together
│   ├── Weapons/            Meshes/ Materials/ Animations (weapon-specific) per class
│   ├── Armor/              Meshes/ Materials (modular armor pieces)
│   ├── Icons/              T_Icon_* (UI icons, shared atlas-friendly)
│   └── Consumables/  Resources/  Crafting/  (meshes/FX for in-world pickups)
│
├── Building/              Player construction kit (settlement build pieces)
│   ├── _Definitions/       DA_BuildingPiece_*
│   ├── Foundations/  Walls/  Roofs/  Doors/  Windows/  Towers/  Decorations/
│   ├── CastlePieces/       Higher-tier modular castle set
│   └── Settlement/         Settlement-level props, signage, plot markers
│
├── Settlement/            Settlement simulation content (non-building)
│   ├── Data/               DA_SettlementProfile_*, resource/event tables
│   └── UI/                 Settlement-management widget content
│
├── Animation/             Project-wide animation assets not owned by one character
│   ├── Shared/  MotionMatching/ (pose search DBs)  Montages/  ControlRig/  IK/  StateMachines/
│
├── Audio/                 All sound (see §2 Audio note)
│   ├── Music/  Ambient/  Weather/  Combat/  Bosses/  Creatures/  UI/
│   ├── Voices/             NPC/  Player/  Narrator/
│   ├── MetaSounds/         MS_* sources & patches
│   └── Mix/                Submixes, AudioModulation buses, mix snapshots
│
├── FX/                    Niagara & visual effects
│   ├── Combat/  Weather/  Boss/  Environment/  GameplayCues/ (GC_-driven NS_)
│
├── Materials/             Shared materials & material functions
│   ├── Master/             M_* master materials   Functions/ MF_*   Layers/
│   └── PostProcess/        PP materials (corruption, damage, weather)
│
├── Textures/              Shared textures not owned by one mesh (decals, noise, gradients)
│
├── Meshes/                Shared static meshes not owned by a region/kit (global props)
│
├── UI/                    User interface (see §UI)
│   ├── HUD/  Menus/  Inventory/  Crafting/  Dialogue/  Map/  QuestLog/  Settlement/  BossUI/
│   ├── Widgets/            WBP_ shared/base widgets, common components
│   ├── Styles/             Common UI styles, brushes, themes
│   ├── Icons/              T_Icon_* (UI), Fonts/
│
├── Quests/                Quest DATA only (structure, no narrative authored here in this doc)
│   └── _Definitions/       DA_Quest_*, objective assets
│
├── Dialogue/              Dialogue graphs + string tables
│   └── _Graphs/  Strings/
│
├── Cinematics/            Sequencer-driven content
│   ├── Intro/  BossCutscenes/  WorldEvents/  Endings/
│   ├── Sequences/          LS_* Level Sequences   Cameras/ (camera rigs/shots)   Tracks/ (VO)
│
├── Data/                  Cross-cutting data tables & data assets (the data spine)
│   ├── DataTables/         DT_* (loot, prices, balancing, recipes)
│   ├── DataAssets/         DA_* not owned by a single system folder
│   ├── Balancing/          Tuning tables (one change at a time, reviewed)
│   ├── LootTables/  NPCData/  BossData/  QuestData/  SettlementData/
│   └── Localization/       String tables, culture data
│
├── Developer/             Per-user sandboxes — NEVER shipped, NEVER referenced by game
│   ├── <username>/         Personal experiments (UE "Developer Folders" enabled)
│   ├── Prototypes/         Shared prototype systems pending promotion
│   └── Temp/               Scratch assets (auto-flagged by validation)
│
├── Testing/               Automation & QA content
│   ├── Maps/               L_Test_* gym/stress maps
│   ├── FunctionalTests/    Automated functional test actors/maps
│   └── DebugTools/         Debug/profiling actors & widgets (cooked only in dev configs)
│
└── _DevMaps/  L_Persistent, L_Startup, L_FrontEnd  (top-level maps live here or /Maps)
```

**Folder rationale (the rules made concrete):**

- **`_`-prefixed folders sort to the top** (`_Shared`, `_Definitions`, `_DevMaps`) — shared/source-of-truth content is found first.
- **Definitions live together, art lives by type.** `DA_Item_*` sit in `Items/_Definitions/`; the meshes/icons they soft-reference live in `Items/Weapons/…`, `Items/Icons/…`. This prevents duplication and lets data exist before art.
- **`Developer/` and `Testing/` are quarantined** and validated to never be referenced by shippable content (a CI check, §7).
- **Shared-vs-owned is explicit:** anything used by more than one region/character/boss goes to a `Shared`/`World/EnvironmentKits` location and is referenced; nothing is copied.

---

## 3. Naming Convention Guide

**General rule:** `Prefix_Category_Descriptor_Variant_Suffix`, PascalCase, no spaces, no
double underscores (except engine-reserved `__ExternalActors__`), ASCII only.

| Asset | Pattern | Example |
|-------|---------|---------|
| Blueprint class | `BP_<Name>` | `BP_PlayerCharacter`, `BP_BellKeeper` |
| Blueprint (component) | `BP_<Name>Component` | `BP_InteractionComponent` |
| Animation Blueprint | `ABP_<Name>` | `ABP_Player`, `ABP_BellKeeper` |
| Widget Blueprint | `WBP_<Name>` | `WBP_Inventory`, `WBP_BossHealthBar` |
| Data Asset | `DA_<System>_<Name>` | `DA_Weapon_IronSword`, `DA_Boss_BellKeeper` |
| Data Table | `DT_<Name>` | `DT_LootTable_Moors`, `DT_CraftingRecipes` |
| Gameplay Ability / Effect / Cue | `GA_ / GE_ / GC_<Name>` | `GA_HeavyAttack`, `GE_Bleed`, `GC_Impact_Flesh` |
| Ability Set | `AS_<Name>` | `AS_GreatswordMoveset`, `AS_Corruption_Stage3` |
| StateTree / BT / Blackboard / EQS | `ST_ / BT_ / BB_ / EQS_<Name>` | `ST_BanditBrain`, `BT_BanditPatrol`, `BTT_AttackTarget`, `BB_Enemy` |
| Static / Skeletal Mesh | `SM_ / SK_<Name>_<Variant>` | `SM_CastleWall_A`, `SK_BellKeeper` |
| Material / Instance / Function | `M_ / MI_ / MF_<Name>` | `M_StoneWall`, `MI_StoneWall_Wet`, `MF_Weathering` |
| Material Param Collection | `MPC_<Name>` | `MPC_Corruption` |
| Texture (by channel) | `T_<Name>_<Type>` | `T_StoneWall_D` (Diffuse/BaseColor), `_N` normal, `_ORM`, `_M` mask |
| Niagara System / Emitter | `NS_ / NE_<Name>` | `NS_BloodMoonFog`, `NS_BellShockwave` |
| MetaSound / Sound Cue / Wave | `MS_ / SC_ / SFX_ / VO_ / MX_` | `SFX_BellKeeper_Roar`, `VO_Merchant_Greeting`, `MX_Combat` |
| Level / Level Sequence | `L_ / LS_<Name>` | `L_WeepingMoors`, `LS_BellKeeper_Phase2` |
| Control Rig / IK Rig / Pose Search | `CR_ / IK_ / PSD_<Name>` | `CR_HumanFoot`, `IK_Player`, `PSD_PlayerLocomotion` |
| Curve / Anim Montage / Sequence | `Curve_ / AM_ / AS_*`* | `AM_Greatsword_Light_01` |

\* Anim **Sequence** uses `A_` or the imported clip name with an `A_` prefix; **Montage** uses `AM_`. (`AS_` is reserved here for Ability Sets; montages never use `AS_`.)

**Folder naming:** PascalCase, singular system / plural collection (`Boss/BellKeeper`,
`Enemies/Bandits`). `_Shared`/`_Definitions` for shared/source nodes.

---

## 4. Asset Prefix Guide

Single source of truth for prefixes (a CI linter enforces it, §7). Grouped by domain:

| Domain | Prefixes |
|--------|----------|
| **Blueprints/Logic** | `BP_` blueprint · `ABP_` anim BP · `WBP_` widget · `BPI_` blueprint interface · `BPFL_` function library · `BPC_` component |
| **GAS** | `GA_` ability · `GE_` effect · `GC_` cue · `AS_` ability set · `GAT_`/Config-sourced gameplay tags |
| **AI** | `ST_` StateTree · `BT_` behavior tree · `BTT_` BT task · `BTD_` BT decorator · `BTS_` BT service · `BB_` blackboard · `EQS_` query · `SO_` smart object |
| **Data** | `DA_` data asset · `DT_` data table · `CT_` curve table · `PDA_` primary data asset (when distinction matters) |
| **Meshes** | `SM_` static · `SK_` skeletal · `GC_`→ avoid clash: geometry collection = `GEO_` · `PCG_` procedural graph |
| **Materials** | `M_` material · `MI_` instance · `MF_` function · `MPC_` param collection · `ML_` material layer · `MLB_` layer blend |
| **Textures** | `T_` texture (`_D/_BC` basecolor, `_N` normal, `_ORM`, `_M` mask, `_E` emissive, `_H` height) · `RT_` render target · `MT_`/VT virtual texture |
| **FX** | `NS_` Niagara system · `NE_` Niagara emitter · `NM_` Niagara module · `PFX_`/legacy cascade (avoid) |
| **Audio** | `MS_` MetaSound · `SC_` sound cue · `SFX_` SFX wave · `VO_` voice · `MUS_` music · `AMB_` ambient · `MX_` submix/mix · `ATT_` attenuation · `MOD_` modulation |
| **Animation** | `A_` sequence · `AM_` montage · `BS_` blendspace · `CR_` control rig · `IK_` IK rig/retarget · `PSD_` pose search DB · `ANO_` anim notify |
| **World** | `L_` level · `LS_` level sequence · `LI_` level instance · `DL_` data layer asset · `HLOD_` HLOD setup · `LSC_` landscape |
| **UI** | `WBP_` widget · `T_Icon_` icon · `F_`/`Font_` font · `WS_` widget style |

> Conflict policy: a prefix means exactly one type. The one historical clash is `GC_`
> (GameplayCue) vs geometry collection — **geometry collections use `GEO_`** to keep `GC_`
> unambiguous.

---

## 5. Source Control Rules

The project is large and binary-heavy; both supported VCS paths are documented. **Default
today: Git + Git LFS + file locking.** At larger team size, **migrate to Perforce.**

### Git + Git LFS (current / indie–AA)

- **LFS-tracked binaries** (in `.gitattributes`): `*.uasset *.umap *.upk` plus media
  (`*.png *.tga *.jpg *.exr *.wav *.mp3 *.m4a *.fbx *.ttf *.bin`). Never store these as
  plain git blobs.
- **File locking is mandatory** for binary assets (`git lfs lock`/`unlock`). `.uasset`/
  `.umap` cannot be merged — locking prevents two people editing the same asset. Configure
  lockable patterns in `.gitattributes` (`*.uasset lockable`).
- **`.gitignore`** excludes: `Binaries/ Build/ DerivedDataCache/ Intermediate/ Saved/`
  and IDE files. **Do NOT ignore** `Content/__ExternalActors__/` and
  `__ExternalObjects__/` (One File Per Actor data) — these **must** be committed.
- **Commit discipline:** small, described, coherent commits; never commit a non-compiling
  state to `main`; run asset validation (§7) before push.

### Perforce (recommended at scale / full team)

- Typed file mappings: `.uasset/.umap` as `binary+l` (exclusive checkout = locking).
- Streams: `//hollowcrown/main`, `//hollowcrown/dev`, per-feature streams; release streams per milestone.
- `p4ignore` mirrors the git ignore set; DDC and Intermediate never submitted.
- UnrealGameSync (UGS) for binary build distribution to non-engineers.

### Branch / stream strategy

```
main (always shippable, protected, CI-gated)
 └── dev (integration; nightly cook + automation must pass)
      ├── feature/<system-or-region>      short-lived, rebased, squash-merged
      ├── region/<RegionName>             region teams isolate WIP environment work
      └── boss/<BossName>                 boss work isolated (self-contained folder helps)
release/<milestone>                       stabilization branches; cherry-pick fixes
```

- Trunk-biased: branches are **short-lived**; long-running divergence on binary assets is
  the #1 cause of unmergeable conflicts.
- **Folder/asset locking** beats merging for binaries: lock the asset you edit, commit,
  unlock. Coordinate large map edits via Level Instances / OFPA so two people rarely touch
  the same file.
- **Redirector hygiene:** fix up redirectors before commit (never leave dangling); renames
  are deliberate, reviewed actions.
- **Versioning:** semantic project version in `Config/DefaultGame.ini`
  (`ProjectVersion`); milestone tags `v0.x` on `release/*`; save-format version is
  independent (see Save architecture).

---

## 6. Team Collaboration Rules

- **Ownership map:** each top-level system plugin and each region/boss folder has a named
  owner (a `CODEOWNERS` file routes reviews). Cross-cutting changes (Core, Data spine)
  require the owning lead's review.
- **One asset, one editor at a time** — enforced by locking. Announce long locks.
- **Level work uses Level Instances + OFPA/Data Layers** so environment, lighting, and
  population can be edited by different people in parallel without touching one `.umap`.
- **No work in another person's `Developer/<user>/`**; promotion out of `Developer/` is a
  reviewed move into the proper folder with naming fixed up.
- **Designers stay in content & data** (Blueprints, Data Assets, StateTrees); engineers own
  C++ plugins. A designer never needs a compile to add an item/enemy/recipe.
- **Definition-first authoring:** create the `DA_`/`DT_` row first (it can ship greyboxed),
  then art fills the soft references — unblocks parallel work.
- **Naming/prefix linter and asset validator run pre-commit and in CI**; a red validation
  blocks merge. Conventions are not optional.
- **Documentation lives with the change:** a new system/region/boss updates its doc in
  `Docs/` in the same PR.

---

## 7. Content Pipeline Rules

- **Asset Manager is the gatekeeper.** Every shippable content category is a registered
  **Primary Asset Type** (`DA_Item`, `DA_Boss`, `DA_EnemyArchetype`, `DA_BuildingPiece`,
  `DA_Quest`, …). Discovery, async loading, and DLC all flow through it. Heavy assets
  (meshes, audio, VFX) are **always soft references** — UI/data never hard-load them.
- **Import standards:** source art (FBX/PSD/WAV) lives outside the engine project in an art
  depot or `Art/` source tree; only engine-ready assets enter `Content/`. Texture sizes are
  power-of-two; budgets per category (§10). Naming/prefix applied on import.
- **No content in `Developer/` or `Testing/` may be referenced by shippable assets** —
  enforced by a CI **reference-validation** pass (and the editor's "Audit Assets").
- **No cross-region hard references** except through `World/EnvironmentKits` and `Core` —
  a region must be deletable. CI validates region folders only reference shared/world/core
  or their own content.
- **Redirector & duplicate checks** in CI: fail on dangling redirectors and on duplicate
  assets (same content, two paths).
- **Validation suite** (Automation/): naming/prefix lint, missing-reference scan,
  texture-budget scan, nanite/LOD presence, lightmap/collision presence, "no `Developer`
  refs", primary-asset rule compliance. Runs pre-commit (fast subset) and nightly (full).
- **Cook & smoke nightly:** a nightly cook of `dev` plus automated functional tests on the
  gym maps; broken cook blocks promotion to `main`.

---

## 8. Region Development Workflow

A region is a **self-contained, removable unit** — ideally a Game Feature plugin
(`HCRegion_<Name>`) carrying its own mirrored `Content/`. Internal layout:

```
Regions/<RegionName>/   (or Plugins/GameFeatures/HCRegion_<Name>/Content/)
├── Maps/               L_<Region>_Persistent + World Partition cells
├── Environment/        Region-specific meshes/materials NOT in shared kits
├── Props/              Region set dressing
├── NPCs/               Region population (DA_NPCProfile_*, placed via Data Layers)
├── Quests/             Region quest DATA
├── Audio/              Region ambient banks, music states
├── Lighting/           Sky/PP/lighting scenarios per Data Layer
├── Weather/            Region climate-zone overrides (DA_WeatherProfile refs)
├── WorldPartition/     Data Layers (runtime + editor), HLOD setup, grid config
└── Streaming/          Streaming sources, level instances, cell tuning
```

**Workflow:**
1. **Greybox** the region in a fresh World Partition map with HLOD enabled and OFPA on.
2. Define **Data Layers** early: gameplay variants (pre/post-boss world-state), and
   editor layers for team parallelism (terrain / props / lighting / population owned by
   different people).
3. Build the environment from **shared `World/EnvironmentKits`** first; only region-unique
   assets go in the region folder (law 2: no duplication).
4. Population & quests are **data + Data-Layer placement**; the region references shared
   character/enemy kits, never copies them.
5. Wire region unlock to **World-State** (region is gated by a flag; streaming activates on
   `OnWorldStateChanged`).
6. **Validate isolation:** CI confirms the region references only shared/world/core + its
   own content. The region must be removable without breaking the base game.
7. Performance pass to budget (streaming, HLOD, significance) before sign-off.

> **Why it scales:** because a region only depends *downward* on shared kits and core, six
> regions (and DLC regions) are developed by independent teams in parallel and shipped
> incrementally as Game Feature plugins.

---

## 9. Boss Development Workflow

Every boss is **one fully self-contained folder** under `Bosses/<Name>/` (or a boss
feature plugin for DLC bosses), inheriting `BP_BossBase` (which derives the C++
`AHCBossBase`). Internal layout (the requested structure):

```
Bosses/<BossName>/
├── Blueprints/     BP_<Boss>, phase/component BPs
├── Animations/     A_/AM_ (attacks, phase transitions), ABP_<Boss>
├── Abilities/      GA_/GE_/GC_ + AS_<Boss>_Phase1/2 (ability sets per phase)
├── Audio/          SFX_<Boss>_*, MUS_<Boss> (phase music states)
├── VFX/            NS_<Boss>_* (telegraphs, signature effects)
├── Data/           DA_Boss_<Name> (phases, the four death guarantees, rewards)
├── UI/             WBP_<Boss>_HealthBar / name plate overrides
├── Arena/          AHCBossArena setup, bounds, fog wall, camera, level instance
└── Cutscenes/      LS_<Boss>_Intro / _PhaseX / _Death
```

**Workflow:**
1. Author **`DA_Boss_<Name>`** first (phases, ability sets per phase, arena ref, and the
   four death guarantees: world-state id, granted ability set, corruption reward, regions
   to unlock, reward loot). The boss can be greyboxed from data alone.
2. Build **phase StateTrees** + per-phase **ability sets** (mechanics are abilities/Niagara,
   never bespoke classes).
3. Set up the **arena** (trigger, bounds, music state, camera) as a Level Instance the
   region references.
4. Hook **cutscenes** via Level Sequences triggered by phase tags.
5. Confirm the **death pipeline**: defeating the boss reports to World-State, which grants
   the ability set + corruption, sets the dead flag, unlocks regions, and broadcasts the
   world change. The framework handles this — the boss only supplies data.
6. Validate isolation (boss folder references shared boss content + core/world kits only)
   and performance (arena is its own budget).

> **Why this structure scales:** a boss is added with **zero new engineering** once the
> framework exists — it is data + StateTrees + montages + a folder. Twelve bosses are twelve
> folders, individually owned, individually removable, with no shared mutable code.

---

## 10. Long-Term Scalability & AAA Best Practices

**How the structure survives multi-year scale**

| Pressure | Why the structure holds |
|----------|--------------------------|
| 100+ NPCs | NPC profiles are data; population is Data-Layer placement; crowds are Mass (no per-NPC folders). |
| 50+ enemy types | One `Enemies/<Faction>/<Type>/` folder per type, all over `Enemies/Shared`; behaviour is data. |
| 12 bosses | 12 self-contained `Bosses/<Name>/` folders, each owned, each removable. |
| Thousands of assets | Strict one-place rule + Asset Manager + soft references + duplicate/redirector CI keep the tree navigable. |
| Large open regions | Regions are isolated Game Feature plugins with their own Content; World Partition + Data Layers + HLOD. |
| Multiple years | Conventions enforced by CI from day one; documentation lives with code; ownership map prevents drift. |
| DLC / expansion | New region/boss = new Game Feature plugin + new Primary Data Assets; activated at runtime; touches no shipped folders. |

**AAA production best practices (the non-negotiables)**

1. **Conventions are enforced, not suggested** — a naming/prefix/reference linter gates every commit.
2. **Asset Manager + soft references everywhere** — nothing hard-loads heavy content; this is the memory and DLC backbone.
3. **OFPA + World Partition + Data Layers + Level Instances** from day one — the only way large maps stay collaborative.
4. **Binary assets are locked, not merged** — locking workflow is mandatory; long branches on binaries are forbidden.
5. **Developer/Testing content is quarantined and CI-verified** to never reach a cook.
6. **Definition-first, art-second** — data assets exist before art, so design/engineering/art proceed in parallel.
7. **One owner per system/region/boss** — `CODEOWNERS` routes review; cross-cutting edits need lead sign-off.
8. **Nightly cook + automated functional tests** on gym maps; a broken cook blocks promotion.
9. **Budgets are tracked continuously** (Insights, LLM tags, dev HUD) and enforced as gates (see [`TechnicalArchitecture.md`](TechnicalArchitecture.md) §9).
10. **Documentation is part of "done"** — every new system/region/boss updates `Docs/` in the same change.

---

*This document defines where things live and how the team works. It is intentionally
silent on what the things are — that is the Design Bible's and the Technical
Architecture's job.*
