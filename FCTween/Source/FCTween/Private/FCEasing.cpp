#include "FCEasing.h"

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
	float x = FMath::Clamp<float>((t - x0) / (x1 - x0), 0.0f, 1.0f);
	return x * x * (3.0f - 2.0f * x);
}

float FCEasing::EaseStepped(float t, int Steps)
{
	if (t <= 0)
	{
		return 0;
	}
	else if (t >= 1)
	{
		return 1;
	}
	else
	{
		return FMath::FloorToFloat(Steps * t) / Steps;
	}
}

float FCEasing::EaseInSine(float t)
{
	return 1 - FMath::Cos(t * PI * .5f);
}

float FCEasing::EaseOutSine(float t)
{
	return FMath::Sin(t * PI * .5f);
}

float FCEasing::EaseInOutSine(float t)
{
	return 0.5f * (1 - FMath::Cos(t * PI));
}

float FCEasing::EaseInQuad(float t)
{
	return t * t;
}

float FCEasing::EaseOutQuad(float t)
{
	return t * (2 - t);
}

float FCEasing::EaseInOutQuad(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return t * t2;
	}
	else
	{
		float m = t - 1;
		return 1 - m * m * 2;
	}
}

float FCEasing::EaseInCubic(float t)
{
	return t * t * t;
}

float FCEasing::EaseOutCubic(float t)
{
	float m = t - 1;
	return 1 + m * m * m;
}

float FCEasing::EaseInOutCubic(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return t * t2 * t2;
	}
	else
	{
		float m = t - 1;
		return 1 + m * m * m * 4;
	}
}

float FCEasing::EaseInQuart(float t)
{
	return t * t * t * t;
}

float FCEasing::EaseOutQuart(float t)
{
	float m = t - 1;
	return 1 - m * m * m * m;
}

float FCEasing::EaseInOutQuart(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return t * t2 * t2 * t2;
	}
	else
	{
		float m = t - 1;
		return 1 - m * m * m * m * 8;
	}
}

float FCEasing::EaseInQuint(float t)
{
	return t * t * t * t * t;
}

float FCEasing::EaseOutQuint(float t)
{
	float m = t - 1;
	return 1 + m * m * m * m * m;
}

float FCEasing::EaseInOutQuint(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return t * t2 * t2 * t2 * t2;
	}
	else
	{
		float m = t - 1;
		return 1 + m * m * m * m * m * 16;
	}
}

float FCEasing::EaseInExpo(float t)
{
	if (t <= 0)
	{
		return 0;
	}
	if (t >= 1)
	{
		return 1;
	}
	return FMath::Pow(2, 10 * (t - 1));
}

float FCEasing::EaseOutExpo(float t)
{
	if (t <= 0)
	{
		return 0;
	}
	if (t >= 1)
	{
		return 1;
	}
	return 1 - FMath::Pow(2, -10 * t);
}

float FCEasing::EaseInOutExpo(float t)
{
	if (t <= 0)
	{
		return 0;
	}
	if (t >= 1)
	{
		return 1;
	}
	if (t < 0.5f)
	{
		return FMath::Pow(2, 10 * (2 * t - 1) - 1);
	}
	else
	{
		return 1 - FMath::Pow(2, -10 * (2 * t - 1) - 1);
	}
}

float FCEasing::EaseInCirc(float t)
{
	return 1 - FMath::Sqrt(1 - t * t);
}

float FCEasing::EaseOutCirc(float t)
{
	float m = t - 1;
	return FMath::Sqrt(1 - m * m);
}

float FCEasing::EaseInOutCirc(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return (1 - FMath::Sqrt(1 - t2 * t2)) * .5f;
	}
	else
	{
		float m = t - 1;
		return (FMath::Sqrt(1 - 4 * m * m) + 1) * .5f;
	}
}

float FCEasing::EaseInElastic(float t, float Amplitude, float Period)
{
	if (t == 0)
	{
		return 0;
	}
	else if (t == 1)
	{
		return 1;
	}
	else
	{
		float m = t - 1;
		float s = Period / 4.0f;
		if (Amplitude > 1)
		{
			s = Period * FMath::Asin(1.0f / Amplitude) / (2.0f * PI);
		}

		return -(Amplitude * FMath::Pow(2, 10 * m) * FMath::Sin((m - s) * (2.0f * PI) / Period));
	}
}
// baked-in-parameters version
// float FCTween::EaseInElastic(float t)
// {
// 	float m = t - 1;
// 	return -FMath::Pow(2, 10 * m) * FMath::Sin((m * 40 - 3) * PI / 6);
// }

