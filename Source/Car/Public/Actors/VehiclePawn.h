// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehiclePawn.h"
#include "VehiclePawn.generated.h"

/**
 * 
 */
UCLASS()
class CAR_API AVehiclePawn : public AWheeledVehiclePawn
{
	GENERATED_BODY()
	
public:
	AVehiclePawn();
	virtual void Tick(float DeltaSeconds) override;

	// Enhanced Input Implemented
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	/* For Throttle and Steering */
	UFUNCTION(BlueprintCallable)
	void ApplyThrottle(const FInputActionValue & Value);
	void ApplySteering(const FInputActionValue & Value);

	/* LookUp and Turn */
	void LookUp(const FInputActionValue & Value);
	void Turn(const FInputActionValue & Value);

	/* Handbrake */
	void HandbrakePressed();
	void HandbrakeReleased();



protected:

	UPROPERTY(Category="Camera",EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	class USpringArmComponent* springArm;
	UPROPERTY(Category="Camera",EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess="true"))
	class UCameraComponent* camera;
	UPROPERTY(EditDefaultsOnly,Category="Values",BlueprintReadWrite);
	float carSpeed=10.0f; // Not used
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext * inputMapping;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction * inputMoveForward;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction * inputsteer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction * inputbrake;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enhanced Input", meta = (AllowPrivateAccess = "true"))
	class UInputAction * inputmouseturn;
};
