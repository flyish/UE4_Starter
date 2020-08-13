// Fill out your copyright notice in the Description page of Project Settings.
#include "TesterController.h"
#include "../Widgets/UserWidgetsManager.h"
#include "../Helper/WidgetBlueprintFunctionLibrary.h"
#include "UMG/Public/Blueprint/UserWidget.h"
#include "../Helper/HelperBlueprintFunctionLibrary.h"
#include "ConstructorHelpers.h"
#include "Kismet/KismetSystemLibrary.h"

UTesterController::UTesterController()
	: m_pCurTester( nullptr )
	, m_bIsTesting( false )
{

}

UTesterController::~UTesterController()
{

}

bool UTesterController::initalize()
{
	UUserWidgetsManager* pWidgetManager_ = UWidgetBlueprintFunctionLibrary::widgetsManager();
	if (MenuPanelType.Get() != nullptr)
	{
		m_pMenuPanel = Cast<UMenuPanel>(CreateWidget(UHelperBlueprintFunctionLibrary::GetFirstPlayerController(this), MenuPanelType));
		m_pMenuPanel->setPanelName(TEXT("MenuPanel"));
		pWidgetManager_->addWidget(TEXT("DescPanel"), m_pMenuPanel);
	}
	else
	{
		m_pMenuPanel = Cast<UMenuPanel>(pWidgetManager_->createWidget(FString("/Game/Blueprints/BP_MenuPanel.BP_MenuPanel_C")));
	}
	
	if (DescPanelType.Get() != nullptr)
	{
		m_pDescPanel = Cast<UDescPanel>( CreateWidget(UHelperBlueprintFunctionLibrary::GetFirstPlayerController(this), DescPanelType) );
		m_pDescPanel->setPanelName(TEXT("DescPanel"));

		pWidgetManager_->addWidget(TEXT("DescPanel"), m_pDescPanel);
	}
	else
	{
		m_pDescPanel = Cast<UDescPanel>(pWidgetManager_->createWidget(FString("/Game/Blueprints/BP_DescPanel.BP_DescPanel_C")));
	}

	return true;
}

void UTesterController::finilise()
{
	//UUserWidgetsManager* pWidgetManager_ = UWidgetBlueprintFunctionLibrary::widgetsManager();
	//if (nullptr != m_pDescPanel)
	//{
	//	pWidgetManager_->removeWidget( m_pDescPanel->getPanelName() );
	//}
	//
	//if (nullptr != m_pMenuPanel)
	//{
	//	pWidgetManager_->removeWidget(m_pMenuPanel->getPanelName());
	//}
}

void UTesterController::onEnterWorld()
{
	if (m_bIsTesting)
	{
		m_pDescPanel->Show((uint8)EPanelShowType::E_PANEL_SHOW_NORMAL);
	}
	else
	{
		m_pMenuPanel->Show((uint8)EPanelShowType::E_PANEL_SHOW_NORMAL);
	}
}

//void UTesterController::startTest(const FString& path)
void UTesterController::startTest(const TSubclassOf<UBaseTester>& tester)
{
	if (nullptr != m_pCurTester)
	{
		//m_pCurTester->Destroy();
		m_pCurTester->end();
		m_pCurTester->ConditionalBeginDestroy();
		m_pCurTester = nullptr;
	}

	//ConstructorHelpers::FObjectFinder<ABaseTester> finder(*path);
	//if (finder.Succeeded())
	//{
	//	m_pCurTester = finder.Object;
	//}
	//else
	//{
	//	UKismetSystemLibrary::PrintString(this, path + TEXT(" not found!!!!"));
	//	endTest();
	//}
	//UClass* pClass = LoadClass<AActor>(this, *path, *path);
	//m_pCurTester = NewObject<UBaseTester>( this, pClass, *path );
	// NewObject cant trigger BeginPlay ?? LoadObject will return nullptr!!!
	m_pCurTester = NewObject<UBaseTester>(this, tester);
	if (nullptr == m_pCurTester)
	{
		UKismetSystemLibrary::PrintString(this, TEXT("tester not found!!!!"));
		endTest();
	}
	else
	{
		m_bIsTesting = true;
		m_pMenuPanel->Hide((uint8)EPanelHideType::E_PANEL_HIDE_NORMAL);
		m_pDescPanel->Show((uint8)EPanelShowType::E_PANEL_SHOW_NORMAL);
		m_pCurTester->initialize();
		m_pCurTester->start();
	}
}

void UTesterController::endTest()
{
	m_bIsTesting = false;
	if (nullptr != m_pCurTester)
	{
		m_pCurTester->end();
		m_pCurTester->finalise();
		m_pCurTester->ConditionalBeginDestroy();
		m_pCurTester = nullptr;
	}
	m_pDescPanel->Hide((uint8)EPanelHideType::E_PANEL_HIDE_NORMAL);
	m_pMenuPanel->Show((uint8)EPanelShowType::E_PANEL_SHOW_NORMAL);
}

void UTesterController::initSteps(const FName& name, const TArray<FString>& title)
{
	if (nullptr != m_pDescPanel)
	{
		m_pDescPanel->initSteps(name, title);
	}
}

void UTesterController::nextStep()
{
	if (nullptr != m_pCurTester)
	{
		m_pCurTester->nextStep();
	}
	else
	{
		endTest();
	}
}

void UTesterController::prevStep()
{
	if (nullptr != m_pCurTester)
	{
		m_pCurTester->prevStep();
	}
	else
	{
		endTest();
	}
}

void UTesterController::gotoStep(int32 step)
{
	if (nullptr != m_pCurTester)
	{
		m_pCurTester->gotoStep( step );
	}
	else
	{
		endTest();
	}
}

void UTesterController::onRunStep(int32 step, const FText& desc)
{
	if (nullptr != m_pDescPanel)
	{
		m_pDescPanel->onRunStep(step, desc);
	}
}
