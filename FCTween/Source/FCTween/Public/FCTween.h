// MIT License - Copyright 2026 Jared Cook
#pragma once
#include "Components/SizeBox.h"
#include "Components/SplineComponent.h"
#include "Components/Widget.h"
#include "FCEasing.h"
#include "FCTweenInstance.h"
#include "FCTweenInstanceFloat.h"
#include "FCTweenInstanceQuat.h"
#include "FCTweenInstanceVector.h"
#include "FCTweenInstanceVector2D.h"
#include "FCTweenManager.h"

FCTWEEN_API DECLARE_LOG_CATEGORY_EXTERN(LogFCTween, Log, All);

class FCTWEEN_API FCTween
{
private:
	static FCTweenManager<FCTweenInstanceFloat>* FloatTweenManager;
	static FCTweenManager<FCTweenInstanceVector2D>* Vector2TweenManager;
	static FCTweenManager<FCTweenInstanceVector>* Vector3TweenManager;
	static FCTweenManager<FCTweenInstanceQuat>* QuatTweenManager;

	static bool bIsInitialized;
	static int NumReservedFloat;
	static int NumReservedVector2;
	static int NumReservedVector3;
	static int NumReservedQuat;

public:
	static void Initialize();
	static void Deinitialize();
	static bool IsInitialized();

	static void Update(float UnscaledDeltaSeconds, float DilatedDeltaSeconds, bool bIsGamePaused);
	static void ClearActiveTweens();

	/**
	 * Compare the current reserved memory for tweens against the initial capacity, to tell the developer if initial capacity needs
	 * to be increased
	 */
	static int CheckTweenCapacity();

	/**
	 * Convenience function for FCEasing::Ease()
	 */
	static float Ease(float t, EFCEase EaseType);

	/**
	 * Play a float tween.
	 */
	static FCTweenInstanceFloat* Play(float Start, float End, TFunction<void(float)> OnUpdate, float DurationSecs, EFCEase EaseType = EFCEase::OutQuad);

	/**
	 * Play a vector2 tween.
	 */
	static FCTweenInstanceVector2D* Play(FVector2D Start, FVector2D End, TFunction<void(FVector2D)> OnUpdate, float DurationSecs, EFCEase EaseType = EFCEase::OutQuad);

	/**
	 * Play a vector tween.
	 */
	static FCTweenInstanceVector* Play(FVector Start, FVector End, TFunction<void(FVector)> OnUpdate, float DurationSecs, EFCEase EaseType = EFCEase::OutQuad);

	/**
	 * Play a quaternion tween.
	 */
	static FCTweenInstanceQuat* Play(FQuat Start, FQuat End, TFunction<void(FQuat)> OnUpdate, float DurationSecs, EFCEase EaseType = EFCEase::OutQuad);

};
