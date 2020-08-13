// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TestItem.generated.h"

UCLASS(BlueprintType, Blueprintable)
class UE4_DEMO_API UTestItem : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
	int32 ItemIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText DescText;
public:	
	// Sets default values for this actor's properties
	UTestItem();
	~UTestItem();

	UFUNCTION(BlueprintCallable, Category = "Tester Item")
	virtual void start();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tester Item")
	void onStart();

	UFUNCTION(BlueprintCallable, Category = "Tester Item")
	virtual void end();
	UFUNCTION(BlueprintImplementableEvent, Category = "Tester Item")
	void onEnd();
};
