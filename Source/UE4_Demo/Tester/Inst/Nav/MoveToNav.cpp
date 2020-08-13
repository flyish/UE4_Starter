// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveToNav.h"
#include "../../../Helper/HelperBlueprintFunctionLibrary.h"
#include "AIModule/Classes/AIController.h"
#include "GameFramework/Character.h"
#include "EngineUtils.h"

UMoveToNav::UMoveToNav()
{
	updateDescription();
}

void UMoveToNav::updateDescription()
{
	FStringFormatOrderedArguments args;
	FStringFormatArg arg(pointName);
	args.Add(arg);
	FString s = FString::Format(TEXT("<n>move to point:{0}</>"), args) ;
	DescText = FText::FromString(s);
}

void UMoveToNav::setPointName(const FString& strName)
{
	pointName = strName;
	updateDescription();

	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	m_pActor = FindObject<AActor>(pWorld_->GetCurrentLevel(), *pointName);
	check(m_pActor);
}

void UMoveToNav::start()
{
	if (nullptr == m_pActor)
	{
		setPointName(Name);
	}

	Super::start();
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();

	TActorIterator<ACharacter> actorItr = TActorIterator<ACharacter>(pWorld_);
	ACharacter* pCharacter_ = nullptr;
	for (actorItr; actorItr; ++actorItr)
	{
		ACharacter* p = *actorItr;
		AAIController* pAIController_ = Cast<AAIController>(p->GetController());
		if (nullptr != pAIController_)
		{
			pCharacter_ = p;
			pAIController_->MoveToActor(m_pActor);
			break;
		}
	}
	
	check(pCharacter_);
}

void UMoveToNav::end()
{
	Super::end();
}
