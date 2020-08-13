// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirectorTest.h"
#include "Kismet/GameplayStatics.h"
#include "../../../Helper/HelperBlueprintFunctionLibrary.h"

UCameraDirectorTest::UCameraDirectorTest()
{
	DescText = FText::FromString(("<n>Press 'Q' switch camera</> \n<n>Press 'E' & 'R' roll camera</>"));
}

void UCameraDirectorTest::start()
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	UGameplayStatics::OpenLevel(pWorld_, "CameraDirectorMap");
	Super::start();
}

void UCameraDirectorTest::end()
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	UGameplayStatics::OpenLevel(pWorld_, "MainMap");
	Super::end();
}
