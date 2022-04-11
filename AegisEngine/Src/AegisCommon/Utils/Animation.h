#pragma once
#include <Vector3.h>
#include <MathUtils.h>
using namespace MathUtils;

struct keyFrame {
	Vector3 pos, scale;
	Vector3 degrees;
	double time;
};

struct Animation {
	int numKeyFrames = 0;
	int currentKeyFrame = 0;
	std::vector<keyFrame> frames;
	float timer = 0;
	bool finished = false;
	bool loop = false;

	Vector3 GetInterpolatedPos()
	{
		return MathUtils::Lerp(getCurrentKeyFrame().pos, getFrame(currentKeyFrame + 1).pos, getNormalizedTime());
	}

	Vector3 GetInterpolatedScale()
	{
		return MathUtils::Lerp(getCurrentKeyFrame().scale, getFrame(currentKeyFrame + 1).scale, getNormalizedTime());
	}

	Vector3 GetInterpolatedEulerAngles()
	{
		return MathUtils::Lerp(getCurrentKeyFrame().degrees, getFrame(currentKeyFrame + 1).degrees, getNormalizedTime());
	}

	//Returns a value between 0 and 1 interpolating frame start and frame end
	float getNormalizedTime()
	{
		return MathUtils::InverseLerp(getCurrentKeyFrame().time, getFrame(currentKeyFrame + 1).time, timer);
	}

	void addTime(float time)
	{
		this->timer += time;
		if (timer > getCurrentKeyFrame().time)
			advanceKeyframe();
	}

	//Advances keyframe number, return to 0 when passing last 
	//keyframe and sets finished to true if loop is false and it was the last keyframe
	bool advanceKeyframe()
	{
		currentKeyFrame = MathUtils::loop(0, numKeyFrames, currentKeyFrame + 1);
		if (currentKeyFrame)
		{
			if (!loop)
				finished = true;
			else
				timer = 0;
		}
		return finished;
	}

	inline keyFrame getCurrentKeyFrame()
	{
		return frames[currentKeyFrame];
	}

	inline keyFrame getFrame(int frame)
	{
		return frames[MathUtils::loop(0, numKeyFrames, frame)];
	}
};