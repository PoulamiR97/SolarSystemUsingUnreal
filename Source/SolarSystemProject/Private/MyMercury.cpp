// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMercury.h"

AMyMercury::AMyMercury()
{
    FS_CelestialName = "MERCURY";
    //Parent->SetActorLocation({ 0,0,0 });
    MyStaticMeshComponent->SetMaterial(0, SGSettings->MercuryMaterial.LoadSynchronous());
    Mass = 0.330f;
    Diameter = 4879.4f;
    OrbitInDays = 88.0f;
    OrbitWidth = 1000.0f;
    OrbitHeight = 2000.0f;
    RotationPerOrbit = 87.97f;
    AxisRotationDirection = -1.0f;
    RevolutionSpeed = floor( GetRevolutionSpeed(OrbitInDays, OrbitHeight, OrbitWidth) * 100) / 100;;
    SetActorLabel(FS_CelestialName);
}

void AMyMercury::OrbitAroundSun()
{
    Super::OrbitAroundSun();
    //Assign New Location
    this->SetActorLocation(MeshXYZ);

    //To show the planet distance from Sun
    DistanceFromSun = sqrt(MeshXYZ.X * MeshXYZ.X + MeshXYZ.Y * MeshXYZ.Y);
    /*return DistanceFromSun;*/
}

void AMyMercury::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    OrbitAroundSun();
}

void AMyMercury::BeginPlay()
{
    SetActorScale3D(FVector((Diameter)*ScaleMultiplier));
    Super::BeginPlay();
}

