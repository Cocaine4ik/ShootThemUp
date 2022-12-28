// Shoot Them Up Game. All Rights Reserved.

#include "AI/Services/STUChangeWeaponService.h"
#include "AIController.h"
#include "Components/STUWeaponComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "STUUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogChangeWeaponService, All, All)
USTUChangeWeaponService::USTUChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if(Controller)
    {
        const auto WeaponComponent = STUUtils::GetSTUPlayerComponent<USTUWeaponComponent>(Controller->GetPawn());
        if(WeaponComponent &&Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon(); 
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}