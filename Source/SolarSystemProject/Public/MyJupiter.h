// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCelestialActors.h"

#include "MyJupiter.generated.h"

/**
 * 
 */
UCLASS()
class SOLARSYSTEMPROJECT_API AMyJupiter : public AMyCelestialActors
{
	GENERATED_BODY()

	protected:

		AMyJupiter();

	public:

		virtual void Tick(float DeltaTime) override;
		void OrbitAroundSun() override;
		virtual void BeginPlay() override;
	
};
