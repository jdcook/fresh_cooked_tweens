// Copyright 2025 Phaser Studio Inc. All Rights Reserved.
// MIT license https://opensource.org/license/MIT

class PhaserEasing
{
public:
	static float EaseStepped(float t, int Steps = 10)
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
	static float EaseInElastic(float t, float Amplitude = 1.0f, float Period = .2f)
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
	static float EaseOutElastic(float t, float Amplitude = 1.0f, float Period = .2f)
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
	static float EaseInOutElastic(float t, float Amplitude = 1.0f, float Period = .2f)
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
};
