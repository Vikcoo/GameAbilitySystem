// Copyright yu kai


#include "Character/AuraEnemy.h"

void AAuraEnemy::Highlight()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("高亮"));
}

void AAuraEnemy::UnHighlight()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("取消高亮"));
}
