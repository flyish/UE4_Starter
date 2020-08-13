// Fill out your copyright notice in the Description page of Project Settings.

#include "UE4_DemoGameModeBase.h"
#include "Tester/TesterController.h"
#include "Helper/HelperBlueprintFunctionLibrary.h"


AUE4_DemoGameModeBase::AUE4_DemoGameModeBase()
{
	//PrimaryActorTick.bCanEverTick = true;
}


AUE4_DemoGameModeBase::~AUE4_DemoGameModeBase()
{

}

void AUE4_DemoGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
}

void AUE4_DemoGameModeBase::StartPlay()
{
	Super::StartPlay();

	UTesterController* pController_ = UHelperBlueprintFunctionLibrary::testerController();
	if (nullptr != pController_)
	{
		pController_->onEnterWorld();
	}
}


void AUE4_DemoGameModeBase::BeginDestroy()
{
	Super::BeginDestroy();
}


void AUE4_DemoGameModeBase::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
