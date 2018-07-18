#include "SpherePlayer.h"
#include "Components/StaticMeshComponent.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASpherePlayer::ASpherePlayer()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ASpherePlayer::SetBodySphereMeshComp(UStaticMeshComponent * BodySphereComp)
{
	PlayerBody = BodySphereComp;
}

// Called when the game starts or when spawned
void ASpherePlayer::BeginPlay()
{
	Super::BeginPlay();
}

void ASpherePlayer::RollRight(float intensity)
{
	FVector rightForce = FVector(0, MoveSpeed * intensity, 0);
	PlayerBody->AddForce(rightForce, "None", false);
	// Damping is managed in the editor
}

void ASpherePlayer::RollForward(float intensity)
{
	FVector forwardForce = FVector(MoveSpeed * intensity, 0, 0);
	PlayerBody->AddForce(forwardForce, "None", false);
	// Damping is managed in the editor
}

void ASpherePlayer::Jump()
{
	if (IsGrounded()) { PlayerBody->AddImpulse(FVector(0, 0, JumpSpeed)); }
}

// coeff is the amount of axis input but with a sign to differ either the attraction or repulsion
void ASpherePlayer::ApplyForce(ASpherePlayer * otherP, float coeff)
{
	// Get other player location
	FVector otherPLocation = otherP->GetActorLocation();

	// Get the unit vector pointing to other player
	auto otherPDirection = otherPLocation - GetActorLocation();
	auto dist2otherP = otherPDirection.Size();
	auto attractDirection = otherPDirection;
	attractDirection.Normalize();

	// define the attraction coefficient 
	// proportional to the distance to the other player and the intensity
	auto attractCoeff = 1 / dist2otherP;

	// Apply force along with the direction of this vector
	auto finalForce = attractDirection * attractCoeff * ForceMultiplier * coeff;
	PlayerBody->AddForce(finalForce, "None", true);
}

void ASpherePlayer::Attract(ASpherePlayer * OtherPRef, float coeff)
{
	if (OtherPRef)
	{
		ApplyForce(OtherPRef, coeff);
	}

}

void ASpherePlayer::Repulse(ASpherePlayer * OtherPRef, float coeff)
{
	if (OtherPRef)
	{
		ApplyForce(OtherPRef, -coeff);
	}
}

bool ASpherePlayer::IsGrounded()
{
	float RayLength = 80;
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation - FVector::UpVector * RayLength;
	FCollisionQueryParams CollParams;
	FCollisionResponseParams ResParams;
	FHitResult Hit;

	// Detect the Ground trace channel (custom channel 1)
	return GetWorld()->LineTraceSingleByChannel(Hit,
		StartLocation,
		EndLocation,
		ECollisionChannel::ECC_GameTraceChannel1,
		CollParams,
		ResParams);
}

bool ASpherePlayer::LinkOtherPlayer(ASpherePlayer * _OtherP)
{
	OtherPRef = _OtherP;
	return (_OtherP) ? true : false;
}

// Called every frame
void ASpherePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

