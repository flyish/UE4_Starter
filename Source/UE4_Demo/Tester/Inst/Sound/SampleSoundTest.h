// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tester/TestItem.h"
#include "GameFramework/Actor.h"
#include "SampleSoundTest.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API USampleSoundTest : public UTestItem
{
	GENERATED_BODY()

	UPROPERTY()
	TArray<AActor*> m_instActors;
	
public:
	USampleSoundTest();

	virtual void start() override;
	virtual void end() override;

};
