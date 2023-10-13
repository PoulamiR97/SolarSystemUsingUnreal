// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCelestialActors.h"

#include "MyEarth.generated.h"

/**
 * 
 */
UCLASS()
class SOLARSYSTEMPROJECT_API AMyEarth : public AMyCelestialActors
{
	GENERATED_BODY()

	protected:

		AMyEarth();

	public:

		void OrbitAroundSun() override;
		virtual void Tick(float DeltaTime) override;
		virtual void BeginPlay() override;
	
};
