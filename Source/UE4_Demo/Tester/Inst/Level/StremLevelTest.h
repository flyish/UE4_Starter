// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tester/TestItem.h"
#include "StremLevelTest.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UStremLevelTest : public UTestItem
{
	GENERATED_BODY()
	
public:
	UStremLevelTest();

	virtual void start() override;
	virtual void end() override;
};
