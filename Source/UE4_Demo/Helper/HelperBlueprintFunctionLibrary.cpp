// Fill out your copyright notice in the Description page of Project Settings.

#include "HelperBlueprintFunctionLibrary.h"
#include "Engine/Engine.h"
#include "Kismet/GameplayStatics.h"
#include "../UE4_DemoGameInstance.h"

UUE4_DemoGameInstance* UHelperBlueprintFunctionLibrary::gameInstance()
{
	UUE4_DemoGameInstance* pGameBase_ = Cast<UUE4_DemoGameInstance>(GWorld->GetGameInstance());
	if (NULL == pGameBase_)
	{
		UEditorEngine* pEditorEngine_ = Cast<UEditorEngine>(GEngine);
		if (nullptr != pEditorEngine_ && nullptr != pEditorEngine_->PlayWorld)
		{
			UGameInstance* pInstance_ = pEditorEngine_->PlayWorld->GetGameInstance();
			pGameBase_ = Cast<UUE4_DemoGameInstance>(pInstance_);
		}
	}

	verify(pGameBase_);
	return pGameBase_;
}

UWorld* UHelperBlueprintFunctionLibrary::playWorld()
{
	UEditorEngine* pEditorEngine_ = Cast<UEditorEngine>(GEngine);
	if (nullptr != pEditorEngine_ && nullptr != pEditorEngine_->PlayWorld)
	{
		return pEditorEngine_->PlayWorld;
	}

	return (UWorld*)GWorld;
}

APlayerController* UHelperBlueprintFunctionLibrary::GetFirstPlayerController(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerController(WorldContextObject, 0);
}

APlayerController* UHelperBlueprintFunctionLibrary::GetFirstPlayerControllerCurrentContext()
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	return UHelperBlueprintFunctionLibrary::GetFirstPlayerController(pWorld_);
}

ACharacter* UHelperBlueprintFunctionLibrary::GetFirstPlayerCharacter(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerCharacter(WorldContextObject, 0);
}

ACharacter* UHelperBlueprintFunctionLibrary::GetFirstPlayerCharacterCurrentContext()
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	return UHelperBlueprintFunctionLibrary::GetFirstPlayerCharacter(pWorld_);
}

APawn* UHelperBlueprintFunctionLibrary::GetFirstPlayerPawn(const UObject* WorldContextObject)
{
	return UGameplayStatics::GetPlayerPawn(WorldContextObject, 0);
}

APawn* UHelperBlueprintFunctionLibrary::GetFirstPlayerPawnCurrentContext()
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	return UHelperBlueprintFunctionLibrary::GetFirstPlayerPawn(pWorld_);
}

AActor* UHelperBlueprintFunctionLibrary::SpawnActorInWorld(TSubclassOf<AActor> cls, const FTransform& transform)
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	return pWorld_->SpawnActor<AActor>(cls, transform);
}


UUserWidget* UHelperBlueprintFunctionLibrary::CreateWidgetForGameInstance(TSubclassOf<UUserWidget> cls)
{
	UWorld* pWorld_ =	playWorld();
	if (NULL != pWorld_)
	{
		return CreateWidget<UUserWidget>(pWorld_->GetGameInstance(), cls);
	}

	return nullptr;
}

UUserWidget* UHelperBlueprintFunctionLibrary::CreateWidgetForWorld(UWorld* world, TSubclassOf<UUserWidget> cls)
{
	return CreateWidget<UUserWidget>(world, cls);
}


UUserWidget* UHelperBlueprintFunctionLibrary::CreateWidgetForParent(UWidget* parent, TSubclassOf<UUserWidget> cls)
{
	return CreateWidget<UUserWidget>(parent, cls);
}


UUserWidget* UHelperBlueprintFunctionLibrary::CreateWidgetForPlayerContrller(APlayerController* playController, TSubclassOf<UUserWidget> cls)
{
	return CreateWidget<UUserWidget>(playController, cls);
}

void UHelperBlueprintFunctionLibrary::OpenLevelNoContext(const FString& levelName)
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	UGameplayStatics::OpenLevel(pWorld_, *levelName);
}

UTesterController* UHelperBlueprintFunctionLibrary::testerController()
{
	UUE4_DemoGameInstance* pGameBase_ = UHelperBlueprintFunctionLibrary::gameInstance();
	verify(pGameBase_);

	UTesterController* pTesterContrller = pGameBase_->testerController();
	check(pTesterContrller);
	return pTesterContrller;
}
