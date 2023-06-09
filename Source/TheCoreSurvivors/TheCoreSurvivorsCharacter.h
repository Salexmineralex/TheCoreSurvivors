// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExperienceComponent.h"
#include "LifeComponent.h"
#include "LifeManagerInterface.h"
#include "SpawnActorsComponent.h"
#include "GameFramework/Character.h"
#include "Item.h"
#include "FirstAidKitItem.h"
#include "ExperienceItem.h"
#include "IExpManagerInterface.h"
#include "ThrowableKnifeSpawnerComponent.h"
#include "TheCoreSurvivorsCharacter.generated.h"


UCLASS(config=Game)
class ATheCoreSurvivorsCharacter : public ACharacter,public ILifeManagerInterface
{
	GENERATED_BODY()


	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = Components,meta = (AllowPrivateAccess = "true"))
	ULifeComponent* _LifeComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = Components,meta = (AllowPrivateAccess = "true"))
	UExperienceComponent* _EXPComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = Components,meta = (AllowPrivateAccess = "true"))
	USpawnActorsComponent* _SpawnActor = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly,Category = Components,meta = (AllowPrivateAccess = "true"))
	UThrowableKnifeSpawnerComponent* _ThowableKnifeSpawner = nullptr;
	
	
public:
	ATheCoreSurvivorsCharacter();

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Input)
	float TurnRateGamepad;

	//LifeInterface
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent, Category = "Damage")
	void ReduceAmount(float damage); virtual void ReduceAmount_Implementation(float damage) override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Damage")
	void RestoreAmount(float recover); virtual void RestoreAmount_Implementation(float recover) override;
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Damage")
	void StartDamageOverTime(float dps); virtual void StartDamageOverTime_Implementation(float dps) override;

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable, Category = "Damage")
	void StopDamageOverTime(); virtual void StopDamageOverTime_Implementation() override ;

	UFUNCTION()
	void OnItemOverlap(UPrimitiveComponent* OverlappedComponent, 
		AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent* sphereCollision;


	USphereComponent* GetCollisionComponent() const;

protected:

	void BeginPlay() override;
	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	/** 
	 * Called via input to turn at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void TurnAtRate(float Rate);

	/**
	 * Called via input to turn look up/down at a given rate. 
	 * @param Rate	This is a normalized rate, i.e. 1.0 means 100% of desired turn rate
	 */
	void LookUpAtRate(float Rate);

	/** Handler for when a touch input begins. */
	void TouchStarted(ETouchIndex::Type FingerIndex, FVector Location);

	/** Handler for when a touch input stops. */
	void TouchStopped(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION()
	void KillPlayer();

	UFUNCTION()
	void LevelUp();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	// End of APawn interface

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};




