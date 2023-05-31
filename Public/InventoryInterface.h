

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "./EEnumR508.h"
#include "InventoryInterface.generated.h"


class APick_Up_Item;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryInterface : public UInterface
{
	GENERATED_BODY()
};


/**
 * 
 */
class R508_API IInventoryInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.

	
public:

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "YourInterface")
	virtual bool AddToInventoryInterface(APick_Up_Item* item) { return false; }
	virtual bool DeleteFromInventoryInterface(APick_Up_Item* item) { return false; }
	virtual ESecondTypeWeapon GetSecondTypeWeaponInterface() {return ESecondTypeWeapon();}


};
