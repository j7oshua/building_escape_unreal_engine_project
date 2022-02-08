// Copyright Joshua Grimard 2022

#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandle();
	SetupInputComponent();
}

void UGrabber::SetupInputComponent()
{
	PawnInput = GetOwner()->FindComponentByClass<UInputComponent>();

	if (PawnInput)
	{
		PawnInput->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		PawnInput->BindAction("Grab", IE_Released, this, &UGrabber::Released);
	}
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing a physics handle component"), *GetOwner()->GetName());
	}
}

void UGrabber::SetLineTraceEnd()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

	if (HitResult.GetActor())
	{
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab, NAME_None, LineTraceEnd);
	}
	
}

void UGrabber::Released()
{
	PhysicsHandle->ReleaseComponent();
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetLineTraceEnd();

	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}

}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{

	FHitResult Hit;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	AActor* ActorHit = Hit.GetActor();

	return Hit;
}

