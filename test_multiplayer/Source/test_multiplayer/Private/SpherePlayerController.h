// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SpherePlayerController.generated.h"


class ASpherePlayer;
/**
 * 
 */
UCLASS()
class ASpherePlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:
	// Input bindings
	void SetupInputComponent() override;
	ASpherePlayer* GetSpherePlayerPawn();

	// ----Input binded function----// 
	void RollRight(float value);
	void RollForward(float value);
	void Jump();
	void Attract(float value);
	void Repulse(float value);
	// ----------------------------//

	// Return a pointer to the other playerController 
	// Used to find the location of the other player
	ASpherePlayerController * GetOtherPlayerController();


private:
	ASpherePlayer * Player = nullptr;

protected:
	void BeginPlay() override;


	
	
};
