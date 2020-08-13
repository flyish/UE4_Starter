// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Action/ActionManager.h"
#include "Widgets/UserWidgetsManager.h"
#include "Tester/TesterController.h"
#include "UE4_DemoGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UUE4_DemoGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FActionManager* m_pActionManager;
	UPROPERTY(EditAnywhere, Category = "Manager")
	UUserWidgetsManager* m_pUserWidgetManager;
	UPROPERTY(EditAnywhere, Category = "Manager")
	UTesterController* m_pTesterController;

private:
	FTimerHandle m_hActionTimer;
public:
	UUE4_DemoGameInstance();
	/** Called when the game instance is started either normally or through PIE. */
	virtual void OnStart() override;
	virtual void Shutdown() override;
	virtual void OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld) override;
public:
	FActionManager* actionManager();

	UFUNCTION(BlueprintPure, Category = "UserWidgets")
	UUserWidgetsManager* userWidgetsManager();

	UFUNCTION(BlueprintPure, Category = "Tester")
	UTesterController* testerController();

private:
	void OnActionTick();
};
