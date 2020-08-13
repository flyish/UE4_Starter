// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tester/BaseTester.h"
#include "GameFramework/Character.h"
#include "NavTester.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UNavTester : public UBaseTester
{
    GENERATED_BODY()
	UPROPERTY()
	ACharacter*     m_playerActor;
    UPROPERTY()
    AController*    m_pOrigContrller;
public:
    UNavTester();
    virtual bool initialize() override;
    virtual void finalise() override;
};
