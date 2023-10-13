// Fill out your copyright notice in the Description page of Project Settings.


#include "MyJupiter.h"

AMyJupiter::AMyJupiter()
{
    FS_CelestialName = "JUPITER";
    MyStaticMeshComponent->SetMaterial(0, SGSettings->JupiterMaterial.LoadSynchronous());
    Mass = 1898.f;
    Diameter = 142984.0f;
    OrbitInDays = 4332.82f;
    OrbitWidth = 7000.0f;
    OrbitHeight = 8000.0f;
    RotationPerOrbit = 4328.9f;
    AxisRotationDirection = -1.0f;
    RevolutionSpeed = GetRevolutionSpeed(OrbitInDays, OrbitHeight, OrbitWidth);
    SetActorLabel(FS_CelestialName);

}

void AMyJupiter::OrbitAroundSun()
{
    Super::OrbitAroundSun();
    //Assign New Location
    this->SetActorLocation(MeshXYZ);

    //To show the planet distance from Sun
    DistanceFromSun = sqrt(MeshXYZ.X * MeshXYZ.X + MeshXYZ.Y * MeshXYZ.Y);
    /*return DistanceFromSun;*/
}

void AMyJupiter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    OrbitAroundSun();
}

void AMyJupiter::BeginPlay()
{
    SetActorScale3D(FVector((Diameter)*ScaleMultiplier));
    Super::BeginPlay();
}