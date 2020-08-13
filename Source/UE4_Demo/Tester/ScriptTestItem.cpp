// Fill out your copyright notice in the Description page of Project Settings.


#include "ScriptTestItem.h"

UScriptTestItem::UScriptTestItem()
	: m_initScript(false) 
{
	
}

void UScriptTestItem::start()
{
	if (!m_initScript)
	{
		constructionScript();
		m_initScript = true;
	}
	start_script();
	Super::start();
}

void UScriptTestItem::end()
{
	end_script();
	Super::end();
}
