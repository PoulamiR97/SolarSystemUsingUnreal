// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "MyDeveloperSettings.generated.h"


/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "My Game Settings"))
class SOLARSYSTEMPROJECT_API UMyDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
	
public:

	/* Soft path will be converted to content reference before use */
	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UStaticMesh> SphereMeshAssetPath;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UStaticMesh> SplineMeshAssetPath;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UMaterial> SunMaterial;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UMaterial> MercuryMaterial;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UMaterial> VenusMaterial;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UMaterial> EarthMaterial;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UMaterial> MarsMaterial;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UMaterial> JupiterMaterial;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UMaterial> SaturnMaterial;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UMaterial> UranusMaterial;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
		TSoftObjectPtr<UMaterial> NeptuneMaterial;

	//UMyDeveloperSettings();
};