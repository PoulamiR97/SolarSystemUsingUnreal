// Fill out your copyright notice in the Description page of Project Settings.


#include "MySun.h"

AMySun::AMySun()
{
    FS_CelestialName = "SUN";
    MyStaticMeshComponent->SetMaterial(0, SGSettings->SunMaterial.LoadSynchronous());
    Mass = 1988500.f;
    Diameter = 1392000.f;
    OrbitInDays = 0.0f;            // Sun will not have translational motion
    OrbitWidth = 0.0f;      // Sun will not have translational motion
    OrbitHeight = 0.0f;     // Sun will not have translational motion
    RevolutionSpeed = 0.0f; // Sun will not have translational motion
    //Sun Rotation and Speed has been set along with material only.
    SetActorLabel(FS_CelestialName);

}


void AMySun::BeginPlay()
{
    SetActorScale3D(FVector((Diameter)*ScaleMultiplier * SunScaleAdjustment));
    Super::BeginPlay();
}