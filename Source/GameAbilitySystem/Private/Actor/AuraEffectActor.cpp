// Copyright yu kai


#include "Actor/AuraEffectActor.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"


AAuraEffectActor::AAuraEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SetRootComponent(CreateDefaultSubobject<USceneComponent>("SceneRoot")); 
}

void AAuraEffectActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AAuraEffectActor::ApplyEffectToTarget(UAbilitySystemComponent* TargetASC,FEffect Effect)
{
	check(TargetASC);
	check(Effect.GamePlayEffectClass);
	//创建此次效果施加需要的数据 并施加效果 返回一个有本次施加效果相关数据的handle->>ActiveEffectHandle
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(Effect.GamePlayEffectClass,Effect.EffectLevel,EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle =  TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	//对Infinite类效果的特殊记录
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && Effect.RemovalPolicy != EEffectRemovalPolicy::DoNotRemove)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle,TargetASC);
	}
}

void AAuraEffectActor::RemoveInfiniteEffectFromTarget(UAbilitySystemComponent* TargetASC)
{
	//目标身上有ASC  则在map中删除一层效果  先创建一个数组保存需要删除的效果 否则遍历过程中在MAP中删除会出大问题
	TArray<FActiveGameplayEffectHandle> HandlesToRemove;
	//遍历目前给其他ASC施加的效果  
	for (const auto HandlePair : ActiveEffectHandles)
	{
		//检查有没有给目前碰撞的物体施加过
		if (HandlePair.Value == TargetASC)
		{
			//如果有 则移除这个效果
			TargetASC->RemoveActiveGameplayEffect(HandlePair.Key, 1);
			//记录这个效果  遍历结束后从MAP中移除
			HandlesToRemove.Add(HandlePair.Key);
		}
	}
	//遍历待移除效果 将其在map中移除
	for (auto& Handle : HandlesToRemove)
	{
		ActiveEffectHandles.FindAndRemoveChecked(Handle);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	//获取目标ASC
	UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;
	
	for (const auto GE : Effects)
	{
		if (GE.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
		{
			ApplyEffectToTarget(TargetASC,GE);
		}
		if (GE.RemovalPolicy == EEffectRemovalPolicy::RemoveOnOverlap)
		{
			RemoveInfiniteEffectFromTarget(TargetASC);
		}
	}	
	
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	//获取目标ASC
	UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	for (const auto GE : Effects)
	{
		if (GE.ApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
		{
			ApplyEffectToTarget(TargetASC,GE);
		}
		if (GE.RemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
		{
			RemoveInfiniteEffectFromTarget(TargetASC);
		}
	}
}






