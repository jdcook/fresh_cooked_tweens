// MIT License - Copyright (c) 2022 Jared Cook
#pragma once
#include "FCTweenInstance.h"
#include "Kismet/BlueprintAsyncActionBase.h"

#include "FCTweenBPAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTweenEventOutputPin);

UCLASS(Abstract, BlueprintType, meta = (ExposedAsyncProxy = AsyncTask))
class FCTWEEN_API UFCTweenBPAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	float DurationSecs;
	EFCEase EaseType;
	float Delay;
	int Loops;
	float LoopDelay;
	bool bYoyo;
	float YoyoDelay;
	bool bCanTickDuringPause;
	bool bUseGlobalTimeDilation;
	float EaseParam1;
	float EaseParam2;

	bool bUseCustomCurve;
	UPROPERTY()
	UCurveFloat* CustomCurve;

	FCTweenInstance* TweenInstance = nullptr;

	UPROPERTY(BlueprintAssignable, AdvancedDisplay)
	FTweenEventOutputPin OnLoop;

	UPROPERTY(BlueprintAssignable, AdvancedDisplay)
	FTweenEventOutputPin OnYoyo;

	UPROPERTY(BlueprintAssignable, AdvancedDisplay)
	FTweenEventOutputPin OnComplete;

	virtual void Activate() override;
	virtual FCTweenInstance* CreateTween();
	virtual FCTweenInstance* CreateTweenCustomCurve();
	virtual void SetSharedTweenProperties(float InDurationSecs, float InDelay, int InLoops, float InLoopDelay, bool InbYoyo,
		float InYoyoDelay, bool bInCanTickDuringPause, bool bInUseGlobalTimeDilation);
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category = "Tween")
	void Pause();
	UFUNCTION(BlueprintCallable, Category = "Tween")
	void Unpause();
	UFUNCTION(BlueprintCallable, Category = "Tween")
	void Restart();
	UFUNCTION(BlueprintCallable, Category = "Tween")
	void Stop();
	UFUNCTION(BlueprintCallable, Category = "Tween")
	void SetTimeMultiplier(float Multiplier);
};