float FCEasing::EaseOutElastic(float t, float Amplitude, float Period)
{
	if (t == 0)
	{
		return 0;
	}
	else if (t == 1)
	{
		return 1;
	}
	else
	{
		float s = Period / 4.0f;
		if (Amplitude > 1)
		{
			s = Period * FMath::Asin(1.0f / Amplitude) / (2.0f * PI);
		}
		return 1.0f + Amplitude * FMath::Pow(2, -10 * t) * FMath::Sin((t - s) * (2.0f * PI) / Period);
	}
}
// baked-in-parameters version
// float FCTween::EaseOutElastic(float t)
// {
// 	return 1 + FMath::Pow(2, 10 * (-t)) * FMath::Sin((-t * 40 - 3) * PI / 6);
// }
float FCEasing::EaseInOutElastic(float t, float Amplitude, float Period)
{
	if (t == 0)
	{
		return 0;
	}
	else if (t == 1)
	{
		return 1;
	}
	else
	{
		float m = 2.0f * t - 1;
		float s = Period / 4.0f;
		if (Amplitude > 1)
		{
			s = Period * FMath::Asin(1.0f / Amplitude) / (2.0f * PI);
		}

		if (m < 0)
		{
			return .5f * -(Amplitude * FMath::Pow(2, 10 * m) * FMath::Sin((m - s) * (2.0f * PI) / Period));
		}
		else
		{
			return 1.0f + .5f * (Amplitude * FMath::Pow(2, -10 * t) * FMath::Sin((t - s) * (2.0f * PI) / Period));
		}
	}
}
// baked-in-parameters version
// float FCTween::EaseInOutElastic(float t)
// {
// 	float s = 2 * t - 1;
// 	float k = (80 * s - 9) * PI / 18;
// 	if (s < 0)
// 	{
// 		return -.5f * FMath::Pow(2, 10 * s) * FMath::Sin(k);
// 	}
// 	else
// 	{
// 		return 1 + .5f * FMath::Pow(2, -10 * s) * FMath::Sin(k);
// 	}
// }

float FCEasing::EaseInBounce(float t)
{
	return 1 - EaseOutBounce(1 - t);
}

float FCEasing::EaseOutBounce(float t)
{
	float t2;

	if (t < BOUNCE_K1)
	{
		return BOUNCE_K0 * t * t;
	}
	else if (t < BOUNCE_K2)
	{
		t2 = t - BOUNCE_K3;
		return BOUNCE_K0 * t2 * t2 + 0.75f;
	}
	else if (t < BOUNCE_K4)
	{
		t2 = t - BOUNCE_K5;
		return BOUNCE_K0 * t2 * t2 + 0.9375f;
	}
	else
	{
		t2 = t - BOUNCE_K6;
		return BOUNCE_K0 * t2 * t2 + 0.984375f;
	}
}

float FCEasing::EaseInOutBounce(float t)
{
	float t2 = t * 2;
	if (t2 < 1)
	{
		return .5f - .5f * EaseOutBounce(1 - t2);
	}
	else
	{
		return .5f + .5f * EaseOutBounce(t2 - 1);
	}
}

float FCEasing::EaseInBack(float t, float Overshoot)
{
	return t * t * ((Overshoot + 1) * t - Overshoot);
}

float FCEasing::EaseOutBack(float t, float Overshoot)
{
	float m = t - 1;
	return 1 + m * m * (m * (Overshoot + 1) + Overshoot);
}

float FCEasing::EaseInOutBack(float t, float Overshoot)
{
	float t2 = t * 2;
	float s = Overshoot * BACK_INOUT_OVERSHOOT_MODIFIER;
	if (t < .5f)
	{
		return t * t2 * (t2 * (s + 1) - s);
	}
	else
	{
		float m = t - 1;
		return 1 + 2 * m * m * (2 * m * (s + 1) + s);
	}
}