// Copyright yu kai


#include "Character/AuraEnemy.h"

#include "GameAbilitySystem/GameAbilitySystem.h"

AAuraEnemy::AAuraEnemy()
{
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility,ECR_Block);
}

void AAuraEnemy::HighlightActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("高亮"));
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);

	Weapon->SetRenderCustomDepth(true);
	Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
}

void AAuraEnemy::UnHighlightActor()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("取消高亮"));
	GetMesh()->SetRenderCustomDepth(false);
	Weapon->SetRenderCustomDepth(false);
}
