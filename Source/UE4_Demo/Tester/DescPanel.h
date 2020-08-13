// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Widgets/UserWidgetPanel.h"
#include "DescPanel.generated.h"

/**
 * 
 */
UCLASS(editinlinenew, BlueprintType, Blueprintable, meta = (DontUseGenericSpawnObject = "True", DisableNativeTick))
class UE4_DEMO_API UDescPanel : public UUserWidgetPanel
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, Category = "DescPanel")
	void initSteps(const FName& name, const TArray<FString>& title);

	UFUNCTION(BlueprintImplementableEvent, Category = "DescPanel")
	void onRunStep(int32 step, const FText& desc);

	UFUNCTION(BlueprintCallable, Category = "DescPanel")
	void gotoStep(int32 step);
};
