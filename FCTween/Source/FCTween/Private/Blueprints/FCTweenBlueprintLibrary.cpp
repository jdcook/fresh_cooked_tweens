// MIT License - Copyright 2026 Jared Cook
#include "Blueprints/FCTweenBlueprintLibrary.h"

#include "FCTween.h"

float UFCTweenBlueprintLibrary::Ease(float t, EFCEase EaseType)

{
	return FCEasing::Ease(t, EaseType);
}

float UFCTweenBlueprintLibrary::EaseWithParams(float t, EFCEase EaseType, float Param1, float Param2)
{
	return FCEasing::EaseWithParams(t, EaseType, Param1, Param2);
}
