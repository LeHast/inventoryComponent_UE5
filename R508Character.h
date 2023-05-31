// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Public/CharacterInterface.h"
#include "R508Character.generated.h"

UCLASS(Blueprintable)
class AR508Character : public ACharacter, public ICharacterInterface
{
	GENERATED_BODY()

	AR508Character();

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int zoomRate;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_Interact;


public:
	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }


	// Handles input for moving forward and backward.
	UFUNCTION(BlueprintCallable)
	void MoveForward(float Value, float y);

	UFUNCTION(BlueprintCallable)
	void Zoom(float Value);

	
	// Current Weapon
	UFUNCTION(BlueprintCallable)
	void DisplayWeapon(UItemDataAsset* weaponData) override;

	virtual void Tick(float DeltaSeconds) override;

private:
	// Current Weapon
	UPROPERTY(VisibleAnywhere, Category = "Current Item")
	bool HasWeapon;

	UPROPERTY(VisibleAnywhere, Category = "Current Item")
	UStaticMeshComponent* CurrentWeaponMesh;


private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UFUNCTION(BlueprintCallable)
	void Interact();

	UFUNCTION(BlueprintCallable)
	void PickUp();

	void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	virtual void BeginPlay() override;

	
};

