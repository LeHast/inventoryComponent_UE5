


#include "InventoryComponent.h"

#include "ItemDataAsset.h"
#include "../Pick_Up_Item.h"
#include "../R508Character.h"
#include "./ItemDataAsset.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "InputMappingContext.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;


	MaxWeaponsInventorySpaces = 3;
	MaxResourcesInventorySpaces = 64;

	HasWeapon = false;
	CurrentWeapon = nullptr;

	DefaultMappingContext = Cast<UInputMappingContext>(StaticLoadObject(UInputMappingContext::StaticClass(), nullptr, TEXT("/Script/EnhancedInput.InputMappingContext'/Game/AA_GamePlay/Blueprints/Input/IMC_Default.IMC_Default'")));
	IA_PickUp = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/AA_GamePlay/Blueprints/Input/Actions/IA_PickUp.IA_PickUp'")));
	AI_WeaponSlot1 = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/AA_GamePlay/Blueprints/Input/Actions/AI_WeaponSlot1.AI_WeaponSlot1'")));
	AI_WeaponSlot2 = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/AA_GamePlay/Blueprints/Input/Actions/AI_WeaponSlot2.AI_WeaponSlot2'")));
	AI_WeaponSlot3 = Cast<UInputAction>(StaticLoadObject(UInputAction::StaticClass(), nullptr, TEXT("/Script/EnhancedInput.InputAction'/Game/AA_GamePlay/Blueprints/Input/Actions/AI_WeaponSlot3.AI_WeaponSlot3'")));
}

void UInventoryComponent::InitializeComponent()
{
	Super::InitializeComponent();



}


// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	AR508Character* Character = Cast<AR508Character>(GetOwner());
	if (APlayerController* PlayerController = Cast<APlayerController>(Character->GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			// Set the priority of the mapping to 1, so that it overrides the Jump action with the Fire action when using touch input
			Subsystem->AddMappingContext(DefaultMappingContext, 1);
		}

		if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent))
		{
			EnhancedInputComponent->BindAction(IA_PickUp, ETriggerEvent::Started, this, &UInventoryComponent::PickUpItem);
			EnhancedInputComponent->BindAction(AI_WeaponSlot1, ETriggerEvent::Started, this, &UInventoryComponent::SetCurrent1);
			EnhancedInputComponent->BindAction(AI_WeaponSlot2, ETriggerEvent::Started, this, &UInventoryComponent::SetCurrent2);
			EnhancedInputComponent->BindAction(AI_WeaponSlot3, ETriggerEvent::Started, this, &UInventoryComponent::SetCurrent3);
		}
	}
	
}

// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UInventoryComponent::PickUpItem()
{
	if (ItemQueue.Num() > 0) {
		APick_Up_Item* tempItem  = ItemQueue.Last();
		UItemDataAsset* tempItemData = tempItem->GetDataAsset();
		switch (tempItemData->GetItemType())
		{
		case EEnumR508::Weapon:
			if (AddWeapon(tempItemData))
				DestroyTempData(tempItem);
			break;

		//case EEnumR508::Food:
		//	AddResources(tempItemData);
		//	break;

		default:
			if (AddResources(tempItemData))
				DestroyTempData(tempItem);
			break;
		} 
	}

}

void UInventoryComponent::DestroyTempData(APick_Up_Item* item)
{
	UE_LOG(LogTemp, Warning, TEXT("Destroy"));
	ItemQueue.Remove(item);
	item->DestroyActor();
}

bool UInventoryComponent::AddResources(UItemDataAsset* item)
{

	if(ResourcesInventory.Num() < MaxResourcesInventorySpaces)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add resource"));
		int32 s = ResourcesInventory.FindRef(item);
		ResourcesInventory.Add(item, (s + 1));
		return true;
	}


	return false;
}

bool UInventoryComponent::AddWeapon(UItemDataAsset* weapon)
{
	if (WeaponInentory.Num() < MaxWeaponsInventorySpaces)
	{
		UE_LOG(LogTemp, Warning, TEXT("Add weapon"));
		WeaponInentory.Add(weapon);
		return true;
	}
	if (WeaponInentory.Num() == MaxWeaponsInventorySpaces) 
	{
		for (int index = 0; index < MaxWeaponsInventorySpaces; index++)
		{
			if (WeaponInentory[index] == nullptr)
			{
				WeaponInentory[index] = weapon;
				return true;
			}
		}
	}

	return false;
}

bool UInventoryComponent::RemoveWeapon(int slot)
{
	if (IsValid(WeaponInentory[slot]))
	{
		WeaponInentory[slot] = nullptr;
	}
	return false;
}

void UInventoryComponent::SetCurrentWeapon(const int currentNumber)
{
	if (WeaponInentory.Num() <= currentNumber)
		return;
	if (IsValid(WeaponInentory[currentNumber])) {
		CurrentWeapon = WeaponInentory[currentNumber];
		HasWeapon = true;
		AActor * OwnerActor = GetOwner();
		if (OwnerActor != nullptr) {
			// Cast the owning actor to the desired interface type
			ICharacterInterface* InterfaceInstance = Cast<ICharacterInterface>(OwnerActor);
			if (InterfaceInstance != nullptr) {
				InterfaceInstance->DisplayWeapon(CurrentWeapon);  // Replace "MyInterfaceFunction" with the function declared in the interface
			}
		}
	}
}

//***********************
// From interface class
bool UInventoryComponent::AddToInventoryInterface(APick_Up_Item* item)
{
	ItemQueue.Add(item);
	//AddInventory(itemData);
	return false;
}

bool UInventoryComponent::DeleteFromInventoryInterface(APick_Up_Item* item)
{
	ItemQueue.Remove(item);
	return true;
}


ESecondTypeWeapon UInventoryComponent::GetSecondTypeWeaponInterface()
{
	return CurrentWeapon->GetSecondType();
}



//***********************
