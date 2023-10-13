// Fill out your copyright notice in the Description page of Project Settings.


#include "MyNeptune.h"

AMyNeptune::AMyNeptune()
{
    FS_CelestialName = "NEPTUNE";
    MyStaticMeshComponent->SetMaterial(0, SGSettings->NeptuneMaterial.LoadSynchronous());
    Mass = 102.f;
    Diameter = 49528.0f;
    OrbitInDays = 60190.03f;
    OrbitWidth = 13000.0f;
    OrbitHeight = 14000.0f;
    RotationPerOrbit = 60148.35f;
    AxisRotationDirection = -1.0f;
    RevolutionSpeed = GetRevolutionSpeed(OrbitInDays, OrbitHeight, OrbitWidth);
    SetActorLabel(FS_CelestialName);
}

void AMyNeptune::OrbitAroundSun()
{
    Super::OrbitAroundSun();
    //Assign New Location
    this->SetActorLocation(MeshXYZ);

    //To show the planet distance from Sun
    DistanceFromSun = sqrt(MeshXYZ.X * MeshXYZ.X + MeshXYZ.Y * MeshXYZ.Y);

}

void AMyNeptune::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    OrbitAroundSun();
}

void AMyNeptune::BeginPlay()
{
    SetActorScale3D(FVector((Diameter)*ScaleMultiplier));
    Super::BeginPlay();
}