// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UserWidgetPanel.h"
#include "MenuPanel.generated.h"

/**
 * 
 */
UCLASS(editinlinenew, BlueprintType, Blueprintable, meta = (DontUseGenericSpawnObject = "True", DisableNativeTick))
class UE4_DEMO_API UMenuPanel : public UUserWidgetPanel
{
	GENERATED_BODY()
	
public:
	void Show_Implementation(uint8 showType);

	UFUNCTION(BlueprintImplementableEvent)
	void addMenu(const FString& showText, TSubclassOf<UBaseTester> tester);
	UFUNCTION(BlueprintCallable)
	void onTest(const TSubclassOf<UBaseTester>& tester);
};
