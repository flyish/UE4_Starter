// Fill out your copyright notice in the Description page of Project Settings.


#include "StremLevelTest.h"
#include "../../../Helper/HelperBlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

UStremLevelTest::UStremLevelTest()
{
	DescText = FText::FromString(("<n>Forward move character will load stream level, Press 'G' Rotate Cube in stream level</>"));
}

void UStremLevelTest::start()
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	UGameplayStatics::OpenLevel(pWorld_, "TestMap");

	Super::start();
}

void UStremLevelTest::end()
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	UGameplayStatics::OpenLevel(pWorld_, "MainMap");
	Super::end();
}
