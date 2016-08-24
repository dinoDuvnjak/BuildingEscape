// Copyright (c), Firelight Technologies Pty, Ltd. 2012-2016.

#pragma once

#include "Sound/ReverbEffect.h"
#include "FMODSnapshotReverb.generated.h"

/* Purely for doxygen generation */
#ifdef GENERATE_DOX
	#define UCLASS(...)
	#define UPROPERTY(...) public:
#endif

/**
 * FMOD Event Asset.
 */
UCLASS()
class FMODSTUDIO_API UFMODSnapshotReverb : public UReverbEffect
{
	GENERATED_UCLASS_BODY()

	/** The unique Guid, which matches the one exported from FMOD Studio */
	UPROPERTY()
	FGuid AssetGuid;

	/** Whether to show in the content window */
	UPROPERTY()
	bool bShowAsAsset;

	/** Force this to be an asset */
	virtual bool IsAsset() const override { return bShowAsAsset; }
};


