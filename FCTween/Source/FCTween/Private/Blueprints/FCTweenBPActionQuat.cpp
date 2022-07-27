#include "Blueprints/FCTweenBPActionQuat.h"

#include "FCTween.h"

UFCTweenBPActionQuat* UFCTweenBPActionQuat::TweenQuat(FQuat Start, FQuat End, float DurationSecs, EFCEase EaseType,
	float EaseParam1, float EaseParam2, float Delay, int Loops, float LoopDelay, bool bYoyo, float YoyoDelay,
	bool bCanTickDuringPause, bool bUseGlobalTimeDilation)
{
	UFCTweenBPActionQuat* BlueprintNode = NewObject<UFCTweenBPActionQuat>();
	BlueprintNode->SetSharedTweenProperties(
		DurationSecs, Delay, Loops, LoopDelay, bYoyo, YoyoDelay, bCanTickDuringPause, bUseGlobalTimeDilation);
	BlueprintNode->EaseType = EaseType;
	BlueprintNode->Start = Start;
	BlueprintNode->End = End;
	BlueprintNode->EaseParam1 = EaseParam1;
	BlueprintNode->EaseParam2 = EaseParam2;
	return BlueprintNode;
}
UFCTweenBPActionQuat* UFCTweenBPActionQuat::TweenQuatFromRotator(FRotator Start, FRotator End, float DurationSecs, EFCEase EaseType,
	float EaseParam1, float EaseParam2, float Delay, int Loops, float LoopDelay, bool bYoyo, float YoyoDelay,
	bool bCanTickDuringPause, bool bUseGlobalTimeDilation)
{
	UFCTweenBPActionQuat* BlueprintNode = NewObject<UFCTweenBPActionQuat>();
	BlueprintNode->SetSharedTweenProperties(
		DurationSecs, Delay, Loops, LoopDelay, bYoyo, YoyoDelay, bCanTickDuringPause, bUseGlobalTimeDilation);
	BlueprintNode->EaseType = EaseType;
	BlueprintNode->Start = Start.Quaternion();
	BlueprintNode->End = End.Quaternion();
	BlueprintNode->EaseParam1 = EaseParam1;
	BlueprintNode->EaseParam2 = EaseParam2;
	return BlueprintNode;
}

UFCTweenBPActionQuat* UFCTweenBPActionQuat::TweenQuatCustomCurve(FQuat Start, FQuat End, float DurationSecs, UCurveFloat* Curve,
	float Delay, int Loops, float LoopDelay, bool bYoyo, float YoyoDelay, bool bCanTickDuringPause, bool bUseGlobalTimeDilation)
{
	UFCTweenBPActionQuat* BlueprintNode = NewObject<UFCTweenBPActionQuat>();
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

UFCTweenBPActionQuat* UFCTweenBPActionQuat::TweenQuatFromRotatorCustomCurve(FRotator Start, FRotator End, float DurationSecs,
	UCurveFloat* Curve, float Delay, int Loops, float LoopDelay, bool bYoyo, float YoyoDelay, bool bCanTickDuringPause,
	bool bUseGlobalTimeDilation)
{
	UFCTweenBPActionQuat* BlueprintNode = NewObject<UFCTweenBPActionQuat>();
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

FCTweenInstance* UFCTweenBPActionQuat::CreateTween()
{
	return FCTween::Play(
		Start, End, [&](FQuat t) { ApplyEasing.Broadcast(t); }, DurationSecs, EaseType);
}

FCTweenInstance* UFCTweenBPActionQuat::CreateTweenCustomCurve()
{
	return FCTween::Play(
		0, 1,
		[&](float t)
		{
			float EasedTime = CustomCurve->GetFloatValue(t);
			FQuat EasedValue = FMath::Lerp(Start, End, EasedTime);
			ApplyEasing.Broadcast(EasedValue);
		},
		DurationSecs, EaseType);
}