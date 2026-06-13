# Regions/WeepingMoors/ — region folder template

The reference layout for a **self-contained, removable** region. Copy this shape for every
region; the workflow is [`Docs/ProjectStructure.md`](../../../Docs/ProjectStructure.md) §8.
At scale a region is promoted to a Game Feature plugin (`HCRegion_WeepingMoors`) carrying
its own mirrored `Content/`.

| Folder | Holds |
|--------|-------|
| `Maps/` | `L_WeepingMoors_Persistent` + World Partition cells |
| `Environment/` | Region-unique meshes/materials **not** in `World/EnvironmentKits` |
| `Props/` | Region set dressing |
| `NPCs/` | Region population (`DA_NPCProfile_*`, placed via Data Layers) |
| `Quests/` | Region quest **data** |
| `Audio/` | Region ambient banks & music states |
| `Lighting/` | Sky/PP/lighting scenarios per Data Layer |
| `Weather/` | Region climate-zone overrides |
| `WorldPartition/` | Data Layers (runtime + editor), HLOD setup, grid config |
| `Streaming/` | Streaming sources, level instances, cell tuning |

**Isolation rule (CI-enforced):** a region references only `World/EnvironmentKits`,
`Core`, shared character/enemy/boss kits, and its **own** content — never another region.
It must be deletable without breaking the base game. That is what lets six regions (and DLC
regions) be built in parallel and shipped incrementally.
