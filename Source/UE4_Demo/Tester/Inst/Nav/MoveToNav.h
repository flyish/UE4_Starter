// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tester/TestItem.h"
#include "UnrealString.h"
#include "MoveToNav.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UMoveToNav : public UTestItem
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
	UMoveToNav();

	UFUNCTION(BlueprintCallable, Category = "Test Item")
	void setPointName(const FString& strName);

	virtual void start() override;
	virtual void end() override;

};
