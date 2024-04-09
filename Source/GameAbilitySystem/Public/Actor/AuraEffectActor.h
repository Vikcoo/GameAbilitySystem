// Copyright yu kai

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"

UCLASS()
class GAMEABILITYSYSTEM_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GamePlayEffectClass);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Effects")
	TSubclassOf<UGameplayEffect> InstantGamePlayEffectClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Effects")
	TSubclassOf<UGameplayEffect> DurationGamePlayEffectClass;
};
