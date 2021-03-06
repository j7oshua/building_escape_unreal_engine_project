// Copyright Joshua Grimard 2022

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/AudioComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDING_ESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	void FindAudioComponent();
	void CheckPressurePlate() const;

private:

	float DoorLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
		float TotalMassToOpenDoor = 130.f;

	UPROPERTY(EditAnywhere)
		float DoorSpeedOpen = 1.5f;

	UPROPERTY(EditAnywhere)
		float DoorSpeedClose = 1.5f;

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere)
		float OpenAngle = 90.f;

	UPROPERTY()
		UAudioComponent* AudioComponent = nullptr;

	float InitialYaw;
	float CurrentYaw;
		
};
