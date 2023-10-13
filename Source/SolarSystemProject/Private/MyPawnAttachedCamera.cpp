// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawnAttachedCamera.h"
using namespace std;


// Sets default values
AMyPawnAttachedCamera::AMyPawnAttachedCamera()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    //Create our components
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    TObjectPtr <UStaticMeshComponent>MyMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    MyCameraSpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    MyCameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

    MyMeshComp->SetupAttachment(RootComponent);
    MyMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    MyMeshComp->GetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility);
    MyCameraSpringArmComp->SetupAttachment(MyMeshComp);
    MyCameraComp->SetupAttachment(MyCameraSpringArmComp, USpringArmComponent::SocketName);
    

    //Setting Default Variables and Behavior of the SpringArmComponent
    MyCameraSpringArmComp->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
    MyCameraSpringArmComp->TargetArmLength = 400.f;
    MyCameraSpringArmComp->bEnableCameraLag = true;
    MyCameraSpringArmComp->CameraLagSpeed = 700.0f;

    //Take control of the default Player
    AutoPossessPlayer = EAutoReceiveInput::Player0;

    static ConstructorHelpers::FClassFinder<UUserWidget> BPMenuWidget(TEXT("/Game/Blueprint/WBP_Widget"));

    if (!ensure(BPMenuWidget.Class != nullptr))
        return;
    MyWidgetClass = BPMenuWidget.Class;

}

// Called when the game starts or when spawned
void AMyPawnAttachedCamera::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawnAttachedCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    //Zoom in if ZoomIn button is down, zoom back out if it's not
    {
        if (bZoomingIn)
        {
            ZoomFactor += DeltaTime / 0.5f;         //Zoom in over half a second
        }
        else
        {
            ZoomFactor -= DeltaTime / 0.25f;        //Zoom out over a quarter of a second
        }
        ZoomFactor = FMath::Clamp<float>(ZoomFactor, 0.0f, 1.0f);

        //Blend our camera's FOV and our SpringArm's length based on ZoomFactor
        MyCameraComp->FieldOfView = FMath::Lerp<float>(90.0f, 60.0f, ZoomFactor);
        MyCameraSpringArmComp->TargetArmLength = FMath::Lerp<float>(400.0f, 300.0f, ZoomFactor);
    }

    //Rotate our actor's yaw, which will turn our camera because we're attached to it
    {
        FRotator NewRotation = GetActorRotation();
        NewRotation.Yaw += CameraInput.X;
        SetActorRotation(NewRotation);
    }

    //Rotate our camera's pitch, but limit it so we're always looking downward
    {
        FRotator NewRotation = MyCameraSpringArmComp->GetComponentRotation();
        NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -80.0f, -15.0f);
        MyCameraSpringArmComp->SetWorldRotation(NewRotation);
    }

    //Handle movement based on our "MoveX" and "MoveY" axes
    {
        if (!MovementInput.IsZero())
        {
            //Scale our movement input axis values by 100 units per second
            MovementInput = MovementInput.GetSafeNormal() * 100.0f;
            FVector NewLocation = GetActorLocation();
            NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
            NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
            SetActorLocation(NewLocation);
        }
    }

    if (MyWidget)
    MyWidget->curDistFrmSunVal->SetText(FText::FromString(FString::SanitizeFloat(PlanetActor->DistanceFromSun, 0) + " km"));

}

// Called to bind functionality to input
void AMyPawnAttachedCamera::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

    //Hook up events for "ZoomIn"
    PlayerInputComponent->BindAction("Zoom", IE_Pressed, this, &AMyPawnAttachedCamera::ZoomIn);
    PlayerInputComponent->BindAction("Zoom", IE_Released, this, &AMyPawnAttachedCamera::ZoomOut);
    PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AMyPawnAttachedCamera::InteractPressed);
    PlayerInputComponent->BindAction("InteractRelease", IE_Pressed, this, &AMyPawnAttachedCamera::InteractReleased);

    //Hook up every-frame handling for our four axes
    PlayerInputComponent->BindAxis("MoveFrontBack", this, &AMyPawnAttachedCamera::MoveFrontBack);
    PlayerInputComponent->BindAxis("MoveLeftRight", this, &AMyPawnAttachedCamera::MoveLeftRight);
    PlayerInputComponent->BindAxis("PitchMyCamera", this, &AMyPawnAttachedCamera::PitchMyCamera);
    PlayerInputComponent->BindAxis("YawMyCamera", this, &AMyPawnAttachedCamera::YawMyCamera);

}

