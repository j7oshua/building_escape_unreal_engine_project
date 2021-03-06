// Copyright Joshua Grimard 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	float Reach = 100.f;

	UPROPERTY()
		UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UPROPERTY()
		UInputComponent* PawnInput = nullptr;

	FVector LineTraceEnd;
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	void Grab();
	void Released();
	void FindPhysicsHandle();
	void SetupInputComponent();
	void SetLineTraceEnd();

	//Return the first actor within reach with a physics body
	FHitResult GetFirstPhysicsBodyInReach() const;


};
