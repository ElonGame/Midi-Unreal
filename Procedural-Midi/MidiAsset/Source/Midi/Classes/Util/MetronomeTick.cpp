// Copyright -> Scott Bishel

#include "MidiPrivatePCH.h"
#include "MetronomeTick.h"


MetronomeTick::MetronomeTick(TimeSignature* sig, int resolution) 
	: MidiEvent(0, 0)
{
	mResolution = resolution;

	setTimeSignature(sig);
	mCurrentMeasure = 1;
}

void MetronomeTick::setTimeSignature(TimeSignature* sig)
{
	mSignature = sig;
	mCurrentBeat = 0;

	setMetronomeFrequency(sig->getMeter());
}

bool MetronomeTick::update(double ticksElapsed)
{
	mMetronomeProgress += ticksElapsed;

	if (mMetronomeProgress >= mMetronomeFrequency)
	{
		mMetronomeProgress = FMath::Fmod(mMetronomeProgress, mMetronomeFrequency);

		mCurrentBeat = (mCurrentBeat + 1) % mSignature->getNumerator();
		if (mCurrentBeat == 0)
		{
			mCurrentMeasure++;
		}

		return true;
	}
	return false;
}

void MetronomeTick::setMetronomeFrequency(int meter)
{
	switch (meter)
	{
	case TimeSignature::METER_EIGHTH:
		mMetronomeFrequency = mResolution / 2;
		break;
	case TimeSignature::METER_QUARTER:
		mMetronomeFrequency = mResolution;
		break;
	case TimeSignature::METER_HALF:
		mMetronomeFrequency = mResolution * 2;
		break;
	case TimeSignature::METER_WHOLE:
		mMetronomeFrequency = mResolution * 4;
		break;
	}
	// reset progress as result of changed frequency
	mMetronomeProgress = 0;
}

int MetronomeTick::getBeatNumber()
{
	return mCurrentBeat + 1;
}

int MetronomeTick::getMeasure()
{
	return mCurrentMeasure;
}

std::string MetronomeTick::ToString()
{
	std::stringstream ss;
	ss << "Metronome: " << mCurrentMeasure << "\t" << getBeatNumber();
	return ss.str();
}

int MetronomeTick::CompareTo(MidiEvent* o)
{
	return 0;
}

int MetronomeTick::getEventSize()
{
	return 0;
}

int MetronomeTick::getSize()
{
	return 0;
}