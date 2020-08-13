// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBlueprintFunctionLibrary.h"
#include "Engine/Engine.h"
#include "../Widgets/UserWidgetsManager.h"
#include "../UE4_DemoGameInstance.h"
#include "HelperBlueprintFunctionLibrary.h"

void UWidgetBlueprintFunctionLibrary::showWidget(const FString& path, uint8 showType, const FString& associatedName, bool create /*= true*/)
{
	UUserWidgetsManager* pWidgetManager_ = widgetsManager();
	if (nullptr != pWidgetManager_)
	{
		pWidgetManager_->showWidget(path, showType, associatedName, create);
	}
}

void UWidgetBlueprintFunctionLibrary::hideWidget(const FString& path, uint8 hideType)
{
	UUserWidgetsManager* pWidgetManager_ = widgetsManager();
	if (nullptr != pWidgetManager_)
	{
		pWidgetManager_->hideWidget(path, hideType);
	}
}

UUserWidgetsManager* UWidgetBlueprintFunctionLibrary::widgetsManager()
{
	UUE4_DemoGameInstance* pGameBase_ = UHelperBlueprintFunctionLibrary::gameInstance();
	verify(pGameBase_);

	UUserWidgetsManager* pWidgetManager_ = pGameBase_->userWidgetsManager();
	check(pWidgetManager_);
	return pWidgetManager_;
}