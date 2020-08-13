// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleSoundTest.h"
#include "UObjectGlobals.h"
#include "Engine/StreamableManager.h"
#include "../../../Helper/HelperBlueprintFunctionLibrary.h"
#include "GameFramework/Character.h"
#include "NoExportTypes.h"

USampleSoundTest::USampleSoundTest()
{
	DescText = FText::FromString("<n>Click new spawn actor play sound, and click again stop sound</>");
}

void USampleSoundTest::start()
{
	UWorld* pWorld_ = UHelperBlueprintFunctionLibrary::playWorld();
	ACharacter* pCharacter_ = UHelperBlueprintFunctionLibrary::GetFirstPlayerCharacter(pWorld_);

	FStreamableManager streamManager;
	FSoftClassPath streamPath1("/Game/Blueprints/Objects/BP_PlayBgSound.BP_PlayBgSound_C");
	UClass* pcls1_ = streamManager.LoadSynchronous<UClass>(streamPath1);
	if ( nullptr != pcls1_)
	{
		//m_instActors.Add(p1_);
		FTransform t_ = pCharacter_->GetTransform();
		FVector lo_ =	t_.GetTranslation() + FVector(150, 0, 0);
		t_.SetTranslation(lo_);
		AActor* a1_ = pWorld_->SpawnActor<AActor>(pcls1_, t_ );
		m_instActors.Add(a1_);
	}
	
	// StaticLoadObject can load BP_Speak/BP_Speak.BP_Speak/BP_Speak.BP_Speak_C
	// LoadClass<> only load BP_Speak.BP_Speak_C
	FString bgPath("/Game/Blueprints/Objects/BP_Speak.BP_Speak_C");
	UObject* u1_ = StaticLoadObject(UObject::StaticClass(), nullptr, *bgPath, *bgPath);
	TSubclassOf<UObject> pcls2_ = LoadClass<UObject>(nullptr, *bgPath);
	if (pcls2_)
	{
		FTransform t_ = pCharacter_->GetTransform();
		FVector lo_ = t_.GetTranslation() + FVector(-150, 0, 0);
		t_.SetTranslation(lo_);
		AActor* a1_ = pWorld_->SpawnActor<AActor>(pcls2_, t_ );
		m_instActors.Add(a1_);
	}
	Super::start();
}

void USampleSoundTest::end()
{
	for (int i = 0; i < m_instActors.Num(); ++i)
	{
		AActor* p = m_instActors[i];
		p->Destroy();
	}
	m_instActors.Empty();
	Super::end();
}
