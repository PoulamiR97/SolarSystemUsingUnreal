// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCelestialActors.h"

#include "MySun.generated.h"

/**
 * 
 */
UCLASS()
class SOLARSYSTEMPROJECT_API AMySun : public AMyCelestialActors
{
	GENERATED_BODY()

	protected:

		AMySun();

	public:

		virtual void BeginPlay() override;
		float SunScaleAdjustment = 0.1;
	
};
