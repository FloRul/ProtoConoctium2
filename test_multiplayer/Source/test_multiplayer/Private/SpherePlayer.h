#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SpherePlayer.generated.h"

UCLASS()
class TEST_MULTIPLAYER_API ASpherePlayer : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASpherePlayer();

	UFUNCTION(BlueprintCallable, Category = SetUp)
	void SetBodySphereMeshComp(UStaticMeshComponent * BodySphereComp);

	// Allow the player to move
	void RollRight(float intensity);

	// Allow the player to move
	void RollForward(float intensity);

	void Jump();

	void ApplyForce(ASpherePlayer * otherP, float intensity);

	void Attract(ASpherePlayer* otherP, float intensity);

	void Repulse(ASpherePlayer * otherP, float intensity);

	bool IsGrounded();

	// Managed in BP
	UFUNCTION(BlueprintCallable, Category = "SetUp")
		bool LinkOtherPlayer(ASpherePlayer * _OtherP);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float MoveSpeed = 1000000;

	UPROPERTY(EditDefaultsOnly)
		float JumpSpeed = 5000;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
		float ForceMultiplier = 10E6;

protected:
	UPROPERTY(BlueprintReadOnly)
		UStaticMeshComponent * PlayerBody = nullptr;

	UPROPERTY(BlueprintReadWrite, Category = SetUp)
		ASpherePlayer * OtherPRef = nullptr;

};