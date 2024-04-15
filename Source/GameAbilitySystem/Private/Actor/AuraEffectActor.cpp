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

void AAuraEffectActor::ApplyEffectToTarget(AActor* TargetActor, TSubclassOf<UGameplayEffect> GamePlayEffectClass)
{
	//获取目标ASC
	UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	if (TargetASC == nullptr) return;

	//创建此次效果施加需要的数据 并施加效果 返回一个有本次施加效果相关数据的handle->>ActiveEffectHandle
	check(GamePlayEffectClass);
	FGameplayEffectContextHandle EffectContextHandle = TargetASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	const FGameplayEffectSpecHandle EffectSpecHandle = TargetASC->MakeOutgoingSpec(GamePlayEffectClass,ActorLevel,EffectContextHandle);
	const FActiveGameplayEffectHandle ActiveEffectHandle =  TargetASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());

	//对Infinite类效果的特殊处理
	const bool bIsInfinite = EffectSpecHandle.Data.Get()->Def->DurationPolicy == EGameplayEffectDurationType::Infinite;
	if (bIsInfinite && InfiniteEffectRemovalPolicy != EEffectRemovalPolicy::DoNotRemove)
	{
		ActiveEffectHandles.Add(ActiveEffectHandle,TargetASC);
	}
}

void AAuraEffectActor::OnOverlap(AActor* TargetActor)
{
	//施加效果
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGamePlayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGamePlayEffectClass);
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGamePlayEffectClass);
	}
	//消除效果 目前只有Infinite效果需要消除
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnOverlap)
	{
		//获取碰撞目标身上的ASC  没有则直接返回
		UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;
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
}

void AAuraEffectActor::OnEndOverlap(AActor* TargetActor)
{
	if (InstantEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InstantGamePlayEffectClass);
	}
	if (DurationEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,DurationGamePlayEffectClass); 
	}
	if (InfiniteEffectApplicationPolicy == EEffectApplicationPolicy::ApplyOnEndOverlap)
	{
		ApplyEffectToTarget(TargetActor,InfiniteGamePlayEffectClass); 
	}
	//消除永久效果
	if (InfiniteEffectRemovalPolicy == EEffectRemovalPolicy::RemoveOnEndOverlap)
	{
		//获取碰撞目标身上的ASC  没有则直接返回
		UAbilitySystemComponent* TargetASC =  UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
		if (!IsValid(TargetASC)) return;
		//目标身上有ASC  则在map中删除一层效果  先创建一个数组保存需要删除的效果 否则遍历过程中在MAP中删除会出大问题
		TArray<FActiveGameplayEffectHandle> HandlesToRemove;
		//遍历目前给其他ASC施加的效果  
		for (const auto HandlePair : ActiveEffectHandles)
		{
			//检查有没有给目前碰撞的物体施加过效果
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
}






