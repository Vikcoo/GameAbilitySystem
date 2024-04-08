// Copyright yu kai

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "EnemyInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEnemyInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEABILITYSYSTEM_API IEnemyInterface
{
	GENERATED_BODY()
public:
	virtual void HighlightActor() = 0;
	virtual void UnHighlightActor() = 0;
};
