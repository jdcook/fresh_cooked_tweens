// MIT License - Copyright 2026 Jared Cook
#include "FCEasing.h"

#include "PhaserEasing.h"
#include "RobertPennerEasing.h"

const float BACK_INOUT_OVERSHOOT_MODIFIER = 1.525f;
const float BOUNCE_R = 1.0f / 2.75f;		  // reciprocal
const float BOUNCE_K1 = BOUNCE_R;			  // 36.36%
const float BOUNCE_K2 = 2 * BOUNCE_R;		  // 72.72%
const float BOUNCE_K3 = 1.5f * BOUNCE_R;	  // 54.54%
const float BOUNCE_K4 = 2.5f * BOUNCE_R;	  // 90.90%
const float BOUNCE_K5 = 2.25f * BOUNCE_R;	  // 81.81%
const float BOUNCE_K6 = 2.625f * BOUNCE_R;	  // 95.45%
const float BOUNCE_K0 = 7.5625f;

float FCEasing::Ease(float t, EFCEase EaseType)
{
	switch (EaseType)
	{
		default:
		case EFCEase::Linear:
			return EaseLinear(t);
		case EFCEase::Smoothstep:
			return EaseSmoothstep(t);
		case EFCEase::Stepped:
			return EaseStepped(t);
		case EFCEase::InSine:
			return EaseInSine(t);
		case EFCEase::OutSine:
			return EaseOutSine(t);
		case EFCEase::InOutSine:
			return EaseInOutSine(t);
		case EFCEase::InQuad:
			return EaseInQuad(t);
		case EFCEase::OutQuad:
			return EaseOutQuad(t);
		case EFCEase::InOutQuad:
			return EaseInOutQuad(t);
		case EFCEase::InCubic:
			return EaseInCubic(t);
		case EFCEase::OutCubic:
			return EaseOutCubic(t);
		case EFCEase::InOutCubic:
			return EaseInOutCubic(t);
		case EFCEase::InQuart:
			return EaseInQuart(t);
		case EFCEase::OutQuart:
			return EaseOutQuart(t);
		case EFCEase::InOutQuart:
			return EaseInOutQuart(t);
		case EFCEase::InQuint:
			return EaseInQuint(t);
		case EFCEase::OutQuint:
			return EaseOutQuint(t);
		case EFCEase::InOutQuint:
			return EaseInOutQuint(t);
		case EFCEase::InExpo:
			return EaseInExpo(t);
		case EFCEase::OutExpo:
			return EaseOutExpo(t);
		case EFCEase::InOutExpo:
			return EaseInOutExpo(t);
		case EFCEase::InCirc:
			return EaseInCirc(t);
		case EFCEase::OutCirc:
			return EaseOutCirc(t);
		case EFCEase::InOutCirc:
			return EaseInOutCirc(t);
		case EFCEase::InElastic:
			return EaseInElastic(t);
		case EFCEase::OutElastic:
			return EaseOutElastic(t);
		case EFCEase::InOutElastic:
			return EaseInOutElastic(t);
		case EFCEase::InBounce:
			return EaseInBounce(t);
		case EFCEase::OutBounce:
			return EaseOutBounce(t);
		case EFCEase::InOutBounce:
			return EaseInOutBounce(t);
		case EFCEase::InBack:
			return EaseInBack(t);
		case EFCEase::OutBack:
			return EaseOutBack(t);
		case EFCEase::InOutBack:
			return EaseInOutBack(t);
	}
}

float FCEasing::EaseWithParams(float t, EFCEase EaseType, float Param1, float Param2)
{
	if (Param1 == 0 && Param2 == 0)
	{
		return Ease(t, EaseType);
	}

	switch (EaseType)
	{
		default:
		case EFCEase::Linear:
			return EaseLinear(t);
		case EFCEase::Smoothstep:
			return EaseSmoothstep(t, Param1, Param2);
		case EFCEase::Stepped:
			return EaseStepped(t, Param1);
		case EFCEase::InSine:
			return EaseInSine(t);
		case EFCEase::OutSine:
			return EaseOutSine(t);
		case EFCEase::InOutSine:
			return EaseInOutSine(t);
		case EFCEase::InQuad:
			return EaseInQuad(t);
		case EFCEase::OutQuad:
			return EaseOutQuad(t);
		case EFCEase::InOutQuad:
			return EaseInOutQuad(t);
		case EFCEase::InCubic:
			return EaseInCubic(t);
		case EFCEase::OutCubic:
			return EaseOutCubic(t);
		case EFCEase::InOutCubic:
			return EaseInOutCubic(t);
		case EFCEase::InQuart:
			return EaseInQuart(t);
		case EFCEase::OutQuart:
			return EaseOutQuart(t);
		case EFCEase::InOutQuart:
			return EaseInOutQuart(t);
		case EFCEase::InQuint:
			return EaseInQuint(t);
		case EFCEase::OutQuint:
			return EaseOutQuint(t);
		case EFCEase::InOutQuint:
			return EaseInOutQuint(t);
		case EFCEase::InExpo:
			return EaseInExpo(t);
		case EFCEase::OutExpo:
			return EaseOutExpo(t);
		case EFCEase::InOutExpo:
			return EaseInOutExpo(t);
		case EFCEase::InCirc:
			return EaseInCirc(t);
		case EFCEase::OutCirc:
			return EaseOutCirc(t);
		case EFCEase::InOutCirc:
			return EaseInOutCirc(t);
		case EFCEase::InElastic:
			return EaseInElastic(t, Param1, Param2);
		case EFCEase::OutElastic:
			return EaseOutElastic(t, Param1, Param2);
		case EFCEase::InOutElastic:
			return EaseInOutElastic(t, Param1, Param2);
		case EFCEase::InBounce:
			return EaseInBounce(t);
		case EFCEase::OutBounce:
			return EaseOutBounce(t);
		case EFCEase::InOutBounce:
			return EaseInOutBounce(t);
		case EFCEase::InBack:
			return EaseInBack(t, Param1);
		case EFCEase::OutBack:
			return EaseOutBack(t, Param1);
		case EFCEase::InOutBack:
			return EaseInOutBack(t, Param1);
	}
}

