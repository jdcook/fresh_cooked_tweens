#pragma once
#include "FCEasing.h"
#include "FCTweenInstance.h"
#include "FCTweenInstanceFloat.h"
#include "FCTweenInstanceQuat.h"
#include "FCTweenInstanceVector.h"
#include "FCTweenInstanceVector2D.h"
#include "FCTweenManager.h"

class FCTWEEN_API FCTween
{
private:
	static FCTweenManager<FCTweenInstanceFloat>* FloatTweenManager;
	static FCTweenManager<FCTweenInstanceVector>* VectorTweenManager;
	static FCTweenManager<FCTweenInstanceVector2D>* Vector2DTweenManager;
	static FCTweenManager<FCTweenInstanceQuat>* QuatTweenManager;

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
	static void Update(float DeltaTime, bool bIsGamePaused);
	static void ClearActiveTweens();

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
