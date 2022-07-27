#include "FCTweenInstance.h"

#include "FCTweenUObject.h"

FCTweenInstance* FCTweenInstance::SetDelay(float InDelaySecs)
{
	this->DelaySecs = InDelaySecs;
	return this;
}

FCTweenInstance* FCTweenInstance::SetLoops(int InNumLoops)
{
	this->NumLoops = InNumLoops;
	return this;
}

FCTweenInstance* FCTweenInstance::SetLoopDelay(float InLoopDelaySecs)
{
	this->LoopDelaySecs = InLoopDelaySecs;
	return this;
}

FCTweenInstance* FCTweenInstance::SetYoyo(bool bInShouldYoyo)
{
	this->bShouldYoyo = bInShouldYoyo;
	return this;
}

FCTweenInstance* FCTweenInstance::SetYoyoDelay(float InYoyoDelaySecs)
{
	this->YoyoDelaySecs = InYoyoDelaySecs;
	return this;
}

FCTweenInstance* FCTweenInstance::SetTimeMultiplier(float InTimeMultiplier)
{
	this->TimeMultiplier = FMath::Abs(InTimeMultiplier);
	return this;
}

FCTweenInstance* FCTweenInstance::SetEaseParam1(float InEaseParam1)
{
	this->EaseParam1 = InEaseParam1;
	return this;
}

FCTweenInstance* FCTweenInstance::SetEaseParam2(float InEaseParam2)
{
	this->EaseParam2 = InEaseParam2;
	return this;
}

FCTweenInstance* FCTweenInstance::SetCanTickDuringPause(bool bInCanTickDuringPause)
{
	this->bCanTickDuringPause = bInCanTickDuringPause;
	return this;
}

FCTweenInstance* FCTweenInstance::SetUseGlobalTimeDilation(bool bInUseGlobalTimeDilation)
{
	this->bUseGlobalTimeDilation = bInUseGlobalTimeDilation;
	return this;
}

FCTweenInstance* FCTweenInstance::SetAutoDestroy(bool bInShouldAutoDestroy)
{
	this->bShouldAutoDestroy = bInShouldAutoDestroy;
	return this;
}

FCTweenInstance* FCTweenInstance::SetOnYoyo(TFunction<void()> Handler)
{
	this->OnYoyo = MoveTemp(Handler);
	return this;
}

FCTweenInstance* FCTweenInstance::SetOnLoop(TFunction<void()> Handler)
{
	this->OnLoop = MoveTemp(Handler);
	return this;
}

FCTweenInstance* FCTweenInstance::SetOnComplete(TFunction<void()> Handler)
{
	this->OnComplete = MoveTemp(Handler);
	return this;
}

void FCTweenInstance::InitializeSharedMembers(float InDurationSecs, EFCEase InEaseType)
{
	checkf(InDurationSecs > 0, TEXT("Tween received duration <= 0"));
	if (InDurationSecs <= 0)
	{
		this->DurationSecs = .001f;
	}
	else
	{
		this->DurationSecs = InDurationSecs;
	}
	this->EaseType = InEaseType;
	Counter = 0;
	DelayCounter = 0;
	bShouldAutoDestroy = true;
	bIsActive = true;
	bIsPaused = false;
	bShouldYoyo = false;
	bIsPlayingYoyo = false;
	bCanTickDuringPause = false;
	bUseGlobalTimeDilation = true;

	NumLoops = 1;
	NumLoopsCompleted = 0;
	DelaySecs = 0;
	LoopDelaySecs = 0;
	YoyoDelaySecs = 0;
	EaseParam1 = 0;
	EaseParam2 = 0;
	TimeMultiplier = 1.0f;

	DelayState = EDelayState::None;

#if ENGINE_MAJOR_VERSION < 5
	OnYoyo = nullptr;
	OnLoop = nullptr;
	OnComplete = nullptr;
#else
	OnYoyo.Reset();
	OnLoop.Reset();
	OnComplete.Reset();
#endif
}

