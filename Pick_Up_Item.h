
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "./Public/InteractInterface.h"
#include "Pick_Up_Item.generated.h"

UCLASS(Blueprintable)
class R508_API APick_Up_Item : public AActor, public IInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APick_Up_Item();

	void PickUpItem();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UItemDataAsset* DataAsset;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void CapsuleOnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void CapsuleOnEndOverlap(class UPrimitiveComponent* OverlappedComponent, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	UFUNCTION()
	void DestroyActor();


	FORCEINLINE UItemDataAsset* GetDataAsset() { return DataAsset; }

// Intereact Interface
public:

	virtual void Interact() override;
};
