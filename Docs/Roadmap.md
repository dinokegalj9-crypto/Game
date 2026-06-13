# Roadmap

Milestones toward the Phase 1 vertical slice and beyond. Each milestone lists its exit
criteria — the slice is "done" when M4's criteria are met.

---

## M0 — Foundation *(current)*

The repository skeleton, engine configuration, design documentation, and C++ scaffolding
for the core systems.

**Exit criteria**
- [x] `.uproject`, `Config/`, `.gitignore`, `README`
- [x] Design Bible, Architecture, per-system docs
- [x] C++ headers + stubs for attributes, combat, corruption, survival, inventory, NPCs,
      settlement, weather, save, and core framework classes
- [ ] Project compiles in UE 5.6 against a local engine install

> The compile step is intentionally left open: it requires a local UE 5.6 installation,
> which is not available in this environment. The C++ is written to UE conventions so it
> compiles once dropped into the engine; treat any first-compile fixups as part of M0.

## M1 — Playable Character & Combat Core

- Third-person `AHCCharacter` with Enhanced Input.
- Attribute component driving health/stamina/poise with regen and a death state.
- Combat component: light/heavy/charged attacks, block, parry window, dodge, sprint,
  weapon trace hit detection, hit reactions, and the stagger/execution path.
- One greatsword and one sword moveset with placeholder animations.

**Exit criteria:** the player can fight and kill a basic enemy that fights back, with
stamina and poise mattering.

## M2 — Living Slice of the Weeping Moors

- A blocked-out Weeping Moors sub-level (World Partition) with fog and the twilight mood.
- Dynamic weather subsystem driving fog/rain transitions.
- One village with 4–6 NPCs using schedule components (sleep/eat/work/travel + fear).
- Inventory + crafting at a campfire; basic survival (food, rest).
- 3 side quests and 1 dungeon with a mini-boss.

**Exit criteria:** a player can explore, loot, craft, and complete the side content.

## M3 — The Bell Keeper & World Change

- The major boss (The Bell Keeper): unique mechanics, arena, and the four boss-death
  guarantees wired through `UHCWorldStateSubsystem`.
- Corruption component fully functional: gain on boss death, five visual stages, NPC fear
  reactions, one corruption-granted ability.
- Basic settlement: place campfire/tent/storage + one upgraded building; resident NPC.

**Exit criteria:** defeating the Bell Keeper visibly changes the world, advances
corruption, grants an ability, and opens a new area.

## M4 — Vertical Slice Polish

- Save/load across world-state, settlement, and player progression.
- Professional UI: HUD, inventory, dialogue, map (minimal markers), pause/options.
- Audio pass, color grading, performance pass (Lumen/Nanite settings), bug fixing.

**Exit criteria:** a polished, self-contained **60-minute** experience suitable as a Steam
demo — the Phase 1 target.

---

## Post-Slice (later phases)

- Regions 2–6 and their bosses.
- Full corruption endings and altered-ending logic.
- Faction AI and reputation.
- Settlement prosperity/collapse economy.
- Wildlife migration and the full living-world simulation.
- Migration of the ability layer onto the Gameplay Ability System (GAS).

---

## Working Agreement

- Every new gameplay system gets a doc under [`Systems/`](Systems) before or alongside its
  code.
- Every boss must satisfy the four guarantees in the Design Bible §7 before it is "done".
- Changes are kept on the designated feature branch and committed in coherent, described
  units.