void AMyPawnAttachedCamera::InteractReleased()
{
    if (MyWidget) {
        MyWidget->RemoveFromParent();
    }
}

//Input functions
void AMyPawnAttachedCamera::MoveFrontBack(float myAxisVal)
{
    MovementInput.X = FMath::Clamp<float>(myAxisVal, -1.0f, 1.0f);
}

void AMyPawnAttachedCamera::MoveLeftRight(float myAxisVal)
{
    MovementInput.Y = FMath::Clamp<float>(myAxisVal, -1.0f, 1.0f);
}

void AMyPawnAttachedCamera::PitchMyCamera(float myAxisVal)
{
    CameraInput.Y = myAxisVal;
}

void AMyPawnAttachedCamera::YawMyCamera(float myAxisVal)
{
    CameraInput.X = myAxisVal;
}

void AMyPawnAttachedCamera::ZoomIn()
{
    bZoomingIn = true;
}

void AMyPawnAttachedCamera::ZoomOut()
{
    bZoomingIn = false;
}


void AMyPawnAttachedCamera::InteractPressed()
{
    FHitResult HitResult;

    bool bHit = GetLocalViewingPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

    if (bHit)
    {
        HitResult.GetActor()->GetClass()->IsChildOf(AMyCelestialActors::StaticClass());
        PlanetActor = Cast<AMyCelestialActors>(HitResult.GetActor());
        InteractReleased();
        setWidget();
    }
}

void AMyPawnAttachedCamera::MakeSolarSystem(AActor* creator)
{
    TObjectPtr <UWorld> world = creator->GetWorld(); // will return null if actor is not spawned

    // To make sure if world exists
    if (world) {

        const FTransform SpawnLocAndRot;

        TObjectPtr <AMySun> Sun = world->SpawnActorDeferred<AMySun>(AMySun::StaticClass(), SpawnLocAndRot);
        TObjectPtr <AMyMercury> Mercury = world->SpawnActorDeferred<AMyMercury>(AMyMercury::StaticClass(), SpawnLocAndRot);
        TObjectPtr <AMyVenus> Venus = world->SpawnActorDeferred<AMyVenus>(AMyVenus::StaticClass(), SpawnLocAndRot);
        TObjectPtr <AMyEarth> Earth = world->SpawnActorDeferred<AMyEarth>(AMyEarth::StaticClass(), SpawnLocAndRot);
        TObjectPtr <AMyMars> Mars = world->SpawnActorDeferred<AMyMars>(AMyMars::StaticClass(), SpawnLocAndRot);
        TObjectPtr <AMyJupiter> Jupiter = world->SpawnActorDeferred<AMyJupiter>(AMyJupiter::StaticClass(), SpawnLocAndRot);
        TObjectPtr <AMySaturn> Saturn = world->SpawnActorDeferred<AMySaturn>(AMySaturn::StaticClass(), SpawnLocAndRot);
        TObjectPtr <AMyUranus> Uranus = world->SpawnActorDeferred<AMyUranus>(AMyUranus::StaticClass(), SpawnLocAndRot);
        TObjectPtr <AMyNeptune> Neptune = world->SpawnActorDeferred<AMyNeptune>(AMyNeptune::StaticClass(), SpawnLocAndRot);
    }
}

void AMyPawnAttachedCamera::setWidget()
{  
    MyWidget = CreateWidget<UMyUserWidget>(GetWorld(), MyWidgetClass);
    MyWidget->CelestialWidgetName->SetText(FText::FromString(PlanetActor->FS_CelestialName));
    MyWidget->massVal->SetText(FText::FromString(FString::SanitizeFloat(PlanetActor->Mass, 0) + " x (10^24) kg"));
    MyWidget->velocityVal->SetText(FText::FromString(FString::SanitizeFloat(PlanetActor->RevolutionSpeed, 0) + " km/yr"));
    MyWidget->diameterVal->SetText(FText::FromString(FString::SanitizeFloat(PlanetActor->Diameter, 0) + " km"));
    MyWidget->NativeConstruct();
    MyWidget->AddToViewport();
}
