#include "Blueprints/FCTweenBPAction.h"

#include "FCTween.h"

void UFCTweenBPAction::Activate()
{
	if (TweenInstance != nullptr)
	{
		// restart the tween
		TweenInstance->Destroy();
		TweenInstance = nullptr;
	}
	if (DurationSecs <= 0)
	{
		FFrame::KismetExecutionMessage(TEXT("Duration must be more than 0"), ELogVerbosity::Error);
		return;
	}
	if (bUseCustomCurve)
	{
		if (CustomCurve != nullptr)
		{
			EaseType = EFCEase::Linear;
			TweenInstance = CreateTweenCustomCurve();
		}
		else
		{
			FFrame::KismetExecutionMessage(TEXT("No Custom Curve defined for custom curve task"), ELogVerbosity::Error);
			return;
		}
	}
	else
	{
		TweenInstance = CreateTween();
	}
	if (TweenInstance == nullptr)
	{
		FFrame::KismetExecutionMessage(TEXT("Tween Instance was not created in child class"), ELogVerbosity::Error);
		return;
	}
	TweenInstance->SetDelay(Delay)
		->SetLoops(Loops)
		->SetLoopDelay(LoopDelay)
		->SetYoyo(bYoyo)
		->SetYoyoDelay(YoyoDelay)
		->SetCanTickDuringPause(bCanTickDuringPause)
		->SetUseGlobalTimeDilation(bUseGlobalTimeDilation)
		// we will tell it when to be destroyed on complete, so that we control when
		// the tween goes invalid and it can't get recycled by doing something unexpected in BPs
		->SetAutoDestroy(false)
		->SetEaseParam1(EaseParam1)
		->SetEaseParam2(EaseParam2);

	if (OnLoop.IsBound())
	{
		TweenInstance->SetOnLoop([&]() { OnLoop.Broadcast(); });
	}
	if (OnYoyo.IsBound())
	{
		TweenInstance->SetOnYoyo([&]() { OnYoyo.Broadcast(); });
	}
	if (OnComplete.IsBound())
	{
		TweenInstance->SetOnComplete(
			[&]()
			{
				OnComplete.Broadcast();
				Stop();
			});
	}
}

FCTweenInstance* UFCTweenBPAction::CreateTween()
{
	// override in specific data type tasks
	return nullptr;
}

FCTweenInstance* UFCTweenBPAction::CreateTweenCustomCurve()
{
	return nullptr;
}

void UFCTweenBPAction::SetSharedTweenProperties(float InDurationSecs, float InDelay, int InLoops, float InLoopDelay, bool InbYoyo,
	float InYoyoDelay, bool bInCanTickDuringPause, bool bInUseGlobalTimeDilation)
{
	TweenInstance = nullptr;
	bUseCustomCurve = false;
	CustomCurve = nullptr;
	DurationSecs = InDurationSecs;
	Delay = InDelay;
	Loops = InLoops;
	LoopDelay = InLoopDelay;
	bYoyo = InbYoyo;
	YoyoDelay = InYoyoDelay;
	bCanTickDuringPause = bInCanTickDuringPause;
	bUseGlobalTimeDilation = bInUseGlobalTimeDilation;
}

void UFCTweenBPAction::BeginDestroy()
{
	Super::BeginDestroy();
	if (TweenInstance != nullptr)
	{
		TweenInstance->Destroy();
		TweenInstance = nullptr;
	}
}

void UFCTweenBPAction::Pause()
{
	if (TweenInstance)
	{
		TweenInstance->Pause();
	}
}

void UFCTweenBPAction::Unpause()
{
	if (TweenInstance)
	{
		TweenInstance->Unpause();
	}
}

void UFCTweenBPAction::Restart()
{
	if (TweenInstance)
	{
		TweenInstance->Restart();
	}
}

void UFCTweenBPAction::Stop()
{
	if (TweenInstance)
	{
		TweenInstance->Destroy();
		TweenInstance = nullptr;
		SetReadyToDestroy();
#if ENGINE_MAJOR_VERSION < 5
		MarkPendingKill();
#else
		MarkAsGarbage();
#endif
	}
}

void UFCTweenBPAction::SetTimeMultiplier(float Multiplier)
{
	if (TweenInstance)
	{
		TweenInstance->SetTimeMultiplier(Multiplier);
	}
}
