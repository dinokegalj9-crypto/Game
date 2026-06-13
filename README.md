# THE HOLLOW CROWN

> *"The world is not dying. It is becoming something else."*

A next-generation dark fantasy action RPG — open-world exploration, light survival,
kingdom building, meaningful choices, deep lore, and unforgettable boss encounters,
built in **Unreal Engine 5.6**.

This is not another generic survival game, and not another Souls clone. The goal is a
living world that feels ancient, mysterious, tragic, and believable — a kingdom trapped
beneath a dying sky.

---

## Project Status

**Phase:** Foundation / Pre-Vertical-Slice
**Engine:** Unreal Engine 5.6 (Lumen, Nanite, Chaos, World Partition)
**Language:** C++ core systems + Blueprint for designers
**Current version:** `0.1.0`

This repository currently contains the **technical foundation**: the project skeleton,
engine configuration, the canonical design documentation, and clean, documented C++
scaffolding for the core gameplay systems. Binary content (maps, meshes, materials,
animations) is authored in the Unreal Editor and tracked via Git LFS.

See [`Docs/Roadmap.md`](Docs/Roadmap.md) for what comes next.

---

## Repository Layout

```
HollowCrown.uproject     Unreal project descriptor
Config/                  Engine, game, and input configuration (.ini)
Docs/                    Design bible, architecture, per-system documentation
  DesignBible.md         The canonical creative vision
  Architecture.md        Technical architecture and module map
  Roadmap.md             Milestones toward the Phase 1 vertical slice
  Systems/               One document per gameplay system
Source/HollowCrown/      C++ game module
  Core/                  Game mode, instance, state
  Player/                Player character + controller
  Combat/                Heavy, grounded melee combat
  Corruption/            The signature corruption mechanic
  Stats/                 Shared attribute component (health, stamina, poise)
  Survival/              Food, rest, temperature, disease
  Inventory/             Items, inventory, crafting
  AI/                    NPCs with schedules; enemy & boss AI hooks
  Settlement/            Kingdom building
  World/                 Dynamic weather
  Save/                  Persistent world save system
```

## The Six Regions

1. **The Weeping Moors** — starting wetlands. Boss: *The Bell Keeper*
2. **Blackwood** — a living, shifting forest. Boss: *The Black Stag*
3. **Ashbourne** — a city buried in endless ash. Boss: *Saint Eleanor*
4. **The Drowned Kingdom** — a half-submerged civilization. Boss: *The Drowned King*
5. **The Silent Cathedral** — a city where sound attracts horror. Boss: *The Choir of Thorns*
6. **The Hollow Capital** — the birthplace of the corruption. The final king.

## Getting Started (developers)

1. Install **Unreal Engine 5.6** via the Epic Games Launcher.
2. Configure Git LFS before pulling binary content:
   ```
   git lfs install
   git lfs track "*.uasset" "*.umap"
   ```
3. Right-click `HollowCrown.uproject` → *Generate Visual Studio project files*.
4. Open the generated solution and build the `HollowCrown` editor target.
5. Launch `HollowCrown.uproject`.

## Documentation

Start with the [**Design Bible**](Docs/DesignBible.md) for the creative vision, then the
[**Architecture**](Docs/Architecture.md) for how the code is organized. Each system has a
dedicated document under [`Docs/Systems/`](Docs/Systems).
