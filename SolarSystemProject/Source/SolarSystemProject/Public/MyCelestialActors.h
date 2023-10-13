// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"
#include "MyDeveloperSettings.h"
#include <string>
#include <math.h>

#include "MyCelestialActors.generated.h"


constexpr float ScaleMultiplier = 0.0001;

/// <summary>
/// Template class from where all the celestial planets are inheriting same properties.
/// </summary>

UCLASS(Config = Game)
class SOLARSYSTEMPROJECT_API AMyCelestialActors : public AActor
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Sets default values for this actor's properties - CONSTRUCTION CELESTIAL ACTORS
	AMyCelestialActors();

	// TIME
	/*UPROPERTY(EditAnywhere, Category = "SolarSystem|Distance")
		float SpeedBaseLine;*/

	UPROPERTY(Config, VisibleAnywhere, Category = "SolarSystem|Distance")
		float SpeedScaleFactor;

	// NAMES
	FString FS_CelestialName;

	// TRANSLATION
	float GetRevolutionSpeed(float, float, float);
	FVector MeshXYZ;
	UPROPERTY(EditAnywhere)
		float RevolutionSpeed;

	UPROPERTY(VisibleAnywhere)
		float DistanceFromSun;

	// ORBIT
	virtual void OrbitAroundSun(); //return current distance from Sun
	float RotationPerOrbit;
	float OrbitInDays;
	UPROPERTY(EditAnywhere, Category = "SolarSystem|Dimensions")
		float OrbitWidth;
	UPROPERTY(EditAnywhere, Category = "SolarSystem|Dimensions")
		float OrbitHeight;

	// ROTATION
	void RotateAroundAxis(float);
	float AxisRotationDirection;

	// SCALE AND PROPERTIES
	UPROPERTY(EditAnywhere, Category = "SolarSystem|Dimensions")
		float Diameter;
	UPROPERTY(VisibleAnywhere, Category = "SolarSystem|Dimensions")
		float Mass;


	// RELATIONS
	UPROPERTY(EditAnywhere, Category = "SolarSystem|Relations")
		TObjectPtr <UStaticMeshComponent> MyStaticMeshComponent;

	///SPLINE
	TObjectPtr <USplineComponent> CelestialSplineComponent;
	TObjectPtr<UStaticMesh> SplineMeshAsset;

	///SAVING GAME SETTINGS
	const UMyDeveloperSettings* SGSettings;

};

