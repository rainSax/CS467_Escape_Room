// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "RetractBar.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CS467_ESCAPE_ROOM_API URetractBar : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	URetractBar();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OpenBar(float dt);
	void CloseBar(float dt);
	float TotalMassOfActors() const;

private:
	float InitialZValue;
	float CurrentZValue;
	float FullOpen;
	float BarLastOpened = 0.f;

	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;

	UPROPERTY(EditAnywhere)
		float MassToOpenBars = 60.f;

	UPROPERTY(EditAnywhere)
		float BarCloseDelay = .2f;

	UPROPERTY(EditAnywhere)
		float BarOpenSpeed = FMath::RandRange(.1f, 2.f);

	UPROPERTY(EditAnywhere)
		float BarCloseSpeed = FMath::RandRange(.1f, 2.f);

	float LastDoorOpenTime;

	AActor* Owner;
		
};
