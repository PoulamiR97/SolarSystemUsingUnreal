// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUserWidget.h"


void UMyUserWidget::NativeConstruct()
{
	Super::NativeConstruct();
	CelestialWidgetName->SetJustification(ETextJustify::Center);
}

//UMyUserWidget::UMyUserWidget(const FObjectInitializer& ObjectInitializer)
//{
//
//}
