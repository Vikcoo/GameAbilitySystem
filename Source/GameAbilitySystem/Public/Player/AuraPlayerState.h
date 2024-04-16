// Copyright yu kai

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "AuraPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GAMEABILITYSYSTEM_API AAuraPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	AAuraPlayerState();
	//重写IAbilitySystemInterface的GetAbilitySystemComponent方法，获取ASC
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//AS没有接口不能重写 自己写 获取AS
	virtual UAttributeSet* GetAttributeSet();
protected:
	//PS的ASC
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	//PS的AS
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAttributeSet> AttributeSet;
};
