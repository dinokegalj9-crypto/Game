// Copyright Hollow Crown Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HCTypes.generated.h"

// ---------------------------------------------------------------------------
// Shared gameplay enums and lightweight structs for The Hollow Crown.
// Keeping these in one place avoids circular dependencies between systems and
// gives Blueprints a single, stable vocabulary to bind against.
// ---------------------------------------------------------------------------

/** The five visual/narrative stages of corruption. See Docs/Systems/CorruptionSystem.md. */
UENUM(BlueprintType)
enum class EHCCorruptionStage : uint8
{
	Stage1_Human       UMETA(DisplayName = "Normal Human"),
	Stage2_DarkEyes    UMETA(DisplayName = "Darkened Eyes"),
	Stage3_Veins       UMETA(DisplayName = "Visible Veins"),
	Stage4_Monstrous   UMETA(DisplayName = "Monstrous Traits"),
	Stage5_Inhuman     UMETA(DisplayName = "Almost Inhuman")
};

/** Melee weapon classes. Each maps to a UHCWeaponData asset / moveset. */
UENUM(BlueprintType)
enum class EHCWeaponClass : uint8
{
	Sword       UMETA(DisplayName = "Sword"),
	Axe         UMETA(DisplayName = "Axe"),
	Spear       UMETA(DisplayName = "Spear"),
	Greatsword  UMETA(DisplayName = "Greatsword"),
	Hammer      UMETA(DisplayName = "Hammer"),
	Torch       UMETA(DisplayName = "Torch")
};

/** High-level combat attack inputs. */
UENUM(BlueprintType)
enum class EHCAttackType : uint8
{
	Light    UMETA(DisplayName = "Light Attack"),
	Heavy    UMETA(DisplayName = "Heavy Attack"),
	Charged  UMETA(DisplayName = "Charged Attack")
};

/** Internal combat state machine. See Docs/Systems/CombatSystem.md. */
UENUM(BlueprintType)
enum class EHCAttackState : uint8
{
	Idle       UMETA(DisplayName = "Idle"),
	Windup     UMETA(DisplayName = "Windup"),
	Active     UMETA(DisplayName = "Active"),
	Recovery   UMETA(DisplayName = "Recovery"),
	Blocking   UMETA(DisplayName = "Blocking"),
	Parrying   UMETA(DisplayName = "Parrying"),
	Dodging    UMETA(DisplayName = "Dodging"),
	Staggered  UMETA(DisplayName = "Staggered")
};

/** Dynamic weather states. See Docs/Systems/WeatherSystem.md. */
UENUM(BlueprintType)
enum class EHCWeatherType : uint8
{
	Clear         UMETA(DisplayName = "Clear Twilight"),
	Fog           UMETA(DisplayName = "Fog"),
	Rain          UMETA(DisplayName = "Rain"),
	Thunderstorm  UMETA(DisplayName = "Thunderstorm"),
	StrongWind    UMETA(DisplayName = "Strong Wind"),
	BloodMoon     UMETA(DisplayName = "Blood Moon")
};

/** Light-survival needs. See Docs/Systems/SurvivalSystem.md. */
UENUM(BlueprintType)
enum class EHCSurvivalNeed : uint8
{
	Food         UMETA(DisplayName = "Food"),
	Rest         UMETA(DisplayName = "Rest"),
	Temperature  UMETA(DisplayName = "Temperature"),
	Disease      UMETA(DisplayName = "Disease"),
	Injury       UMETA(DisplayName = "Injury")
};

/** How an NPC currently regards the player / nearby danger. */
UENUM(BlueprintType)
enum class EHCFearState : uint8
{
	Calm     UMETA(DisplayName = "Calm"),
	Uneasy   UMETA(DisplayName = "Uneasy"),
	Fearful  UMETA(DisplayName = "Fearful"),
	Fleeing  UMETA(DisplayName = "Fleeing")
};

/** A stable identifier for a major boss, used by the world-state pipeline. */
USTRUCT(BlueprintType)
struct FHCBossId
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Hollow Crown")
	FName Id = NAME_None;

	FHCBossId() = default;
	explicit FHCBossId(FName InId) : Id(InId) {}

	bool IsValid() const { return Id != NAME_None; }
	bool operator==(const FHCBossId& Other) const { return Id == Other.Id; }
};

FORCEINLINE uint32 GetTypeHash(const FHCBossId& BossId)
{
	return GetTypeHash(BossId.Id);
}
