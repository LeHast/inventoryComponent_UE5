

#include "Pick_Up_Item.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"

#include "InventoryInterface.h"
#include "InventoryComponent.h"

// Sets default values
APick_Up_Item::APick_Up_Item()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	Capsule->SetCapsuleSize(125.f, 125.f);
	Capsule->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Capsule->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	Capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Ignore);
	Capsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RootComponent = Capsule;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(RootComponent);
	StaticMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}
// Called when the game starts or when spawned
void APick_Up_Item::BeginPlay()
{
	Super::BeginPlay();

	Capsule->OnComponentBeginOverlap.AddDynamic(this, &APick_Up_Item::CapsuleOnBeginOverlap);
	Capsule->OnComponentEndOverlap.AddDynamic(this, &APick_Up_Item::CapsuleOnEndOverlap);

}

// Called every frame
void APick_Up_Item::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APick_Up_Item::CapsuleOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Begin Over"));

	UInventoryComponent* component = Cast<UInventoryComponent>(OtherActor->GetComponentByClass(UInventoryComponent::StaticClass()));
	if (component && component->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
	{
		IInventoryInterface* inventoryInterface = Cast<IInventoryInterface>(component);
		inventoryInterface->AddToInventoryInterface(this);		
	}
}

void APick_Up_Item::CapsuleOnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("----"));
	UInventoryComponent* component = Cast<UInventoryComponent>(OtherActor->GetComponentByClass(UInventoryComponent::StaticClass()));
	if (component && component->GetClass()->ImplementsInterface(UInventoryInterface::StaticClass()))
	{
		IInventoryInterface* inventoryInterface = Cast<IInventoryInterface>(component);
		inventoryInterface->DeleteFromInventoryInterface(this);
		UE_LOG(LogTemp, Warning, TEXT("++++"));

	}

}

void APick_Up_Item::DestroyActor()
{
	UE_LOG(LogTemp, Warning, TEXT("Destroying"));
	Capsule->OnComponentEndOverlap.Clear();
	this->Destroy();
}

void APick_Up_Item::Interact()
{
}


void APick_Up_Item::PickUpItem()
{


}
