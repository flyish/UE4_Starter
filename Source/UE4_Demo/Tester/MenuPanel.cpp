// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPanel.h"
#include "../Helper/HelperBlueprintFunctionLibrary.h"

void UMenuPanel::Show_Implementation(uint8 showType)
{
	Super::Show_Implementation(showType);
	UWidget* p = this->GetWidgetFromName("MenuList");
	if (p)
	{
		printf("xxx");
	}
}

void UMenuPanel::onTest(const TSubclassOf<UBaseTester>& tester)
{
	UTesterController* pController_ = UHelperBlueprintFunctionLibrary::testerController();
	pController_->startTest(tester);
}
