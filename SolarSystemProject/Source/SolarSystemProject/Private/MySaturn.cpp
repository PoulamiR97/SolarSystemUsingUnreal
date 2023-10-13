// Fill out your copyright notice in the Description page of Project Settings.


#include "MySaturn.h"

AMySaturn::AMySaturn()
{
    FS_CelestialName = "SATURN";
    MyStaticMeshComponent->SetMaterial(0, SGSettings->SaturnMaterial.LoadSynchronous());
    Mass = 568.f;
    Diameter = 120536.0f;
    OrbitInDays = 10755.7f;
    OrbitWidth = 9000.0f;
    OrbitHeight = 10000.0f;
    RotationPerOrbit = 10752.9f;
    AxisRotationDirection = -1.0f;
    RevolutionSpeed = GetRevolutionSpeed(OrbitInDays, OrbitHeight, OrbitWidth);;
    SetActorLabel(FS_CelestialName);

}

void AMySaturn::OrbitAroundSun()
{
    Super::OrbitAroundSun();
    //Assign New Location
    this->SetActorLocation(MeshXYZ);

    //To show the planet distance from Sun
    DistanceFromSun = sqrt(MeshXYZ.X * MeshXYZ.X + MeshXYZ.Y * MeshXYZ.Y);
}

void AMySaturn::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    OrbitAroundSun();
}

void AMySaturn::BeginPlay()
{
    SetActorScale3D(FVector((Diameter)*ScaleMultiplier));
    Super::BeginPlay();
}