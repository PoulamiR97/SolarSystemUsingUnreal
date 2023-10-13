// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyCelestialActors.h"
#include "Components/CanvasPanel.h"
#include "Components/TextBlock.h"
#include <Components/TextBlock.h>
#include "UObject/ConstructorHelpers.h"

#include "MyUserWidget.generated.h"


/**
 * 
 */
UCLASS()
class SOLARSYSTEMPROJECT_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void NativeConstruct() override;

	//UMyUserWidget(const FObjectInitializer& ObjectInitializer);


	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr <UTextBlock> CelestialWidgetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr <UTextBlock> massVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr <UTextBlock> velocityVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr <UTextBlock> diameterVal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
		TObjectPtr <UTextBlock> curDistFrmSunVal;


};
