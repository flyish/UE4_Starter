// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MenuPanel.h"
#include "DescPanel.h"
#include "BaseTester.h"
#include "TesterController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_DEMO_API UTesterController : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, Category = "Panel")
	TSubclassOf<UMenuPanel>		MenuPanelType;
	UPROPERTY(EditAnywhere, Category = "Panel")
	TSubclassOf<UDescPanel>		DescPanelType;

	UPROPERTY(BlueprintReadOnly, Category = "Panel")
	UMenuPanel* m_pMenuPanel;
	UPROPERTY(BlueprintReadOnly, Category = "Panel")
	UDescPanel* m_pDescPanel;
	UPROPERTY(BlueprintReadOnly, Category = "Tester")
	UBaseTester* m_pCurTester;
	UPROPERTY(BlueprintReadOnly, Category = "Tester")
	bool m_bIsTesting;
public:
	UTesterController();
	~UTesterController();
	bool initalize();
	void finilise();
public:
	UFUNCTION(BlueprintCallable, Category = "Controller")
	void onEnterWorld();
	UFUNCTION(BlueprintCallable, Category = "Controller")
	//void startTest(const FString& path);
	void startTest(const TSubclassOf<UBaseTester>& tester);
	UFUNCTION(BlueprintCallable, Category = "Controller")
	void endTest();
	UFUNCTION(BlueprintCallable, Category = "Controller")
	void initSteps( const FName& name, const TArray<FString>& title );
	UFUNCTION(BlueprintCallable, Category = "Controller")
	void nextStep();
	UFUNCTION(BlueprintCallable, Category = "Controller")
	void prevStep();
	UFUNCTION(BlueprintCallable, Category = "Controller")
	void gotoStep( int32 step );
	UFUNCTION(BlueprintCallable, Category = "Controller")
	void onRunStep(int32 step, const FText& desc);
};
