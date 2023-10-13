// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEarth.h"

AMyEarth::AMyEarth()
{
	FS_CelestialName = "EARTH";
    MyStaticMeshComponent->SetMaterial(0, SGSettings->EarthMaterial.LoadSynchronous());
    Mass = 5.97f;
    Diameter = 12742.0f;
    OrbitInDays = 365.0f;
    OrbitWidth = 3000.0f;
    OrbitHeight = 4000.0f;
    RotationPerOrbit = 365.26f;
    AxisRotationDirection = -1.0f;
    RevolutionSpeed = GetRevolutionSpeed(OrbitInDays, OrbitHeight, OrbitWidth);   
    SetActorLabel(FS_CelestialName);
}

void AMyEarth::OrbitAroundSun()
{
     Super::OrbitAroundSun();
    //Assign New Location
     this->SetActorLocation(MeshXYZ);

     //To show the planet distance from Sun
     DistanceFromSun = sqrt(MeshXYZ.X * MeshXYZ.X + MeshXYZ.Y * MeshXYZ.Y);
     /*return DistanceFromSun;*/
}

void AMyEarth::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    OrbitAroundSun();
}

void AMyEarth::BeginPlay()
{
    SetActorScale3D(FVector((Diameter)*ScaleMultiplier));
    Super::BeginPlay();   
}
