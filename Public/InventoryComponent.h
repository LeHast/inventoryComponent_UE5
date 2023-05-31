

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryInterface.h"
#include "InventoryComponent.generated.h"

class APick_Up_Item;
class UItemDataAsset;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), BlueprintType)
class R508_API UInventoryComponent : public UActorComponent, public IInventoryInterface
{
	GENERATED_BODY()


	UInventoryComponent();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap<UItemDataAsset*, int32> ResourcesInventory;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Inventory")
	TMap <int32, UItemDataAsset*> WeaponInentoryMap;

	UPROPERTY(EditAnywhere, Category = "Inventory")
	TArray <UItemDataAsset*> WeaponInentory;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int MaxWeaponsInventorySpaces;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory")
	int MaxResourcesInventorySpaces;

	UPROPERTY(VisibleAnywhere, Category = "Inventory")
	TArray <APick_Up_Item*> ItemQueue;

	// Current weapon
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory|Current Item")
	bool HasWeapon;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Inventory|Current Item")
	UItemDataAsset* CurrentWeapon;

	// Input Mapping
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* IA_PickUp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AI_WeaponSlot1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AI_WeaponSlot2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AI_WeaponSlot3;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void PickUpItem();
	void DestroyTempData(APick_Up_Item* item);

	bool AddResources(UItemDataAsset* item);
	bool AddWeapon(UItemDataAsset* weapon);


	void SetCurrentWeapon(const int currentNumber);
	FORCEINLINE void SetCurrent1() { SetCurrentWeapon(0); };
	FORCEINLINE void SetCurrent2() { SetCurrentWeapon(1); };
	FORCEINLINE void SetCurrent3() { SetCurrentWeapon(2); };
public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		bool RemoveWeapon(int slot);


// Inventory Interaface
public:
	virtual bool AddToInventoryInterface(APick_Up_Item* itemData) override;
	virtual bool DeleteFromInventoryInterface(APick_Up_Item* item) override;
	virtual void InitializeComponent() override;
	UFUNCTION(BlueprintCallable)
	virtual ESecondTypeWeapon GetSecondTypeWeaponInterface() override;

};
