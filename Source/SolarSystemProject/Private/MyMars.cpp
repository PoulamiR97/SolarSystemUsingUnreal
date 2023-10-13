// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMars.h"

AMyMars::AMyMars()
{
    FS_CelestialName = "MARS";
    MyStaticMeshComponent->SetMaterial(0, SGSettings->MarsMaterial.LoadSynchronous());
    Mass = 0.642f;
    Diameter = 6792.0f;
    OrbitInDays = 689.98f;
    OrbitWidth = 4000.0f;
    OrbitHeight = 5000.0f;
    RotationPerOrbit = 686.2f;
    AxisRotationDirection = -1.0f;
    RevolutionSpeed = GetRevolutionSpeed(OrbitInDays, OrbitHeight, OrbitWidth);
    SetActorLabel(FS_CelestialName);

}

void AMyMars::OrbitAroundSun()
{
    Super::OrbitAroundSun();
    //Assign New Location
    this->SetActorLocation(MeshXYZ);

    //To show the planet distance from Sun
    DistanceFromSun = sqrt(MeshXYZ.X * MeshXYZ.X + MeshXYZ.Y * MeshXYZ.Y);
    /*return DistanceFromSun;*/
}

void AMyMars::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    OrbitAroundSun();
}

void AMyMars::BeginPlay()
{
    SetActorScale3D(FVector((Diameter)*ScaleMultiplier));
    Super::BeginPlay();
}