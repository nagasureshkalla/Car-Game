// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/VehiclePawn.h"
#include "ChaosWheeledVehicleMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
// static const FName NAME_STEERINPUT("IA_Steering");
// static const FName NAME_THROTTLEINPUT("IA_Throttle");
// static const FName NAME_HANDBRAKEINPUT("IA_Handbrake");
// static const FName NAME_LOOKAROUNDINPUT("IA_LookAround");



AVehiclePawn::AVehiclePawn()
{
	
	UChaosWheeledVehicleMovementComponent* Vehicle=CastChecked<UChaosWheeledVehicleMovementComponent>(GetVehicleMovement());

	Vehicle->Mass=500.0f;
	
	// create a springArm and attach Camera to it 
	springArm=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	springArm->SetupAttachment(GetMesh());
	springArm->TargetArmLength=500.0f;
	springArm->bUsePawnControlRotation=false; // false means camera is sticked to back of car
	camera=CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	camera->SetupAttachment(springArm,USpringArmComponent::SocketName);
	//camera->AttachToComponent(GetMesh(),FAttachmentTransformRules::SnapToTargetIncludingScale,"Mesh");
	camera->FieldOfView=90.0f;

	
	// Torque adjust
	Vehicle -> EngineSetup.TorqueCurve.GetRichCurve()->Reset();
	Vehicle->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(0.0f,400.0f);
	Vehicle->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(890.0f,400.0f);
	Vehicle->EngineSetup.TorqueCurve.GetRichCurve()->AddKey(1697.0f,400.0f);

	

	//Vehicle->DifferentialSetup.DifferentialType= EVehicleDifferential::AllWheelDrive;
	Vehicle->DifferentialSetup.FrontRearSplit= 0.65;
	

	// Automatic Gearbox
	Vehicle->TransmissionSetup.bUseAutomaticGears=true;
	Vehicle->TransmissionSetup.GearChangeTime=0.01f;

	

	
	
}

void AVehiclePawn::Tick(float DeltaSeconds)
{ 
	Super::Tick(DeltaSeconds);
}

void AVehiclePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);


			// For the Depreciated Action and Axis MAppings
	//PlayerInputComponent->BindAxis(NAME_THROTTLEINPUT,this,&AVehiclePawn::ApplyThrottle);
	// PlayerInputComponent->BindAxis(NAME_STEERINPUT,this,&AVehiclePawn::ApplySteering);
	// PlayerInputComponent->BindAxis(NAME_LOOKAROUNDINPUT,this,&AVehiclePawn::LookUp);
	// PlayerInputComponent->BindAction(NAME_HANDBRAKEINPUT,IE_Pressed,this,&AVehiclePawn::HandbrakePressed);
	// PlayerInputComponent->BindAction(NAME_HANDBRAKEINPUT,IE_Released,this,&AVehiclePawn::HandbrakeReleased);
	
 
	// Get the EnhancedInputComponent
	const auto EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	EnhancedInputComponent->BindAction(inputMoveForward, ETriggerEvent::Triggered, this,  &AVehiclePawn::ApplyThrottle);
	EnhancedInputComponent->BindAction(inputsteer, ETriggerEvent::Triggered, this,  &AVehiclePawn::ApplySteering);
	EnhancedInputComponent->BindAction(inputMoveForward, ETriggerEvent::Completed, this,  &AVehiclePawn::ApplyThrottle);
	EnhancedInputComponent->BindAction(inputsteer, ETriggerEvent::Completed, this,  &AVehiclePawn::ApplySteering);
	
	EnhancedInputComponent->BindAction(inputbrake, ETriggerEvent::Triggered, this,  &AVehiclePawn::HandbrakePressed);
	EnhancedInputComponent->BindAction(inputbrake, ETriggerEvent::Completed, this,  &AVehiclePawn::HandbrakeReleased);

	

	//EnhancedInputComponent->BindAction(inputmouseturn, ETriggerEvent::Triggered, this,  &AVehiclePawn::LookUp);
	 
}

void AVehiclePawn::ApplyThrottle(const FInputActionValue & Value)
{
	
	GetVehicleMovementComponent()->SetThrottleInput(Value.Get<float>());
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("My Location is: %f"), speed));
}

void AVehiclePawn::ApplySteering(const FInputActionValue & Value)
{
	
	GetVehicleMovementComponent()->SetSteeringInput(Value.Get<float>());
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("My Location is: %f"), speed));
}

void AVehiclePawn::LookUp(const FInputActionValue & Value)
{
	if(Value.Get<float>() != 0.f)
	{
		AddControllerPitchInput(Value.Get<float>());
	}
}

void AVehiclePawn::Turn(const FInputActionValue & Value)
{
	if(Value.Get<float>() != 0.f)
	{
		AddControllerYawInput(Value.Get<float>());
	}
}

void AVehiclePawn::HandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AVehiclePawn::HandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

