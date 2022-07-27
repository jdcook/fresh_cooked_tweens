#include "Blueprints/FCTweenBPActionRotator.h"

#include "FCTween.h"

UFCTweenBPActionRotator* UFCTweenBPActionRotator::TweenRotator(FRotator Start, FRotator End, float DurationSecs, EFCEase EaseType,
	float EaseParam1, float EaseParam2, float Delay, int Loops, float LoopDelay, bool bYoyo, float YoyoDelay,
	bool bCanTickDuringPause, bool bUseGlobalTimeDilation)
{
	UFCTweenBPActionRotator* BlueprintNode = NewObject<UFCTweenBPActionRotator>();
	BlueprintNode->SetSharedTweenProperties(
		DurationSecs, Delay, Loops, LoopDelay, bYoyo, YoyoDelay, bCanTickDuringPause, bUseGlobalTimeDilation);
	BlueprintNode->EaseType = EaseType;
	BlueprintNode->Start = Start.Quaternion();
	BlueprintNode->End = End.Quaternion();
	BlueprintNode->EaseParam1 = EaseParam1;
	BlueprintNode->EaseParam2 = EaseParam2;
	return BlueprintNode;
}

UFCTweenBPActionRotator* UFCTweenBPActionRotator::TweenRotatorCustomCurve(FRotator Start, FRotator End, float DurationSecs,
	UCurveFloat* Curve, float Delay, int Loops, float LoopDelay, bool bYoyo, float YoyoDelay, bool bCanTickDuringPause,
	bool bUseGlobalTimeDilation)
{
	UFCTweenBPActionRotator* BlueprintNode = NewObject<UFCTweenBPActionRotator>();
	BlueprintNode->SetSharedTweenProperties(
		DurationSecs, Delay, Loops, LoopDelay, bYoyo, YoyoDelay, bCanTickDuringPause, bUseGlobalTimeDilation);
	BlueprintNode->CustomCurve = Curve;
	BlueprintNode->bUseCustomCurve = true;
	BlueprintNode->Start = Start.Quaternion();
	BlueprintNode->End = End.Quaternion();
	BlueprintNode->EaseParam1 = 0;
	BlueprintNode->EaseParam2 = 0;
	return BlueprintNode;
}

FCTweenInstance* UFCTweenBPActionRotator::CreateTween()
{
	return FCTween::Play(
		Start, End, [&](FQuat t) { ApplyEasing.Broadcast(t.Rotator()); }, DurationSecs, EaseType);
}

FCTweenInstance* UFCTweenBPActionRotator::CreateTweenCustomCurve()
{
	return FCTween::Play(
		0, 1,
		[&](float t)
		{
			float EasedTime = CustomCurve->GetFloatValue(t);
			FQuat EasedValue = FMath::Lerp(Start, End, EasedTime);
			ApplyEasing.Broadcast(EasedValue.Rotator());
		},
		DurationSecs, EaseType);
}