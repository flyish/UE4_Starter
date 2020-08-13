// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToNav2.h"
#include "../../../Helper/HelperBlueprintFunctionLibrary.h"
#include "AIModule/Classes/Blueprint/AIBlueprintHelperLibrary.h"


UMoveToNav2::UMoveToNav2()
{
	updateDescription();
}

void UMoveToNav2::updateDescription()
{
	FStringFormatOrderedArguments args;
	FStringFormatArg arg(pointName);
	args.Add(arg);
	FString s = FString::Format(TEXT("<n>move to point:{0}</>"), args);
	DescText = FText::FromString(s);
}

void UMoveToNav2::setPointName(const FString& strName)
{
	pointName = strName;
	updateDescription();

	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	m_pActor = FindObject<AActor>(pWorld_->GetCurrentLevel(), *pointName);
	check(m_pActor);
}

void UMoveToNav2::start()
{
	if (nullptr == m_pActor)
	{
		setPointName(Name);
	}

	Super::start();

	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	ACharacter* pCharacter_ = UHelperBlueprintFunctionLibrary::GetFirstPlayerCharacter(pWorld_);
	check(pCharacter_);
	UAIBlueprintHelperLibrary::SimpleMoveToActor(pCharacter_->GetController(), m_pActor);
}

void UMoveToNav2::end()
{
	Super::end();
}
