// Fill out your copyright notice in the Description page of Project Settings.


#include "UE4_DemoGameInstance.h"

UUE4_DemoGameInstance::UUE4_DemoGameInstance()
	: m_pActionManager(nullptr)
	, m_pUserWidgetManager(nullptr)
	, m_pTesterController(nullptr)
{

}

void UUE4_DemoGameInstance::OnStart()
{
	m_pActionManager = new FActionManager();
	if (nullptr == m_pUserWidgetManager)
	{
		m_pUserWidgetManager = NewObject<UUserWidgetsManager>();
	}

	if (nullptr == m_pTesterController)
	{
		m_pTesterController = NewObject<UTesterController>();
	}

	if (nullptr != m_pTesterController)
	{
		m_pTesterController->initalize();
	}

	TimerManager->SetTimer(m_hActionTimer, this, &UUE4_DemoGameInstance::OnActionTick, 0.033f, true);
}

void UUE4_DemoGameInstance::Shutdown()
{
	if (m_hActionTimer.IsValid())
	{
		TimerManager->ClearTimer(m_hActionTimer);
	}
	if (nullptr != m_pTesterController)
	{
		m_pTesterController->finilise();
	}

	if (NULL != m_pActionManager)
	{
		delete m_pActionManager;
		m_pActionManager = nullptr;
	}
	m_pUserWidgetManager = nullptr;
	m_pTesterController = nullptr;
}

void UUE4_DemoGameInstance::OnWorldChanged(UWorld* OldWorld, UWorld* NewWorld)
{
}

FActionManager* UUE4_DemoGameInstance::actionManager()
{
	return m_pActionManager;
}

UUserWidgetsManager* UUE4_DemoGameInstance::userWidgetsManager()
{
	return m_pUserWidgetManager;
}

UTesterController* UUE4_DemoGameInstance::testerController()
{
	return m_pTesterController;
}

void UUE4_DemoGameInstance::OnActionTick()
{
	if (nullptr != m_pActionManager)
	{
		m_pActionManager->update(0.33f);
	}
}
