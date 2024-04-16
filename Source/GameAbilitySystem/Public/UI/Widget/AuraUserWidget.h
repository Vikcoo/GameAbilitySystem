// Copyright yu kai

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AuraUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class GAMEABILITYSYSTEM_API UAuraUserWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//设置这个Widget的控制器
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	
protected:
	//SetController后执行的事件  在SetWidgetController中的最后调用
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();
	
	//这个Widget的控制器
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
};
