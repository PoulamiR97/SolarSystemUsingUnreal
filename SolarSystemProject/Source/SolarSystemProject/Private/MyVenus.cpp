// Fill out your copyright notice in the Description page of Project Settings.


#include "MyVenus.h"

AMyVenus::AMyVenus()
{
    FS_CelestialName = "VENUS";
    MyStaticMeshComponent->SetMaterial(0, SGSettings->VenusMaterial.LoadSynchronous());
    Mass = 4.87f;
    Diameter = 12104.f;
    OrbitInDays = 224.7f;
    OrbitWidth = 2000.0f;
    OrbitHeight = 3000.0f;
    RotationPerOrbit = 224.7f;
    AxisRotationDirection = 1.0f;
    RevolutionSpeed = GetRevolutionSpeed(OrbitInDays, OrbitHeight, OrbitWidth);
    SetActorLabel(FS_CelestialName);
}

void AMyVenus::OrbitAroundSun()
{
    Super::OrbitAroundSun();
    //Assign New Location
    this->SetActorLocation(MeshXYZ);

    //To show the planet distance from Sun
    DistanceFromSun = sqrt(MeshXYZ.X * MeshXYZ.X + MeshXYZ.Y * MeshXYZ.Y);
}

void AMyVenus::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    OrbitAroundSun();
}

void AMyVenus::BeginPlay()
{
    SetActorScale3D(FVector((Diameter)*ScaleMultiplier));
    Super::BeginPlay();
}