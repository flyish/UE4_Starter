// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tester/TestItem.h"
#include "ScriptTestItem.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class UE4_DEMO_API UScriptTestItem : public UTestItem
{
	GENERATED_BODY()

	bool m_initScript;
public:
	UScriptTestItem();

	virtual void start() override;
	virtual void end() override;

public:
	UFUNCTION(BlueprintImplementableEvent, Category = "Test Item", meta = (DisplayName = "Construction Script"))
	void constructionScript();

	UFUNCTION(BlueprintImplementableEvent, Category = "Test Item", meta = (DisplayName = "Start"))
	void start_script();

	UFUNCTION(BlueprintImplementableEvent, Category = "Test Item", meta = (DisplayName = "End"))
	void end_script();
};
