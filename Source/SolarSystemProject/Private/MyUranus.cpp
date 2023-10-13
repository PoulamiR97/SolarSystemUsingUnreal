// Fill out your copyright notice in the Description page of Project Settings.


#include "MyUranus.h"

AMyUranus::AMyUranus()
{
    FS_CelestialName = "URANUS";
    MyStaticMeshComponent->SetMaterial(0, SGSettings->UranusMaterial.LoadSynchronous());
    Mass = 86.8f;
    Diameter = 51118.0f;
    OrbitInDays = 30687.15f;
    OrbitWidth = 11000.0f;
    OrbitHeight = 12000.0f;
    RotationPerOrbit = 34663.65f;
    AxisRotationDirection = 1.0f;
    RevolutionSpeed = GetRevolutionSpeed(OrbitInDays, OrbitHeight, OrbitWidth);
    SetActorLabel(FS_CelestialName);

}

void AMyUranus::OrbitAroundSun()
{
    Super::OrbitAroundSun();
    //Assign New Location
    this->SetActorLocation(MeshXYZ);

    //To show the planet distance from Sun
    DistanceFromSun = sqrt(MeshXYZ.X * MeshXYZ.X + MeshXYZ.Y * MeshXYZ.Y);
}

void AMyUranus::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    OrbitAroundSun();
}

void AMyUranus::BeginPlay()
{
    SetActorScale3D(FVector((Diameter)*ScaleMultiplier));
    Super::BeginPlay();
}