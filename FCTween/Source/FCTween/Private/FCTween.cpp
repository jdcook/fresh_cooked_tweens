// MIT License - Copyright 2026 Jared Cook
#include "FCTween.h"

#include "Components/WindowTitleBarAreaSlot.h"
#include "FCTweenConfig.h"
#include "FCTweenManager.h"

DEFINE_LOG_CATEGORY(LogFCTween)

FCTweenManager<FCTweenInstanceFloat>* FCTween::FloatTweenManager = nullptr;
FCTweenManager<FCTweenInstanceVector2D>* FCTween::Vector2TweenManager = nullptr;
FCTweenManager<FCTweenInstanceVector>* FCTween::Vector3TweenManager = nullptr;
FCTweenManager<FCTweenInstanceQuat>* FCTween::QuatTweenManager = nullptr;

bool FCTween::bIsInitialized = false;
int FCTween::NumReservedFloat = 0;
int FCTween::NumReservedVector2 = 0;
int FCTween::NumReservedVector3 = 0;
int FCTween::NumReservedQuat = 0;

void FCTween::Initialize()
{
	if (bIsInitialized)
	{
		return;
	}
	const UFCTweenConfig* Config = GetDefault<UFCTweenConfig>();
	FloatTweenManager = new FCTweenManager<FCTweenInstanceFloat>(Config->FloatTweenCapacity);
	Vector2TweenManager = new FCTweenManager<FCTweenInstanceVector2D>(Config->Vector2TweenCapacity);
	Vector3TweenManager = new FCTweenManager<FCTweenInstanceVector>(Config->Vector3TweenCapacity);
	QuatTweenManager = new FCTweenManager<FCTweenInstanceQuat>(Config->QuatTweenCapacity);

	NumReservedFloat = Config->FloatTweenCapacity;
	NumReservedVector2 = Config->Vector2TweenCapacity;
	NumReservedVector3 = Config->Vector3TweenCapacity;
	NumReservedQuat = Config->QuatTweenCapacity;

	bIsInitialized = true;
}

void FCTween::Deinitialize()
{
	if (!bIsInitialized)
	{
		return;
	}
	bIsInitialized = false;
	delete FloatTweenManager;
	delete Vector2TweenManager;
	delete Vector3TweenManager;
	delete QuatTweenManager;
}

bool FCTween::IsInitialized()
{
	return bIsInitialized;
}

void FCTween::Update(float UnscaledDeltaSeconds, float DilatedDeltaSeconds, bool bIsGamePaused)
{
	if (!bIsInitialized)
	{
		return;
	}
	FloatTweenManager->Update(UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
	Vector2TweenManager->Update(UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
	Vector3TweenManager->Update(UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
	QuatTweenManager->Update(UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
}

void FCTween::ClearActiveTweens()
{
	if (!bIsInitialized)
	{
		return;
	}
	FloatTweenManager->ClearActiveTweens();
	Vector2TweenManager->ClearActiveTweens();
	Vector3TweenManager->ClearActiveTweens();
	QuatTweenManager->ClearActiveTweens();
}

int FCTween::CheckTweenCapacity()
{
	if (!bIsInitialized)
	{
		return 0;
	}
	if (FloatTweenManager->GetCurrentCapacity() > NumReservedFloat)
	{
		UE_LOG(LogFCTween, Warning,
			TEXT("Consider increasing initial capacity for Float tweens in the Project Settings for FCTween. %d were initially "
				 "reserved, but now there are %d in memory."),
			NumReservedFloat, FloatTweenManager->GetCurrentCapacity());
	}
	if (Vector2TweenManager->GetCurrentCapacity() > NumReservedVector2)
	{
		UE_LOG(LogFCTween, Warning,
			TEXT("Consider increasing initial capacity for Vector2D tweens in the Project Settings for FCTween. %d were initially "
				 "reserved, but now there are %d in memory."),
			NumReservedVector2, Vector2TweenManager->GetCurrentCapacity());
	}
	if (Vector3TweenManager->GetCurrentCapacity() > NumReservedVector3)
	{
		UE_LOG(LogFCTween, Warning,
			TEXT("Consider increasing initial capacity for Vector (3d vector) tweens in the Project Settings for FCTween. %d were "
				 "initially reserved, but now there are %d in memory."),
			NumReservedVector3, Vector3TweenManager->GetCurrentCapacity());
	}
	if (QuatTweenManager->GetCurrentCapacity() > NumReservedQuat)
	{
		UE_LOG(LogFCTween, Warning,
			TEXT("Consider increasing initial capacity for Quaternion tweens in the Project Settings for FCTween. %d were initially "
				 "reserved, but now there are %d in memory."),
			NumReservedQuat, QuatTweenManager->GetCurrentCapacity());
	}

	return FloatTweenManager->GetCurrentCapacity() + Vector2TweenManager->GetCurrentCapacity() + Vector3TweenManager->GetCurrentCapacity() + QuatTweenManager->GetCurrentCapacity();
}

float FCTween::Ease(float t, EFCEase EaseType)
{
	return FCEasing::Ease(t, EaseType);
}

FCTweenInstanceFloat* FCTween::Play(float Start, float End, TFunction<void(float)> OnUpdate, float DurationSecs, EFCEase EaseType)
{
	FCTweenInstanceFloat* NewTween = FloatTweenManager->CreateTween();
	NewTween->Initialize(Start, End, MoveTemp(OnUpdate), DurationSecs, EaseType);
	return NewTween;
}

FCTweenInstanceVector2D* FCTween::Play(FVector2D Start, FVector2D End, TFunction<void(FVector2D)> OnUpdate, float DurationSecs, EFCEase EaseType)
{
	FCTweenInstanceVector2D* NewTween = Vector2TweenManager->CreateTween();
	NewTween->Initialize(Start, End, MoveTemp(OnUpdate), DurationSecs, EaseType);
	return NewTween;
}


FCTweenInstanceVector* FCTween::Play(FVector Start, FVector End, TFunction<void(FVector)> OnUpdate, float DurationSecs, EFCEase EaseType)
{
	FCTweenInstanceVector* NewTween = Vector3TweenManager->CreateTween();
	NewTween->Initialize(Start, End, MoveTemp(OnUpdate), DurationSecs, EaseType);
	return NewTween;
}


FCTweenInstanceQuat* FCTween::Play(FQuat Start, FQuat End, TFunction<void(FQuat)> OnUpdate, float DurationSecs, EFCEase EaseType)
{
	FCTweenInstanceQuat* NewTween = QuatTweenManager->CreateTween();
	NewTween->Initialize(Start, End, MoveTemp(OnUpdate), DurationSecs, EaseType);
	return NewTween;
}
