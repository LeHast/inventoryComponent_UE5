// Copyright Epic Games, Inc. All Rights Reserved.

#include "R508Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "Materials/Material.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InventoryComponent.h"
#include "Engine/StaticMeshActor.h"  // Include the header for AStaticMeshActor
#include "Components/StaticMeshComponent.h"  // Include the header for UStaticMeshComponent
#include "Kismet/GameplayStatics.h"  // Include the header for UGameplayStatics
#include "./ItemDataAsset.h"
#include "Components/StaticMeshComponent.h"  // Include the header for UStaticMeshComponent

#include "Engine/World.h"

AR508Character::AR508Character()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;



	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1300.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	zoomRate = 50;

	// Weapon
	CurrentWeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CurrentWeaponMesh"));  // Create the static mesh component
	CurrentWeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CurrentWeaponMesh->SetCollisionResponseToAllChannels(ECR_Ignore);
	CurrentWeaponMesh->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetIncludingScale, FName("Hand_RSocket"));
	HasWeapon = false;

}


void AR508Character::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

}


void AR508Character::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}


void AR508Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(IA_Interact, ETriggerEvent::Started, this, &AR508Character::Interact);

	}
}

void AR508Character::Interact()
{

}

void AR508Character::PickUp()
{

}


// Blueprint use
void AR508Character::MoveForward(float x, float y)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, x);
	
	Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, y);
}

// Blueprint use
void AR508Character::Zoom(float value) {

	CameraBoom->TargetArmLength += value * zoomRate;


}

void AR508Character::DisplayWeapon(UItemDataAsset* weaponData)
{
	if (IsValid(weaponData)) 
	{
		CurrentWeaponMesh->SetStaticMesh(weaponData->GetStaticMesh());
		HasWeapon = true;
		UE_LOG(LogTemp, Warning, TEXT("DisplayWeapon"));
	}

}
