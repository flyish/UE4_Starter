// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "../UE4_DemoGameInstance.h"
#include "HelperBlueprintFunctionLibrary.h"

FActionManager* UActionBlueprintFunctionLibrary::actionManager()
{
	UUE4_DemoGameInstance* pGameBase_ = UHelperBlueprintFunctionLibrary::gameInstance();
	verify(pGameBase_);

	FActionManager* pManager = pGameBase_->actionManager();
	check(pManager);
	return pManager;
}

void UActionBlueprintFunctionLibrary::stopAllActions()
{
	UUE4_DemoGameInstance* pGameBase_ = UHelperBlueprintFunctionLibrary::gameInstance();
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->removeAllActions();
	}
}

void UActionBlueprintFunctionLibrary::pauseAllActions()
{
	UUE4_DemoGameInstance* pGameBase_ = UHelperBlueprintFunctionLibrary::gameInstance();
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->pauseAllActions();
	}
}

void UActionBlueprintFunctionLibrary::resumeAllActions()
{
	UUE4_DemoGameInstance* pGameBase_ = UHelperBlueprintFunctionLibrary::gameInstance();
	verify(pGameBase_);

	FActionManager* pActionManager_ = pGameBase_->actionManager();
	if (nullptr != pActionManager_)
	{
		pActionManager_->resumeAllActions();
	}
}
