// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tester/TestItem.h"
#include "UObject/NoExportTypes.h"
#include "CameraDirectorTest.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UCameraDirectorTest : public UTestItem
{
	GENERATED_BODY()
protected:
	UCameraDirectorTest();
	virtual void start();
	virtual void end();
};
