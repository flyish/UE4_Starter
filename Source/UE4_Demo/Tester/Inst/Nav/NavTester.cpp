// Fill out your copyright notice in the Description page of Project Settings.


#include "NavTester.h"
#include "../../../Helper/HelperBlueprintFunctionLibrary.h"
#include "AIModule/Classes/AIController.h"

UNavTester::UNavTester()
	: m_playerActor( NULL )
	, m_pOrigContrller( NULL )
{

}

bool UNavTester::initialize()
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	check(pWorld_);

	m_playerActor = UHelperBlueprintFunctionLibrary::GetFirstPlayerCharacter(pWorld_);
	check(m_playerActor);

	m_pOrigContrller = m_playerActor->GetController();

	FActorSpawnParameters SpawnInfo;
	SpawnInfo.Instigator = m_playerActor->GetInstigator();
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnInfo.OverrideLevel = m_playerActor->GetLevel();
	SpawnInfo.ObjectFlags |= RF_Transient;	// We never want to save AI controllers into a map
	AController* NewController = pWorld_->SpawnActor<AController>(AAIController::StaticClass(), m_playerActor->GetActorLocation(), m_playerActor->GetActorRotation(), SpawnInfo);
	if (NewController != nullptr)
	{
		// if successful will result in setting this->Controller 
		// as part of possession mechanics
		NewController->Possess((APawn*)m_playerActor);
	}

	return Super::initialize();
}

void UNavTester::finalise()
{
	if (nullptr != m_pOrigContrller && nullptr != m_playerActor)
	{
		AController* pContrller_ = m_playerActor->GetController();
		if (pContrller_ != m_pOrigContrller)
		{
			m_pOrigContrller->Possess((APawn*)m_playerActor);
			m_pOrigContrller = nullptr;
			m_playerActor = nullptr;
			pContrller_->Destroy();
		}
	}
	Super::finalise();
}