#include "Blueprints/FCTweenBPActionVector2D.h"

#include "FCTween.h"

UFCTweenBPActionVector2D* UFCTweenBPActionVector2D::TweenVector2D(FVector2D Start, FVector2D End, float DurationSecs,
	EFCEase EaseType, float EaseParam1, float EaseParam2, float Delay, int Loops, float LoopDelay, bool bYoyo, float YoyoDelay,
	bool bCanTickDuringPause, bool bUseGlobalTimeDilation)
{
	UFCTweenBPActionVector2D* BlueprintNode = NewObject<UFCTweenBPActionVector2D>();
	BlueprintNode->SetSharedTweenProperties(
		DurationSecs, Delay, Loops, LoopDelay, bYoyo, YoyoDelay, bCanTickDuringPause, bUseGlobalTimeDilation);
	BlueprintNode->EaseType = EaseType;
	BlueprintNode->Start = Start;
	BlueprintNode->End = End;
	BlueprintNode->EaseParam1 = EaseParam1;
	BlueprintNode->EaseParam2 = EaseParam2;
	return BlueprintNode;
}

UFCTweenBPActionVector2D* UFCTweenBPActionVector2D::TweenVector2DCustomCurve(FVector2D Start, FVector2D End, float DurationSecs,
	UCurveFloat* Curve, float Delay, int Loops, float LoopDelay, bool bYoyo, float YoyoDelay, bool bCanTickDuringPause,
	bool bUseGlobalTimeDilation)
{
	UFCTweenBPActionVector2D* BlueprintNode = NewObject<UFCTweenBPActionVector2D>();
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

FCTweenInstance* UFCTweenBPActionVector2D::CreateTween()
{
	return FCTween::Play(
		Start, End, [&](FVector2D t) { ApplyEasing.Broadcast(t); }, DurationSecs, EaseType);
}

FCTweenInstance* UFCTweenBPActionVector2D::CreateTweenCustomCurve()
{
	return FCTween::Play(
		0, 1,
		[&](float t)
		{
			float EasedTime = CustomCurve->GetFloatValue(t);
			FVector2D EasedValue = FMath::Lerp(Start, End, EasedTime);
			ApplyEasing.Broadcast(EasedValue);
		},
		DurationSecs, EaseType);
}