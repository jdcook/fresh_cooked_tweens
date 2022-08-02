#include "FCTween.h"

#include "FCTweenManager.h"

DEFINE_LOG_CATEGORY(LogFCTween)

const int DEFAULT_FLOAT_TWEEN_CAPACITY = 50;
const int DEFAULT_VECTOR_TWEEN_CAPACITY = 50;
const int DEFAULT_VECTOR2D_TWEEN_CAPACITY = 50;
const int DEFAULT_QUAT_TWEEN_CAPACITY = 10;

FCTweenManager<FCTweenInstanceFloat>* FCTween::FloatTweenManager = nullptr;
FCTweenManager<FCTweenInstanceVector>* FCTween::VectorTweenManager = nullptr;
FCTweenManager<FCTweenInstanceVector2D>* FCTween::Vector2DTweenManager = nullptr;
FCTweenManager<FCTweenInstanceQuat>* FCTween::QuatTweenManager = nullptr;

int FCTween::NumReservedFloat = DEFAULT_FLOAT_TWEEN_CAPACITY;
int FCTween::NumReservedVector = DEFAULT_VECTOR_TWEEN_CAPACITY;
int FCTween::NumReservedVector2D = DEFAULT_VECTOR2D_TWEEN_CAPACITY;
int FCTween::NumReservedQuat = DEFAULT_QUAT_TWEEN_CAPACITY;

void FCTween::Initialize()
{
	FloatTweenManager = new FCTweenManager<FCTweenInstanceFloat>(DEFAULT_FLOAT_TWEEN_CAPACITY);
	VectorTweenManager = new FCTweenManager<FCTweenInstanceVector>(DEFAULT_VECTOR_TWEEN_CAPACITY);
	Vector2DTweenManager = new FCTweenManager<FCTweenInstanceVector2D>(DEFAULT_VECTOR2D_TWEEN_CAPACITY);
	QuatTweenManager = new FCTweenManager<FCTweenInstanceQuat>(DEFAULT_QUAT_TWEEN_CAPACITY);
	
	NumReservedFloat = DEFAULT_FLOAT_TWEEN_CAPACITY;
	NumReservedVector = DEFAULT_VECTOR_TWEEN_CAPACITY;
	NumReservedVector2D = DEFAULT_VECTOR2D_TWEEN_CAPACITY;
	NumReservedQuat = DEFAULT_QUAT_TWEEN_CAPACITY;
}

void FCTween::Deinitialize()
{
	delete FloatTweenManager;
	delete VectorTweenManager;
	delete Vector2DTweenManager;
	delete QuatTweenManager;
}

void FCTween::EnsureCapacity(int NumFloatTweens, int NumVectorTweens, int NumVector2DTweens, int NumQuatTweens)
{
	FloatTweenManager->EnsureCapacity(NumFloatTweens);
	VectorTweenManager->EnsureCapacity(NumVectorTweens);
	Vector2DTweenManager->EnsureCapacity(NumVector2DTweens);
	QuatTweenManager->EnsureCapacity(NumQuatTweens);
	
	NumReservedFloat = FloatTweenManager->GetCurrentCapacity();
	NumReservedVector = VectorTweenManager->GetCurrentCapacity();
	NumReservedVector2D = Vector2DTweenManager->GetCurrentCapacity();
	NumReservedQuat = QuatTweenManager->GetCurrentCapacity();
}

void FCTween::EnsureCapacity(int NumTweens)
{
	EnsureCapacity(NumTweens, NumTweens, NumTweens, NumTweens);
}

void FCTween::Update(float UnscaledDeltaSeconds, float DilatedDeltaSeconds, bool bIsGamePaused)
{
	FloatTweenManager->Update(UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
	VectorTweenManager->Update(UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
	Vector2DTweenManager->Update(UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
	QuatTweenManager->Update(UnscaledDeltaSeconds, DilatedDeltaSeconds, bIsGamePaused);
}

void FCTween::ClearActiveTweens()
{
	FloatTweenManager->ClearActiveTweens();
	VectorTweenManager->ClearActiveTweens();
	Vector2DTweenManager->ClearActiveTweens();
	QuatTweenManager->ClearActiveTweens();
}

int FCTween::CheckTweenCapacity()
{
	if(FloatTweenManager->GetCurrentCapacity() > NumReservedFloat)
	{
		UE_LOG(LogFCTween, Warning, TEXT("Consider increasing initial capacity for Float tweens with FCTween::EnsureCapacity(). %d were initially reserved, but now there are %d in memory."),
			NumReservedFloat, FloatTweenManager->GetCurrentCapacity());
	}
	if(VectorTweenManager->GetCurrentCapacity() > NumReservedVector)
	{
		UE_LOG(LogFCTween, Warning, TEXT("Consider increasing initial capacity for Vector (3d vector) tweens with FCTween::EnsureCapacity(). %d were initially reserved, but now there are %d in memory."),
			NumReservedVector, VectorTweenManager->GetCurrentCapacity());
	}
	if(Vector2DTweenManager->GetCurrentCapacity() > NumReservedVector2D)
	{
		UE_LOG(LogFCTween, Warning, TEXT("Consider increasing initial capacity for Vector2D tweens with FCTween::EnsureCapacity(). %d were initially reserved, but now there are %d in memory."),
			NumReservedVector2D, Vector2DTweenManager->GetCurrentCapacity());
	}
	if(QuatTweenManager->GetCurrentCapacity() > NumReservedQuat)
	{
		UE_LOG(LogFCTween, Warning, TEXT("Consider increasing initial capacity for Quaternion tweens with FCTween::EnsureCapacity(). %d were initially reserved, but now there are %d in memory."),
			NumReservedQuat, QuatTweenManager->GetCurrentCapacity());
	}

	return FloatTweenManager->GetCurrentCapacity() + VectorTweenManager->GetCurrentCapacity() +  Vector2DTweenManager->GetCurrentCapacity() + QuatTweenManager->GetCurrentCapacity();
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

FCTweenInstanceVector* FCTween::Play(
	FVector Start, FVector End, TFunction<void(FVector)> OnUpdate, float DurationSecs, EFCEase EaseType)
{
	FCTweenInstanceVector* NewTween = VectorTweenManager->CreateTween();
	NewTween->Initialize(Start, End, MoveTemp(OnUpdate), DurationSecs, EaseType);
	return NewTween;
}

FCTweenInstanceVector2D* FCTween::Play(
	FVector2D Start, FVector2D End, TFunction<void(FVector2D)> OnUpdate, float DurationSecs, EFCEase EaseType)
{
	FCTweenInstanceVector2D* NewTween = Vector2DTweenManager->CreateTween();
	NewTween->Initialize(Start, End, MoveTemp(OnUpdate), DurationSecs, EaseType);
	return NewTween;
}

FCTweenInstanceQuat* FCTween::Play(FQuat Start, FQuat End, TFunction<void(FQuat)> OnUpdate, float DurationSecs, EFCEase EaseType)
{
	FCTweenInstanceQuat* NewTween = QuatTweenManager->CreateTween();
	NewTween->Initialize(Start, End, MoveTemp(OnUpdate), DurationSecs, EaseType);
	return NewTween;
}
