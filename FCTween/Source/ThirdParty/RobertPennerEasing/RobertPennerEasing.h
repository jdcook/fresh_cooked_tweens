// Copyright 2001 Robert Penner. All Rights Reserved.
// MIT license https://opensource.org/license/MIT

class RobertPennerEasing
{
	
public:
	static float EaseSmoothstep(float t, float x0 = 0, float x1 = 1)
	{
		float x = FMath::Clamp<float>((t - x0) / (x1 - x0), 0.0f, 1.0f);
		return x * x * (3.0f - 2.0f * x);
	}
	static float EaseInSine(float t)
	{
		return 1 - FMath::Cos(t * PI * .5f);
	}
	static float EaseOutSine(float t)
	{
		return FMath::Sin(t * PI * .5f);
	}
	static float EaseInOutSine(float t)
	{
		return 0.5f * (1 - FMath::Cos(t * PI));
	}
	static float EaseInQuad(float t)
	{
		return t * t;
	}
	static float EaseOutQuad(float t)
	{
		return t * (2 - t);
	}
	static float EaseInOutQuad(float t)
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
	static float EaseInCubic(float t)
	{
		return t * t * t;
	}
	static float EaseOutCubic(float t)
	{
		float m = t - 1;
		return 1 + m * m * m;
	}
	static float EaseInOutCubic(float t)
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
	static float EaseInQuart(float t)
	{
		return t * t * t * t;
	}
	static float EaseOutQuart(float t)
	{
		float m = t - 1;
		return 1 - m * m * m * m;
	}
	static float EaseInOutQuart(float t)
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
	static float EaseInQuint(float t)
	{
		return t * t * t * t * t;
	}
	static float EaseOutQuint(float t)
	{
		float m = t - 1;
		return 1 + m * m * m * m * m;
	}
	static float EaseInOutQuint(float t)
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
	static float EaseInExpo(float t)
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
	static float EaseOutExpo(float t)
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
	static float EaseInOutExpo(float t)
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
	static float EaseInCirc(float t)
	{
		return 1 - FMath::Sqrt(1 - t * t);
	}
	static float EaseOutCirc(float t)
	{
		float m = t - 1;
		return FMath::Sqrt(1 - m * m);
	}
	static float EaseInOutCirc(float t)
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
	static float EaseInBounce(float t)
	{
		return 1 - EaseOutBounce(1 - t);
	}
	static float EaseOutBounce(float t)
	{
		float t2;
		const float BOUNCE_R = 1.0f / 2.75f;		  // reciprocal
		const float BOUNCE_K1 = BOUNCE_R;			  // 36.36%
		const float BOUNCE_K2 = 2 * BOUNCE_R;		  // 72.72%
		const float BOUNCE_K3 = 1.5f * BOUNCE_R;	  // 54.54%
		const float BOUNCE_K4 = 2.5f * BOUNCE_R;	  // 90.90%
		const float BOUNCE_K5 = 2.25f * BOUNCE_R;	  // 81.81%
		const float BOUNCE_K6 = 2.625f * BOUNCE_R;	  // 95.45%
		const float BOUNCE_K0 = 7.5625f;

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
	static float EaseInOutBounce(float t)
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
	static float EaseInBack(float t, float Overshoot = 1.70158f)
	{
		return t * t * ((Overshoot + 1) * t - Overshoot);
	}
	static float EaseOutBack(float t, float Overshoot = 1.70158f)
	{
		float m = t - 1;
		return 1 + m * m * (m * (Overshoot + 1) + Overshoot);
	}
	static float EaseInOutBack(float t, float Overshoot = 1.70158f)
	{
		float t2 = t * 2;
		const float BACK_INOUT_OVERSHOOT_MODIFIER = 1.525f;
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
};
