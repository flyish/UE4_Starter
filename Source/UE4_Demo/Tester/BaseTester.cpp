// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseTester.h"
#include "../Helper/HelperBlueprintFunctionLibrary.h"

// Sets default values
UBaseTester::UBaseTester()
	: m_nMaxStep( 0 )
	, m_nCurStep(0)
	, m_pRunItem(nullptr)
{
}

UBaseTester::~UBaseTester()
{

}

bool UBaseTester::initialize()
{
	onInitialize();
	return true;
}

void UBaseTester::finalise()
{
	onFinalise();
}

void UBaseTester::start()
{
	m_nMaxStep = m_itemNames.Num();
	UTesterController* pController_ = UHelperBlueprintFunctionLibrary::testerController();
	pController_->initSteps(TesterName, m_itemNames);

	m_nCurStep = -1;
	//gotoStep(0);
}

void UBaseTester::end()
{
	m_nCurStep = -1;
	if (nullptr != m_pRunItem)
	{
		m_pRunItem->end();
		m_pRunItem->ConditionalBeginDestroy();
		m_pRunItem = NULL;
	}
}

void UBaseTester::prevStep()
{
	int32 nStep = m_nCurStep - 1;
	gotoStep(nStep);
}

void UBaseTester::nextStep()
{
	int32 nStep = m_nCurStep + 1;
	gotoStep(nStep);
}

void UBaseTester::gotoStep_Implementation( int32 nStep )
{
	if (nStep < 0 || nStep >= m_nMaxStep)
	{
		UTesterController* pController_ = UHelperBlueprintFunctionLibrary::testerController();
		pController_->endTest();
	}
	else
	{
		onStepChaned(nStep);
	}
}

void UBaseTester::onInitialize_Implementation()
{

}

void UBaseTester::onFinalise_Implementation()
{

}

void UBaseTester::onStepChaned( int32 nStep)
{
	if (nStep == m_nCurStep)
	{
		return;
	}

	m_nCurStep = nStep;
	if (nullptr != m_pRunItem)
	{
		m_pRunItem->end();
		m_pRunItem->ConditionalBeginDestroy();
		m_pRunItem = NULL;
	}

	TSubclassOf<UTestItem>& cls = m_itemClasses[nStep];
	//m_pRunItem = Cast<UTestItem>( GWorld->SpawnActor(cls.Get()) );
	m_pRunItem = NewObject<UTestItem>(this, cls);
	if (nullptr != m_pRunItem)
	{
		m_pRunItem->ItemIndex = nStep;
		m_pRunItem->Name = m_itemNames[nStep];
		m_pRunItem->start();
	}
}

void UBaseTester::addItem(const FString& name, TSubclassOf<UTestItem> itemClass)
{
	m_itemNames.Add(name);
	m_itemClasses.Add(itemClass);
}