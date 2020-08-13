// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ObjectMacros.h"
#include "GameFramework/Actor.h"
#include "../Tester/TesterController.h"
#include "UMG/Public/Components/Widget.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "HelperBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UHelperBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "Game Helper")
	static UUE4_DemoGameInstance* gameInstance();

	UFUNCTION(BlueprintPure, Category = "Game Helper")
	static UWorld*				playWorld();

	UFUNCTION(BlueprintPure, Category = "Game Helper", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static APlayerController* GetFirstPlayerController(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "Game Helper")
	static APlayerController* GetFirstPlayerControllerCurrentContext();

	UFUNCTION(BlueprintPure, Category = "Game Helper", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static ACharacter* GetFirstPlayerCharacter(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "Game Helper")
	static ACharacter* GetFirstPlayerCharacterCurrentContext();

	UFUNCTION(BlueprintPure, Category = "Game Helper", meta = (WorldContext = "WorldContextObject", UnsafeDuringActorConstruction = "true"))
	static APawn* GetFirstPlayerPawn(const UObject* WorldContextObject);
	UFUNCTION(BlueprintPure, Category = "Game Helper")
	static APawn* GetFirstPlayerPawnCurrentContext();

	UFUNCTION(BlueprintCallable, Category = "Game Helper")
	static AActor* SpawnActorInWorld(TSubclassOf<AActor> cls, const FTransform& transform);

	UFUNCTION(BlueprintCallable, Category = "Game Helper")
	static UUserWidget* CreateWidgetForGameInstance(TSubclassOf<UUserWidget> cls);
	UFUNCTION(BlueprintCallable, Category = "Game Helper")
	static UUserWidget* CreateWidgetForWorld( UWorld* world, TSubclassOf<UUserWidget> cls);
	UFUNCTION(BlueprintCallable, Category = "Game Helper")
	static UUserWidget* CreateWidgetForParent(UWidget* parent, TSubclassOf<UUserWidget> cls);
	UFUNCTION(BlueprintCallable, Category = "Game Helper")
	static UUserWidget* CreateWidgetForPlayerContrller(APlayerController* playController, TSubclassOf<UUserWidget> cls);
	
	UFUNCTION(BlueprintCallable, Category = "Game Helper")
	static void OpenLevelNoContext( const FString& levelName );

	UFUNCTION(BlueprintPure, Category = "Game Helper")
	static UTesterController* testerController();
};
