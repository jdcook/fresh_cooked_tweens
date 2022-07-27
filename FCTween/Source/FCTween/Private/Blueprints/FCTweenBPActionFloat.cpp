#include "Blueprints/FCTweenBPActionFloat.h"

#include "FCTween.h"

UFCTweenBPActionFloat* UFCTweenBPActionFloat::TweenFloat(float Start, float End, float DurationSecs, EFCEase EaseType,
	float EaseParam1, float EaseParam2, float Delay, int Loops, float LoopDelay, bool bYoyo, float YoyoDelay,
	bool bCanTickDuringPause, bool bUseGlobalTimeDilation)
{
	UFCTweenBPActionFloat* BlueprintNode = NewObject<UFCTweenBPActionFloat>();
	BlueprintNode->SetSharedTweenProperties(
		DurationSecs, Delay, Loops, LoopDelay, bYoyo, YoyoDelay, bCanTickDuringPause, bUseGlobalTimeDilation);
	BlueprintNode->EaseType = EaseType;
	BlueprintNode->Start = Start;
	BlueprintNode->End = End;
	BlueprintNode->EaseParam1 = EaseParam1;
	BlueprintNode->EaseParam2 = EaseParam2;
	return BlueprintNode;
}

UFCTweenBPActionFloat* UFCTweenBPActionFloat::TweenFloatCustomCurve(float Start, float End, float DurationSecs, UCurveFloat* Curve,
	float Delay, int Loops, float LoopDelay, bool bYoyo, float YoyoDelay, bool bCanTickDuringPause, bool bUseGlobalTimeDilation)
{
	UFCTweenBPActionFloat* BlueprintNode = NewObject<UFCTweenBPActionFloat>();
	BlueprintNode->SetSharedTweenProperties(
		DurationSecs, Delay, Loops, LoopDelay, bYoyo, YoyoDelay, bCanTickDuringPause, bUseGlobalTimeDilation);
	BlueprintNode->CustomCurve = Curve;
	BlueprintNode->bUseCustomCurve = true;
	BlueprintNode->Start = Start;
	BlueprintNode->End = End;
	BlueprintNode->EaseParam1 = 0;
	BlueprintNode->EaseParam2 = 0;
	return BlueprintNode;
}

FCTweenInstance* UFCTweenBPActionFloat::CreateTween()
{
	return FCTween::Play(
		Start, End, [&](float t) { ApplyEasing.Broadcast(t); }, DurationSecs, EaseType);
}

FCTweenInstance* UFCTweenBPActionFloat::CreateTweenCustomCurve()
{
	return FCTween::Play(
		0, 1,
		[&](float t)
		{
			float EasedTime = CustomCurve->GetFloatValue(t);
			float EasedValue = FMath::Lerp(Start, End, EasedTime);
			ApplyEasing.Broadcast(EasedValue);
		},
		DurationSecs, EaseType);
}
