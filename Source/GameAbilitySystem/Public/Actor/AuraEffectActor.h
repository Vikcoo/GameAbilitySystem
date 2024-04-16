// Copyright yu kai

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffect.h"
#include "GameFramework/Actor.h"
#include "AuraEffectActor.generated.h"



UENUM(BlueprintType)
enum class EEffectApplicationPolicy
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

UENUM(BlueprintType)
enum class EEffectRemovalPolicy
{
	RemoveOnOverlap,
	RemoveOnEndOverlap,
	DoNotRemove
};

USTRUCT(BlueprintType)
struct FEffect
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere)
	float EffectLevel = 1;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> GamePlayEffectClass = nullptr;
	UPROPERTY(EditAnywhere)
	EEffectApplicationPolicy ApplicationPolicy = EEffectApplicationPolicy::ApplyOnOverlap;
	UPROPERTY(EditAnywhere)
	EEffectRemovalPolicy RemovalPolicy = EEffectRemovalPolicy::DoNotRemove;
};

UCLASS()
class GAMEABILITYSYSTEM_API AAuraEffectActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAuraEffectActor();
	
protected:
	virtual void BeginPlay() override;

	//对目标施加所有效果
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(UAbilitySystemComponent* TargetASC, FEffect Effect);

	UFUNCTION(BlueprintCallable)
	void RemoveInfiniteEffectFromTarget(UAbilitySystemComponent* TargetASC);

	//是否在效果移除时候销毁
	bool bDestroyOnEffectRemoval = false;

	//存储了这个effectActor向其他ASC施加了的所有目前有效的效果
	TMap<FActiveGameplayEffectHandle, UAbilitySystemComponent*> ActiveEffectHandles;

	//当碰撞体产生重叠时 在蓝图或C++ 可以调用下列两个方法 在开始重叠或者结束重叠时 施加效果
	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Effects")
	TArray<FEffect> Effects;
	
};
