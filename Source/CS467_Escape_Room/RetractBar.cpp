// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/PrimitiveComponent.h"
#include "Engine/World.h"
#include "RetractBar.h"

// Sets default values for this component's properties
URetractBar::URetractBar()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void URetractBar::BeginPlay()
{
	Super::BeginPlay();
	FVector Origin;
	FVector BoxExtent;
	InitialZValue = GetOwner()->GetActorLocation().Z;

	GetOwner()->GetActorBounds(false, Origin, BoxExtent);
	FullOpen = (BoxExtent.Z * 2) * -1;
	FullOpen += InitialZValue;

	if (!PressurePlate)
	{
		UE_LOG(LogTemp, Error, TEXT("%s has retract bar component but no pressure plate set!"), *GetOwner()->GetName());
	}
	
}

// Called every frame
void URetractBar::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TotalMassOfActors() > MassToOpenBars)
	{
		OpenBar(DeltaTime);
		BarLastOpened = GetWorld()->GetTimeSeconds();
	}
	else
	{
		if (GetWorld()->GetTimeSeconds() - BarLastOpened > BarCloseDelay)
		{
			CloseBar(DeltaTime);
		}
	}
}

void URetractBar::OpenBar(float dt)
{
	CurrentZValue = FMath::Lerp(CurrentZValue, FullOpen, dt * BarOpenSpeed);
	FVector OpenLocation = GetOwner()->GetActorLocation();
	OpenLocation.Z = CurrentZValue;
	GetOwner()->SetActorLocation(OpenLocation);
}

void URetractBar::CloseBar(float dt)
{
	CurrentZValue = FMath::Lerp(CurrentZValue, InitialZValue, dt * BarCloseSpeed);
	FVector CloseLocation = GetOwner()->GetActorLocation();
	CloseLocation.Z = CurrentZValue;
	GetOwner()->SetActorLocation(CloseLocation);
}

float URetractBar::TotalMassOfActors() const
{
	float TotalMass = 0.f;

	// Find all overlapping actors
	TArray<AActor*> OverlappingActors;
	if (PressurePlate)
	{
		PressurePlate->GetOverlappingActors(OverlappingActors);
	}

	// Add their masses
	for (AActor* Actor : OverlappingActors)
	{
		// UE_LOG(LogTemp, Warning, TEXT("%s is in the collision volume with mass of %f"), *Actor->GetName(), Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass());
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		// UE_LOG(LogTemp, Warning, TEXT("Total mass is %f"), TotalMass);
	}

	return TotalMass;
}
