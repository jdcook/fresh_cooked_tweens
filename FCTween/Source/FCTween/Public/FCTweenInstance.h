// MIT License - Copyright (c) 2022 Jared Cook

#pragma once

#include "CoreMinimal.h"
#include "FCEasing.h"

class UFCTweenUObject;
UENUM()
enum class EDelayState : uint8
{
	None,
	Start,
	Loop,
	Yoyo,
};

class FCTWEEN_API FCTweenInstance
{
public:
	float DurationSecs;
	EFCEase EaseType;
	float Counter;
	float DelayCounter;

	uint8 bShouldAutoDestroy : 1;
	uint8 bIsActive : 1;
	uint8 bIsPaused : 1;
	uint8 bShouldYoyo : 1;
	uint8 bIsPlayingYoyo : 1;
	uint8 bCanTickDuringPause : 1;
	uint8 bUseGlobalTimeDilation : 1;

	int NumLoops;
	int NumLoopsCompleted;
	float DelaySecs;
	float LoopDelaySecs;
	float YoyoDelaySecs;
	float TimeMultiplier;
	float EaseParam1;
	float EaseParam2;

	EDelayState DelayState;

private:
	TFunction<void()> OnYoyo;
	TFunction<void()> OnLoop;
	TFunction<void()> OnComplete;

public:
	FCTweenInstance()
	{
	}

	virtual ~FCTweenInstance()
	{
	}

	FCTweenInstance* SetDelay(float InDelaySecs);

	/**
	 * @brief How many times to replay the loop (yoyo included). use -1 for infinity
	 */
	FCTweenInstance* SetLoops(int InNumLoops);

	/**
	 * @brief seconds to wait before starting another loop
	 */
	FCTweenInstance* SetLoopDelay(float InLoopDelaySecs);

	/**
	 * @brief interpolate backwards after reaching the end
	 */
	FCTweenInstance* SetYoyo(bool bInShouldYoyo);

	/**
	 * @brief seconds to wait before yoyo-ing backwards
	 */
	FCTweenInstance* SetYoyoDelay(float InYoyoDelaySecs);

	/**
	 * @brief multiply the time delta by this number to speed up or slow down the tween. Only positive numbers allowed.
	 */
	FCTweenInstance* SetTimeMultiplier(float InTimeMultiplier);

	/**
	 * @brief set EaseParam1 to fine-tune specific equations. Elastic: Amplitude (1.0) / Back: Overshoot (1.70158) / Stepped: Steps
	 * (10) / Smoothstep: x0 (0)
	 */
	FCTweenInstance* SetEaseParam1(float InEaseParam1);

	/**
	 * @brief set EaseParam2 to fine-tune specific equations. Elastic: Period (0.2) / Smoothstep: x1 (1)
	 */
	FCTweenInstance* SetEaseParam2(float InEaseParam2);

	/**
	 * @brief let this tween run while the game is paused
	 */
	FCTweenInstance* SetCanTickDuringPause(bool bInCanTickDuringPause);

	/**
	 * @brief let this tween run while the game is paused
	 */
	FCTweenInstance* SetUseGlobalTimeDilation(bool bInUseGlobalTimeDilation);

	/**
	 * @brief Automatically recycles this instance after tween is complete (Stop() is called)
	 */
	FCTweenInstance* SetAutoDestroy(bool bInShouldAutoDestroy);

	FCTweenInstance* SetOnYoyo(TFunction<void()> Handler);
	FCTweenInstance* SetOnLoop(TFunction<void()> Handler);
	FCTweenInstance* SetOnComplete(TFunction<void()> Handler);

	/**
	 * @brief Reset variables and start a fresh tween
	 */
	void InitializeSharedMembers(float InDurationSecs, EFCEase InEaseType);
	/**
	 * @brief called on the first frame this tween is updated, to set up any options that have been defined
	 */
	void Start();
	/**
	 * @brief Takes the existing tween settings and restarts the timer, to play it again from the start
	 */
	void Restart();
	/**
	 * @brief stop tweening and mark this instance for recycling
	 */
	void Destroy();
	/**
	 * @brief Get a UObject wrapper for this tween. It will recycle the tween automatically when it's Outer is destroyed
	 */
	UFCTweenUObject* CreateUObject(UObject* Outer = (UObject*) GetTransientPackage());
	void Pause();
	void Unpause();
	void Update(float UnscaledDeltaSeconds, float DilatedDeltaSeconds, bool bIsGamePaused = false);

protected:
	virtual void ApplyEasing(float EasedPercent) = 0;

private:
	void CompleteLoop();
	void StartNewLoop();
	void StartYoyo();
};
