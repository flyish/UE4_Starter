// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tester/TestItem.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "MoveToNav2.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UMoveToNav2 : public UTestItem
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Test Item")
	FString pointName;
private:
	UPROPERTY()
		AActor* m_pActor;
private:
	void updateDescription();

public:
	UMoveToNav2();

	UFUNCTION(BlueprintCallable, Category = "Test Item")
	void setPointName(const FString& strName);

	virtual void start() override;
	virtual void end() override;
};
