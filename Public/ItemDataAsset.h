// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
//
#include "./EEnumR508.h"

//
#include "ItemDataAsset.generated.h"

class UStaticMesh;
/**
 * 
 */
UCLASS()
class R508_API UItemDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EEnumR508 TypeOfItem;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	ESecondTypeWeapon SecondType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	UStaticMesh* StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	int Price;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	int Size;

public:

	FORCEINLINE EEnumR508 GetItemType() { return TypeOfItem; }
	FORCEINLINE ESecondTypeWeapon GetSecondType() { return SecondType; }
	FORCEINLINE UStaticMesh* GetStaticMesh() { return StaticMesh; }
	FORCEINLINE FString GetName() { return Name; }
	FORCEINLINE int GetSize() { return Size; }


};
