// Shoot Them Up Game. All Rights Reserved.


#include "Weapons/Components/STUWeaponFXComponent.h"

#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

USTUWeaponFXComponent::USTUWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponFXComponent::PlayImpactEffects(const FHitResult& Hit)
{
    auto ImpactData = DefaultImpactData;

    if(Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if(ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }
    // spawn niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), //
        ImpactData.NiagaraEffect,                              //
        Hit.ImpactPoint,                                       //
        Hit.ImpactNormal.Rotation());

    // spawn decal
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),
        ImpactData.DecalData.Material, //
        ImpactData.DecalData.Size,     //
        Hit.ImpactPoint,               //
        Hit.ImpactNormal.Rotation());

    if(DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    }
}