float FCEasing::EaseLinear(float t)
{
	return t;
}

float FCEasing::EaseSmoothstep(float t, float x0, float x1)
{
	return RobertPennerEasing::EaseSmoothstep(t, x0, x1);
}

float FCEasing::EaseStepped(float t, int Steps)
{
	return PhaserEasing::EaseStepped(t, Steps);
}

float FCEasing::EaseInSine(float t)
{
	return RobertPennerEasing::EaseInSine(t);
}

float FCEasing::EaseOutSine(float t)
{
	return RobertPennerEasing::EaseOutSine(t);
}

float FCEasing::EaseInOutSine(float t)
{
	return RobertPennerEasing::EaseInOutSine(t);
}

float FCEasing::EaseInQuad(float t)
{
	return RobertPennerEasing::EaseInQuad(t);
}

float FCEasing::EaseOutQuad(float t)
{
	return RobertPennerEasing::EaseOutQuad(t);
}

float FCEasing::EaseInOutQuad(float t)
{
	return RobertPennerEasing::EaseInOutQuad(t);
}

float FCEasing::EaseInCubic(float t)
{
	return RobertPennerEasing::EaseInCubic(t);
}

float FCEasing::EaseOutCubic(float t)
{
	return RobertPennerEasing::EaseOutCubic(t);
}

float FCEasing::EaseInOutCubic(float t)
{
	return RobertPennerEasing::EaseInOutCubic(t);
}

float FCEasing::EaseInQuart(float t)
{
	return RobertPennerEasing::EaseInQuart(t);
}

float FCEasing::EaseOutQuart(float t)
{
	return RobertPennerEasing::EaseOutQuart(t);
}

float FCEasing::EaseInOutQuart(float t)
{
	return RobertPennerEasing::EaseInOutQuart(t);
}

float FCEasing::EaseInQuint(float t)
{
	return RobertPennerEasing::EaseInQuint(t);
}

float FCEasing::EaseOutQuint(float t)
{
	return RobertPennerEasing::EaseOutQuint(t);
}

float FCEasing::EaseInOutQuint(float t)
{
	return RobertPennerEasing::EaseInOutQuint(t);
}

float FCEasing::EaseInExpo(float t)
{
	return RobertPennerEasing::EaseInExpo(t);
}

float FCEasing::EaseOutExpo(float t)
{
	return RobertPennerEasing::EaseOutExpo(t);
}

float FCEasing::EaseInOutExpo(float t)
{
	return RobertPennerEasing::EaseInOutExpo(t);
}

float FCEasing::EaseInCirc(float t)
{
	return RobertPennerEasing::EaseInCirc(t);
}

float FCEasing::EaseOutCirc(float t)
{
	return RobertPennerEasing::EaseOutCirc(t);
}

float FCEasing::EaseInOutCirc(float t)
{
	return RobertPennerEasing::EaseInOutCirc(t);
}

float FCEasing::EaseInElastic(float t, float Amplitude, float Period)
{
	return PhaserEasing::EaseInElastic(t, Amplitude, Period);
}

float FCEasing::EaseOutElastic(float t, float Amplitude, float Period)
{
	return PhaserEasing::EaseOutElastic(t, Amplitude, Period);
}

float FCEasing::EaseInOutElastic(float t, float Amplitude, float Period)
{
	return PhaserEasing::EaseInOutElastic(t, Amplitude, Period);
}

float FCEasing::EaseInBounce(float t)
{
	return RobertPennerEasing::EaseInBounce(t);
}

float FCEasing::EaseOutBounce(float t)
{
	return RobertPennerEasing::EaseOutBounce(t);
}

float FCEasing::EaseInOutBounce(float t)
{
	return RobertPennerEasing::EaseInOutBounce(t);
}

float FCEasing::EaseInBack(float t, float Overshoot)
{
	return RobertPennerEasing::EaseInBack(t, Overshoot);
}

float FCEasing::EaseOutBack(float t, float Overshoot)
{
	return RobertPennerEasing::EaseOutBack(t, Overshoot);
}

float FCEasing::EaseInOutBack(float t, float Overshoot)
{
	return RobertPennerEasing::EaseInOutBack(t, Overshoot);
}