void FCTweenInstance::Start()
{
	DelayCounter = DelaySecs;
	if (DelayCounter > 0)
	{
		DelayState = EDelayState::Start;
	}
	else
	{
		DelayState = EDelayState::None;
	}
}

void FCTweenInstance::Restart()
{
	if (bIsActive)
	{
		Counter = 0;
		bIsPlayingYoyo = false;
		NumLoopsCompleted = 0;
		Unpause();
		Start();
	}
}

void FCTweenInstance::Destroy()
{
	// mark for recycling
	bIsActive = false;

#if ENGINE_MAJOR_VERSION < 5
	OnLoop  = nullptr;
	OnYoyo  = nullptr;
	OnComplete = nullptr;
#else
	OnLoop.Reset();
	OnYoyo.Reset();
	OnComplete.Reset();
#endif
}

UFCTweenUObject* FCTweenInstance::CreateUObject(UObject* Outer)
{
	UFCTweenUObject* Wrapper = NewObject<UFCTweenUObject>(Outer);
	Wrapper->SetTweenInstance(this);
	return Wrapper;
}

void FCTweenInstance::Pause()
{
	bIsPaused = true;
}

void FCTweenInstance::Unpause()
{
	bIsPaused = false;
}

void FCTweenInstance::Update(float UnscaledDeltaSeconds, float DilatedDeltaSeconds, bool bIsGamePaused)
{
	if (bIsPaused || !bIsActive || bIsGamePaused && !bCanTickDuringPause)
	{
		return;
	}

	float DeltaTime = bUseGlobalTimeDilation ? DilatedDeltaSeconds : UnscaledDeltaSeconds;
	DeltaTime *= TimeMultiplier;

	if (DelayCounter > 0)
	{
		DelayCounter -= DeltaTime;
		if (DelayCounter <= 0)
		{
			switch (DelayState)
			{
				case EDelayState::Loop:
					if (OnLoop)
					{
						OnLoop();
					}
					break;
				case EDelayState::Yoyo:
					if (OnYoyo)
					{
						OnYoyo();
					}
					break;
			}
		}
	}
	else
	{
		if (bIsPlayingYoyo)
		{
			Counter -= DeltaTime;
		}
		else
		{
			Counter += DeltaTime;
		}

		Counter = FMath::Clamp<float>(Counter, 0, DurationSecs);

		ApplyEasing(FCEasing::EaseWithParams(Counter / DurationSecs, EaseType, EaseParam1, EaseParam2));

		if (bIsPlayingYoyo)
		{
			if (Counter <= 0)
			{
				CompleteLoop();
			}
		}
		else
		{
			if (Counter >= DurationSecs)
			{
				if (bShouldYoyo)
				{
					StartYoyo();
				}
				else
				{
					CompleteLoop();
				}
			}
		}
	}
}

void FCTweenInstance::CompleteLoop()
{
	++NumLoopsCompleted;
	if (NumLoops < 0 || NumLoopsCompleted < NumLoops)
	{
		StartNewLoop();
	}
	else
	{
		if (OnComplete)
		{
			OnComplete();
		}
		if (bShouldAutoDestroy)
		{
			Destroy();
		}
		else
		{
			Pause();
		}
	}
}

void FCTweenInstance::StartNewLoop()
{
	DelayCounter = LoopDelaySecs;
	Counter = 0;
	bIsPlayingYoyo = false;
	if (DelayCounter > 0)
	{
		DelayState = EDelayState::Loop;
	}
	else
	{
		if (OnLoop)
		{
			OnLoop();
		}
	}
}

void FCTweenInstance::StartYoyo()
{
	bIsPlayingYoyo = true;
	DelayCounter = YoyoDelaySecs;
	if (DelayCounter > 0)
	{
		DelayState = EDelayState::Yoyo;
	}
	else
	{
		if (OnYoyo)
		{
			OnYoyo();
		}
	}
}