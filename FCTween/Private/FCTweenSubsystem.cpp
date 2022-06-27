#include "FCTweenSubsystem.h"

#include "FCTween.h"
#include "Kismet/GameplayStatics.h"

void UFCTweenSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	LastTickedFrame = GFrameCounter;
#if WITH_EDITOR
	FCTween::ClearActiveTweens();
#endif
}

void UFCTweenSubsystem::Deinitialize()
{
	Super::Deinitialize();
#if WITH_EDITOR
	FCTween::ClearActiveTweens();
#endif
}

void UFCTweenSubsystem::Tick(float DeltaTime)
{
	if (LastTickedFrame < GFrameCounter)
	{
		LastTickedFrame = GFrameCounter;

		if (GetWorld() != nullptr)
		{
			FCTween::Update(DeltaTime, GetWorld()->IsPaused());
		}
	}
}

ETickableTickType UFCTweenSubsystem::GetTickableTickType() const
{
	return ETickableTickType::Always;
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