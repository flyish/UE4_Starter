// Fill out your copyright notice in the Description page of Project Settings.


#include "DescPanel.h"
#include "TesterController.h"
#include "../Helper/HelperBlueprintFunctionLibrary.h"

void UDescPanel::gotoStep(int32 step)
{
	UTesterController* pController_ = UHelperBlueprintFunctionLibrary::testerController();
	pController_->gotoStep(step);
}
