// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TestItem.h"
#include "UObject/NoExportTypes.h"
#include "BaseTester.generated.h"

UCLASS(editinlinenew, BlueprintType, Blueprintable)
class UE4_DEMO_API UBaseTester : public UObject
{
	GENERATED_BODY()
protected:
	int32 m_nMaxStep;
	int32 m_nCurStep;
	
	TArray< TSubclassOf<UTestItem> > m_itemClasses;
	TArray< FString>				m_itemNames;
	UPROPERTY(BlueprintReadOnly, Category = "Tester")
	UTestItem* m_pRunItem;

public:
	UPROPERTY(EditAnywhere, Category = "Tester")
	FName TesterName;
public:	
	// Sets default values for this actor's properties
	UBaseTester();
	~UBaseTester();
public:	
	UFUNCTION(BlueprintCallable, Category = "Tester")
	virtual bool initialize();
	UFUNCTION(BlueprintCallable, Category = "Tester")
	virtual void finalise();

	UFUNCTION(BlueprintCallable, Category = "Tester")
	virtual void start();

	UFUNCTION(BlueprintCallable, Category = "Tester")
	virtual void end();

	UFUNCTION(BlueprintCallable, Category = "Tester")
	void prevStep();

	UFUNCTION(BlueprintCallable, Category = "Tester")
	void nextStep();
	UFUNCTION(BlueprintNativeEvent, Category = "Tester")
	void gotoStep(int32 step);
	UFUNCTION(BlueprintNativeEvent, Category = "Tester")
	void onInitialize();
	UFUNCTION(BlueprintNativeEvent, Category = "Tester")
	void onFinalise();

	UFUNCTION(BlueprintCallable, Category = "Tester")
	virtual void onStepChaned( int32 nStep);

protected:
	UFUNCTION(BlueprintCallable, Category = "Tester")
	void addItem(const FString& name, TSubclassOf<UTestItem> itemClass );
};
