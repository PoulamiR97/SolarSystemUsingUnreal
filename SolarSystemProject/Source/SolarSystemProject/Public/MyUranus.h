// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCelestialActors.h"

#include "MyUranus.generated.h"

/**
 * 
 */
UCLASS()
class SOLARSYSTEMPROJECT_API AMyUranus : public AMyCelestialActors
{
	GENERATED_BODY()

	protected:

		AMyUranus();

	public:

		virtual void Tick(float DeltaTime) override;
		void OrbitAroundSun() override;
		virtual void BeginPlay() override;
};
