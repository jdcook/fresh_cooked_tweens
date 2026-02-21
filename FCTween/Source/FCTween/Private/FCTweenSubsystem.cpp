// MIT License - Copyright 2026 Jared Cook
#include "FCTweenSubsystem.h"

#include "FCTween.h"
#include "Kismet/GameplayStatics.h"
#include "Runtime/Launch/Resources/Version.h"

bool UFCTweenSubsystem::ShouldCreateSubsystem(UObject* Outer) const
{
	return !FCTween::IsInitialized();
}

void UFCTweenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	bInitialized = true;
	
	LastTickedFrame = GFrameCounter;

#if ENGINE_MAJOR_VERSION < 5
	if (GetWorld() != nullptr)
	{
		LastRealTimeSeconds = GetWorld()->RealTimeSeconds;
	}
#endif

	FCTween::Initialize();
}

void UFCTweenSubsystem::Deinitialize()
{
#if WITH_EDITOR
	FCTween::CheckTweenCapacity();
	FCTween::ClearActiveTweens();
#endif

	bInitialized = false;
	
	Super::Deinitialize();
}

void UFCTweenSubsystem::FinishDestroy()
{
	if (!IsTemplate())
	{
		FCTween::Deinitialize();
	}
	Super::FinishDestroy();
}

void UFCTweenSubsystem::Tick(float DeltaTime)
{
	if (LastTickedFrame < GFrameCounter)
	{
		LastTickedFrame = GFrameCounter;

		if (GetWorld() != nullptr)
		{
#if ENGINE_MAJOR_VERSION < 5
			float DeltaRealTimeSeconds = GetWorld()->RealTimeSeconds - LastRealTimeSeconds;
			FCTween::Update(DeltaRealTimeSeconds, GetWorld()->DeltaTimeSeconds, GetWorld()->IsPaused());
			LastRealTimeSeconds = GetWorld()->RealTimeSeconds;
#else
			FCTween::Update(GetWorld()->DeltaRealTimeSeconds, GetWorld()->DeltaTimeSeconds, GetWorld()->IsPaused());
#endif
		}
	}
}

ETickableTickType UFCTweenSubsystem::GetTickableTickType() const
{
	if (IsTemplate())
	{
		return ETickableTickType::Never;
	}

	return ETickableTickType::Conditional;
}

bool UFCTweenSubsystem::IsAllowedToTick() const
{
	return bInitialized;
}

TStatId UFCTweenSubsystem::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FCTween, STATGROUP_Tickables);
}

bool UFCTweenSubsystem::IsTickableWhenPaused() const
{
	return true;
}

bool UFCTweenSubsystem::IsTickableInEditor() const
{
	return false;
}