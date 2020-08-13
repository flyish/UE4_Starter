// Fill out your copyright notice in the Description page of Project Settings.


#include "TestItem.h"
#include "../Helper/HelperBlueprintFunctionLibrary.h"

// Sets default values
UTestItem::UTestItem()
{

}

UTestItem::~UTestItem()
{

}

void UTestItem::start()
{
	UTesterController* pController_ = UHelperBlueprintFunctionLibrary::testerController();
	if (NULL != pController_)
	{
		pController_->onRunStep(ItemIndex, DescText);
	}

	onStart();
}

void UTestItem::end()
{
	onEnd();
}
