// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCelestialActors.h"

#include "MyMercury.generated.h"

/**
 * 
 */
UCLASS()
class SOLARSYSTEMPROJECT_API AMyMercury : public AMyCelestialActors
{
	GENERATED_BODY()

	protected:

		AMyMercury();

	public:

		virtual void Tick(float DeltaTime) override;
		void OrbitAroundSun() override;
		virtual void BeginPlay() override;
};
