// MIT License - Copyright 2026 Jared Cook
#pragma once

#include "CoreMinimal.h"
#include "FCEasing.h"

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
	uint8 bIsComplete : 1;

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
	TFunction<void()> OnStart;
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
	 * How many times to replay the loop. A single loop includes the optional yoyo. Use -1 for infinity
	 */
	FCTweenInstance* SetLoops(int InNumLoops);

	/**
	 * seconds to wait before starting another loop
	 */
	FCTweenInstance* SetLoopDelay(float InLoopDelaySecs);

	/**
	 * interpolate backwards after reaching the end
	 */
	FCTweenInstance* SetYoyo(bool bInShouldYoyo);

	/**
	 * seconds to wait before yoyo-ing backwards
	 */
	FCTweenInstance* SetYoyoDelay(float InYoyoDelaySecs);

	/**
	 * multiply the time delta by this number to speed up or slow down the tween. Only positive numbers allowed.
	 */
	FCTweenInstance* SetTimeMultiplier(float InTimeMultiplier);

	/**
	 * set EaseParam1 to fine-tune specific equations. Elastic: Amplitude (1.0) / Back: Overshoot (1.70158) / Stepped: Steps
	 * (10) / Smoothstep: x0 (0)
	 */
	FCTweenInstance* SetEaseParam1(float InEaseParam1);

	/**
	 * set EaseParam2 to fine-tune specific equations. Elastic: Period (0.2) / Smoothstep: x1 (1)
	 */
	FCTweenInstance* SetEaseParam2(float InEaseParam2);

	/**
	 * let this tween run while the game is paused
	 */
	FCTweenInstance* SetCanTickDuringPause(bool bInCanTickDuringPause);

	/**
	 * let this tween run while the game is paused
	 */
	FCTweenInstance* SetUseGlobalTimeDilation(bool bInUseGlobalTimeDilation);

	/**
	 * Automatically recycles this instance after the tween is complete (or Destroy() is called)
	 */
	FCTweenInstance* SetAutoDestroy(bool bInShouldAutoDestroy);

	/**
	 * This lambda will be called when the tween first begins, after the initial Delay timer. Called again if Restart() is triggered. Not called on loops.
	 */
	FCTweenInstance* SetOnStart(TFunction<void()> Handler);
	FCTweenInstance* SetOnYoyo(TFunction<void()> Handler);
	FCTweenInstance* SetOnLoop(TFunction<void()> Handler);
	FCTweenInstance* SetOnComplete(TFunction<void()> Handler);

	/**
	 * Reset variables and start a fresh tween
	 */
	void InitializeSharedMembers(float InDurationSecs, EFCEase InEaseType);
	/**
	 * called on the first frame this tween is updated, to set up any options that have been defined
	 */
	void Start();
	/**
	 * Takes the existing tween settings and restarts the timer, to play it again from the start
	 */
	void Restart();
	/**
	 * Stop tweening and mark this instance for recycling
	 */
	void Destroy();
	/**
	 * Stop tweening and mark this instance for recycling. Same as Destroy().
	 */
	void Stop();
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
