// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCelestialActors.h"

#include "Engine.h"
#include <string>
#include <math.h>




using namespace std;

// Sets default values
AMyCelestialActors::AMyCelestialActors()
{

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//DEFAULT DISTANCE
	// This is relative speed, most likely set to Earth so that we can see things moving and not static
	//SpeedBaseLine = 5.0f;

	//SET MESH
	TObjectPtr <USceneComponent> MySceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = MySceneComponent;

	MyStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	MyStaticMeshComponent->SetMobility(EComponentMobility::Movable);
	MyStaticMeshComponent->SetupAttachment(MySceneComponent);
	MyStaticMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	MyStaticMeshComponent->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECollisionResponse::ECR_Block);

	SGSettings = GetDefault<UMyDeveloperSettings>(); // Access via CDO
	MyStaticMeshComponent->SetStaticMesh(SGSettings->SphereMeshAssetPath.LoadSynchronous());


	CelestialSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("My Spline"));
	CelestialSplineComponent->bDrawDebug = true;
	CelestialSplineComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CelestialSplineComponent->SetMaterial(0, MyStaticMeshComponent->GetMaterial(0));
	SplineMeshAsset = SGSettings->SplineMeshAssetPath.LoadSynchronous();
}


//Get Revolution speed of planets
float AMyCelestialActors::GetRevolutionSpeed(float planetOrbitInDays, float a, float b)
{
	float planetSpeed{ 0.0f };
	float perimeter = 2 * PI * sqrt((a * a + b * b) / 2);  // p = 2 * pi() * sqrt((a2 + b2) / 2)
	planetSpeed = perimeter / (planetOrbitInDays / 365);
	return planetSpeed;
}


//Revolution of planets  and also current distance from Sun
void AMyCelestialActors::OrbitAroundSun()
{
	FVector RelativeXYZ;
	FVector ParentXYZ;
	//ParentXYZ = Parent->GetActorLocation();
	
	//Set Parent Location
	ParentXYZ = FVector(0,0,0);

	//Store Local translation
	RelativeXYZ = MyStaticMeshComponent->GetRelativeTransform().GetLocation();
	MeshXYZ = RelativeXYZ;

	//Set MeshXYZ
	MeshXYZ.X = (sin(GetWorld()->GetRealTimeSeconds() * RevolutionSpeed / (180.f * 4 * PI * SpeedScaleFactor * 10)) * OrbitWidth) + ParentXYZ.X;
	MeshXYZ.Y = (cos(GetWorld()->GetRealTimeSeconds() * RevolutionSpeed / (180.f * 4 * PI * SpeedScaleFactor * 10)) * OrbitHeight) + ParentXYZ.Y;
	MeshXYZ.Z = 0.0f;


	// update spline mesh details
	TObjectPtr <USplineMeshComponent> CelestialSplineMeshComponent = NewObject<USplineMeshComponent>(this, USplineMeshComponent::StaticClass());
	//CelestialSplineMeshComponent->SetMaterial(0, MyStaticMeshComponent->GetMaterial(0));
	CelestialSplineMeshComponent->SetMobility(EComponentMobility::Movable);
	CelestialSplineMeshComponent->AttachToComponent(CelestialSplineComponent, FAttachmentTransformRules::KeepRelativeTransform);
	CelestialSplineMeshComponent->SetStaticMesh(SplineMeshAsset);
	CelestialSplineMeshComponent->SetForwardAxis(ESplineMeshAxis::Type::Z, true);
	CelestialSplineMeshComponent->SetStartScale(FVector2D(0.2,0.2), true);
	CelestialSplineMeshComponent->SetEndScale(FVector2D(0.2, 0.2), true);

	// initialize the spline object
	CelestialSplineMeshComponent->RegisterComponentWithWorld(GetWorld());	
	CelestialSplineMeshComponent->CreationMethod = EComponentCreationMethod::UserConstructionScript;

	/*FVector StartSplineMeshPoint = MeshXYZ;*/
	FVector StartSplineMeshPoint = (GetActorLocation().X == 0.0f) ? MeshXYZ : GetActorLocation();
	FVector StartSplineMeshTangent = CelestialSplineComponent->GetTangentAtSplinePoint(CelestialSplineComponent->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
	//FVector EndSplineMeshPoint = MeshXYZ + GetWorld()->GetRealTimeSeconds();
	FVector EndSplineMeshPoint = MeshXYZ;
	FVector EndSplineMeshTangent = CelestialSplineComponent->GetTangentAtSplinePoint(CelestialSplineComponent->GetNumberOfSplinePoints(), ESplineCoordinateSpace::World);
	CelestialSplineMeshComponent->SetStartAndEnd(StartSplineMeshPoint, StartSplineMeshTangent, EndSplineMeshPoint, EndSplineMeshTangent, true);
	CelestialSplineMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}


void AMyCelestialActors::RotateAroundAxis(float DeltaTime)
{
	FRotator3d NewAxisRotation;

	NewAxisRotation.Pitch = 0;  //Y-axis
	NewAxisRotation.Roll = 0;    //X-axis
	NewAxisRotation.Yaw = DeltaTime * (100000 / RotationPerOrbit) * (AxisRotationDirection); //Z-axis
	this->AddActorLocalRotation(NewAxisRotation);
}



// Called when the game starts or when spawned
void AMyCelestialActors::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMyCelestialActors::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AMyCelestialActors::OrbitAroundSun();
	AMyCelestialActors::RotateAroundAxis(DeltaTime);
}
