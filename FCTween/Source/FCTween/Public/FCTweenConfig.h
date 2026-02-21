// MIT License - Copyright 2026 Jared Cook
#pragma once
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"

#include "FCTweenConfig.generated.h"

UCLASS(Config = Game, DefaultConfig, meta = (DisplayName = "Fresh Cooked Tweens"))
class FCTWEEN_API UFCTweenConfig : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UFCTweenConfig();
	virtual FName GetContainerName() const override;

	UPROPERTY(Config, EditAnywhere, Category="Performance")
	int FloatTweenCapacity = 50;

	UPROPERTY(Config, EditAnywhere, Category="Performance")
	int Vector2TweenCapacity = 50;

	UPROPERTY(Config, EditAnywhere, Category="Performance")
	int Vector3TweenCapacity = 50;

	UPROPERTY(Config, EditAnywhere, Category="Performance")
	int QuatTweenCapacity = 10;
};
