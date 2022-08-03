// MIT License - Copyright (c) 2022 Jared Cook

#pragma once
#include "FCEasing.h"
#include "FCTweenInstance.h"
#include "FCTweenInstanceFloat.h"
#include "FCTweenInstanceQuat.h"
#include "FCTweenInstanceVector.h"
#include "FCTweenInstanceVector2D.h"
#include "FCTweenManager.h"

FCTWEEN_API DECLARE_LOG_CATEGORY_EXTERN(LogFCTween, Log, All)

class FCTWEEN_API FCTween
{
private:
	static FCTweenManager<FCTweenInstanceFloat>* FloatTweenManager;
	static FCTweenManager<FCTweenInstanceVector>* VectorTweenManager;
	static FCTweenManager<FCTweenInstanceVector2D>* Vector2DTweenManager;
	static FCTweenManager<FCTweenInstanceQuat>* QuatTweenManager;

	static int NumReservedFloat;
	static int NumReservedVector;
	static int NumReservedVector2D;
	static int NumReservedQuat;

public:
	static void Initialize();
	static void Deinitialize();

	/**
	 * @brief Ensure there are at least this many tweens in the recycle pool. Call this at game startup to increase your initial
	 * capacity for each type of tween, if you know you will be needing more and don't want to allocate memory during the game.
	 */
	static void EnsureCapacity(int NumFloatTweens, int NumVectorTweens, int NumVector2DTweens, int NumQuatTweens);
	/**
	 * @brief Add more tweens to the recycle pool. Call this at game startup to increase your initial capacity if you know you will
	 * be needing more and don't want to allocate memory during the game.
	 */
	static void EnsureCapacity(int NumTweens);
	static void Update(float UnscaledDeltaSeconds, float DilatedDeltaSeconds, bool bIsGamePaused);
	static void ClearActiveTweens();

	/**
	 * @brief compare the current reserved memory for tweens against the initial capacity, to tell the developer if initial capacity needs to be increased
	 */
	static int CheckTweenCapacity();

	/**
	 * @brief Convenience function for UFCEasing::Ease()
	 */
	static float Ease(float t, EFCEase EaseType);

	static FCTweenInstanceFloat* Play(
		float Start, float End, TFunction<void(float)> OnUpdate, float DurationSecs, EFCEase EaseType = EFCEase::OutQuad);

	static FCTweenInstanceVector* Play(
		FVector Start, FVector End, TFunction<void(FVector)> OnUpdate, float DurationSecs, EFCEase EaseType = EFCEase::OutQuad);

	static FCTweenInstanceVector2D* Play(FVector2D Start, FVector2D End, TFunction<void(FVector2D)> OnUpdate, float DurationSecs,
		EFCEase EaseType = EFCEase::OutQuad);

	static FCTweenInstanceQuat* Play(
		FQuat Start, FQuat End, TFunction<void(FQuat)> OnUpdate, float DurationSecs, EFCEase EaseType = EFCEase::OutQuad);
};
