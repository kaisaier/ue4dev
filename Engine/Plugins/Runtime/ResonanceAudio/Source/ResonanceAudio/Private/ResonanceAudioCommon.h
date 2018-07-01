//
// Copyright Google Inc. 2017. All rights reserved.
//

#pragma once

#include <vraudio_api.h>

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(LogResonanceAudio, Log, All);

UENUM(BlueprintType)
enum class ERaQualityMode : uint8
{
	// Stereo panning.
	STEREO_PANNING						UMETA(DisplayName = "Stereo Panning"),
	// Binaural Low (First Order Ambisonics).
	BINAURAL_LOW						UMETA(DisplayName = "Binaural Low Quality"),
	// Binaural Medium (Second Order Ambisonics).
	BINAURAL_MEDIUM						UMETA(DisplayName = "Binaural Medium Quality"),
	// Binaural High (Third Order Ambisonics = Default).
	BINAURAL_HIGH						UMETA(DisplayName = "Binaural High Quality")
};

UENUM(BlueprintType)
enum class ERaSpatializationMethod : uint8
{
	// Stereo panning.
	STEREO_PANNING						UMETA(DisplayName = "Stereo Panning"),
	// Binaural rendering via HRTF.
	HRTF								UMETA(DisplayName = "HRTF")
};

UENUM(BlueprintType)
enum class ERaDistanceRolloffModel : uint8
{
	// Logarithmic distance attenuation model (default).
	LOGARITHMIC							UMETA(DisplayName = "Logarithmic"),
	// Linear distance attenuation model.
	LINEAR								UMETA(DisplayName = "Linear"),
	// Use Unreal Engine attenuation settings.
	NONE								UMETA(DisplayName = "None")
};

UENUM(BlueprintType)
enum class ERaMaterialName : uint8
{
	// Full acoustic energy absorption.
	TRANSPARENT							UMETA(DisplayName = "Transparent"),
	ACOUSTIC_CEILING_TILES				UMETA(DisplayName = "Acoustic Ceiling Tiles"),
	BRICK_BARE							UMETA(DisplayName = "Brick Bare"),
	BRICK_PAINTED						UMETA(DisplayName = "Brick Painted"),
	CONCRETE_BLOCK_COARSE				UMETA(DisplayName = "Concrete Block Coarse"),
	CONCRETE_BLOCK_PAINTED				UMETA(DisplayName = "Concrete Block Painted"),
	CURTAIN_HEAVY						UMETA(DisplayName = "Curtain Heavy"),
	FIBER_GLASS_INSULATION				UMETA(DisplayName = "Fiber Glass Insulation"),
	GLASS_THIN							UMETA(DisplayName = "Glass Thin"),
	GLASS_THICK							UMETA(DisplayName = "Glass Thick"),
	GRASS								UMETA(DisplayName = "Grass"),
	LINOLEUM_ON_CONCRETE				UMETA(DisplayName = "Linoleum On Concrete"),
	MARBLE								UMETA(DisplayName = "Marble"),
	METAL								UMETA(DisplayName = "Metal"),
	PARQUET_ONCONCRETE					UMETA(DisplayName = "Parquet On Concrete"),
	PLASTER_ROUGH						UMETA(DisplayName = "Plaster Rough"),
	PLASTER_SMOOTH						UMETA(DisplayName = "Plaster Smooth"),
	PLYWOOD_PANEL						UMETA(DisplayName = "Plywood Panel"),
	POLISHED_CONCRETE_OR_TILE			UMETA(DisplayName = "Polished Concrete Or Tile"),
	SHEETROCK							UMETA(DisplayName = "Sheetrock"),
	WATER_OR_ICE_SURFACE				UMETA(DisplayName = "Water Or Ice Surface"),
	WOOD_CEILING						UMETA(DisplayName = "Wood Ceiling"),
	WOOD_PANEL							UMETA(DisplayName = "Wood Panel"),
	// Uniform acoustic energy absorption across all frequency bands.
	UNIFORM								UMETA(DisplayName = "Uniform")
};

namespace ResonanceAudio
{
	typedef vraudio::VrAudioApi::SourceId RaSourceId;
	typedef vraudio::VrAudioApi::MaterialName RaMaterialName;
	typedef vraudio::VrAudioApi::RoomProperties RaRoomProperties;

	// Resonance Audio assets base color.
	const FColor ASSET_COLOR = FColor(0, 198, 246);

	// Number of surfaces in a shoe-box room.
	const int NUM_SURFACES = 6;

	// Conversion factor between Resonance Audio and Unreal world distance units (1cm in Unreal = 0.01m in Resonance Audio).
	const float SCALE_FACTOR = 0.01f;

	// Attempts to load the dynamic library pertaining to the given platform, performing some basic error checking.
	// Returns handle to dynamic library or nullptr on error.
	void* LoadResonanceAudioDynamicLibrary();

	// Calls the CreateVrAudioApi method either from the given dynamic library or directly in the case of static linkage.
	vraudio::VrAudioApi* CreateResonanceAudioApi(void* DynamicLibraryHandle, size_t NumChannels, size_t NumFrames, int SampleRate);

	// Invalid Source ID.
	const RaSourceId RA_INVALID_SOURCE_ID = vraudio::VrAudioApi::kInvalidSourceId;

	// Converts between Unreal enum and Resonance Audio room material.
	RaMaterialName ConvertToResonanceAudioMaterialName(ERaMaterialName UnrealMaterialName);

	// Converts between Unreal and Resonance Audio position coordinates.
	FVector ConvertToResonanceAudioCoordinates(const FVector& UnrealVector);

	// Converts between Unreal and Resonance Audio rotation quaternions.
	FQuat ConvertToResonanceAudioRotation(const FQuat& UnrealQuat);

} // namespace ResonanceAudio