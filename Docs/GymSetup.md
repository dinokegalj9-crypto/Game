# Combat Gym — Setup Guide

> **Goal:** get a player fighting a basic enemy in a foggy gym so you can iterate on **deflect
> feel** — the one question the whole project rests on
> ([`FeasibilityAnalysis.md`](FeasibilityAnalysis.md) §13.2, [`VerticalSliceProduction.md`](VerticalSliceProduction.md) §14).
> **Prereqs:** UE 5.7 + Visual Studio (C++), the project builds (resolve M0 first-compile
> fixups). This uses the C++ classes already in `Source/HollowCrown/`, plus the gym glue added
> for you: `UHCMeleeAttackNotifyState`, `AHCEnemyBase`, `AHCEnemyController`.

Do these in order. Most of it is data/Blueprint setup — little or no new code.

## 1. Build & open
- Right-click `HollowCrown.uproject` → *Generate Visual Studio project files* → open the `.sln`.
- Build **Development Editor / Win64**. Fix any first-compile errors (expected, M0). Launch.

## 2. Input (Enhanced Input)
- Create under `Content/Core/Input/`:
  - **Input Mapping Context** `IMC_Default`.
  - **Input Actions:** `IA_Move` (Axis2D), `IA_Look` (Axis2D), `IA_LightAttack`, `IA_Heavy`,
    `IA_Block`, `IA_Dodge`, `IA_Sprint`, `IA_Interact` (all Digital/bool).
- In `IMC_Default`, map keys: WASD→Move (with the standard 2D-vector modifiers), Mouse XY→Look,
  LMB→LightAttack, RMB→Heavy, Q→Block, Space→Dodge, Shift→Sprint, E→Interact (plus gamepad).

## 3. Player
- **BP_PlayerCharacter** from `AHCCharacter` (`Content/Characters/Player/`): set the **Skeletal
  Mesh** (UE Manny is fine for the gym) and an **Anim Blueprint** with basic locomotion.
- Select its **Combat** component → set **Equipped Weapon** = `DA_Sword` (made in step 5).
- **BP_PlayerController** from `AHCPlayerController`: assign `DefaultMappingContext = IMC_Default`
  and each `MoveAction/LookAction/LightAttackAction/...` to the matching `IA_*`.

## 4. Game Mode
- **BP_HCGameMode** from `AHCGameMode` (defaults to the HC pawn/controller in C++). Set its
  Default Pawn = `BP_PlayerCharacter`, Player Controller = `BP_PlayerController`.
- In the gym map's **World Settings → GameMode Override**, set `BP_HCGameMode`.

## 5. Weapon data
- **DA_Sword** = a `UHCWeaponData` (`Content/Items/Weapons/`): set damage/stamina/poise values
  and **Reach** (~180). Assign the montages from step 6 once they exist.

## 6. Attack montages + the hit window (the key step)
- Make **Anim Montages** from attack animations (acquired/Mixanmo): `AM_Sword_Light_01`,
  `AM_Sword_Heavy`, etc.
- In each montage, add the **"HC Melee Attack Window"** notify *state* (it's
  `UHCMeleeAttackNotifyState`) spanning the frames where the blade connects. It calls
  `OnAttackWindowOpen/Close` on the owner's combat component — i.e. the **weapon trace only
  happens during this window.** No montage = no damage.
- Assign the montages into `DA_Sword` (`LightComboMontages[0]`, `HeavyMontage`, …).

## 7. Enemy (the punching bag that fights back)
- **BP_Enemy** from `AHCEnemyBase` (`Content/Enemies/`): set Skeletal Mesh + Anim BP; set
  **DefaultWeapon** = `DA_Sword` (or a `DA_EnemyWeapon`). It is auto-possessed by
  `AHCEnemyController` (approach → face → attack on cooldown — no NavMesh needed).
- Give the enemy at least one attack montage with the hit-window notify so *it* can damage you.

## 8. The gym map
- `Content/Testing/Maps/L_Test_CombatGym`: flat floor, a **Player Start**, a couple of
  `BP_Enemy` placed, an **Exponential Height Fog** (+ volumetric) for the mood. Set the GameMode
  override (step 4). Hit **Play**.

## 9. Iterate deflect feel (the actual work)
Tune until deflecting *feels great* — this is Phase 1's gate:
- Deflect **timing window** (start ~90–120 ms; see `CombatDesign.md` §5).
- **Hit-stop** on deflect/hit (brief global or per-actor time dilation).
- **Spark VFX** (Niagara) + **metallic ring SFX** at the contact point.
- **Camera** kick/shake; **controller haptics**.
- Enemy **telegraph** readability (wind-up pose/timing).

When a tester says *"deflecting feels good,"* Phase 1 is done — proceed to the
[Vertical Slice blueprint](VerticalSliceProduction.md).

---

### Notes
- **Damage flow:** player attack → montage hit-window notify → `UHCCombatComponent` weapon trace
  (sphere sweep on the Pawn channel) → target's combat/attribute components apply block/parry then
  health/poise. Both player and enemy carry these components, so it works both ways.
- **The enemy AI is intentionally minimal** (direct movement, no NavMesh) so the gym runs with zero
  navigation setup. Replace with a StateTree + AI Perception + EQS on a NavMesh for production
  (`Docs/Systems/NPCSystem.md`).
- **No GAS in the gym** — the slice uses the component-based combat already in the repo
  (`FeasibilityAnalysis.md` §12). GAS migration is deferred.
