// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Actor.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine.h"
#include "MyUserWidget.h"
#include "MyCelestialActors.h"
#include "DrawDebugHelpers.h"
#include "MySun.h"
#include "MyMercury.h"
#include "MyVenus.h"
#include "MyEarth.h"
#include "MyMars.h"
#include "MyJupiter.h"
#include "MySaturn.h"
#include "MyUranus.h"
#include "MyNeptune.h"

#include <vector>
#include <string>
#include <math.h>

#include "MyPawnAttachedCamera.generated.h"

UCLASS()
class SOLARSYSTEMPROJECT_API AMyPawnAttachedCamera : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPawnAttachedCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "SolarSystem|MyCamera")
        TObjectPtr <UCameraComponent> MyCameraComp;

    UPROPERTY(EditAnywhere, Category = "SolarSystem|MyCamera")
        TObjectPtr <USpringArmComponent> MyCameraSpringArmComp;

    //Input variables
    FVector2D MovementInput;
    FVector2D CameraInput;
    float ZoomFactor;
    bool bZoomingIn;

    //Input functions
    void MoveFrontBack(float myAxisVal);
    void MoveLeftRight(float myAxisVal);
    void PitchMyCamera(float myAxisVal);
    void YawMyCamera(float myAxisVal);
    void ZoomIn();
    void ZoomOut();
    void InteractPressed();
    void InteractReleased();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    TObjectPtr <AMyCelestialActors> PlanetActor;

    TSubclassOf<UUserWidget> MyWidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
        TObjectPtr <UMyUserWidget> MyWidget;

    void setWidget();

    ///Main function
    UFUNCTION(BlueprintCallable, Category = "SolarSystem|Celestial Actors")
        static void MakeSolarSystem(AActor* creator);

};
