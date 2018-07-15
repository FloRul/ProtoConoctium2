// Fill out your copyright notice in the Description page of Project Settings.

#include "SpherePlayerController.h"
#include "Components/InputComponent.h"
#include "SpherePlayer.h"
#include "Engine/World.h"
#include "EngineUtils.h"

void ASpherePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAxis("RollRight", this, &ASpherePlayerController::RollRight);
	InputComponent->BindAxis("RollForward", this, &ASpherePlayerController::RollForward);
	InputComponent->BindAxis("Attract", this, &ASpherePlayerController::Attract);
	InputComponent->BindAxis("Repulse", this, &ASpherePlayerController::Repulse);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ASpherePlayerController::Jump);
}

// -------------- All of the following method are delegated to the pawn for the movement -------------- //
// *****************************************************************************************************//
void ASpherePlayerController::RollRight(float value) { if (GetSpherePlayerPawn()) { GetSpherePlayerPawn()->RollRight(value); } }

// Delegated to the pawn
void ASpherePlayerController::RollForward(float value) { if (GetSpherePlayerPawn()) { GetSpherePlayerPawn()->RollForward(value); } }

// Delegated to the pawn
void ASpherePlayerController::Jump() { if (GetSpherePlayerPawn()) { GetSpherePlayerPawn()->Jump(); } }

void ASpherePlayerController::Attract(float value)
{
	ASpherePlayer * otherP = GetOtherPlayerController() ? GetOtherPlayerController()->GetSpherePlayerPawn() : nullptr;
	GetSpherePlayerPawn()->Attract(otherP, value);
}

void ASpherePlayerController::Repulse(float value)
{
	ASpherePlayer * otherP = GetOtherPlayerController() ? GetOtherPlayerController()->GetSpherePlayerPawn() : nullptr;
	GetSpherePlayerPawn()->Repulse(otherP, value);
}
// *****************************************************************************************************//
// -----------------------------------------------------------------------------------------------------//


ASpherePlayerController * ASpherePlayerController::GetOtherPlayerController()
{
	ASpherePlayerController * otherPController = nullptr;
	// for all the player controller in game
	for (TActorIterator<ASpherePlayerController>PControllerItr(GetWorld()); PControllerItr; ++PControllerItr)
	{
		// if the selected player controller id is different from OUR id
		if (PControllerItr->GetInputIndex() != GetInputIndex()) { otherPController = *PControllerItr; }
	}
	return otherPController;
}

void ASpherePlayerController::BeginPlay() { Super::BeginPlay(); }

ASpherePlayer* ASpherePlayerController::GetSpherePlayerPawn()
{
	return (GetPawn()) ? Cast<ASpherePlayer>(GetPawn()) : nullptr;
}



