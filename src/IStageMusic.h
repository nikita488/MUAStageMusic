#pragma once

class IStageMusic
{
public:
	virtual void Initialize() = 0;

	virtual void Shutdown() = 0;

	virtual void Play() = 0;

	virtual void Stop() = 0;
};

extern IStageMusic& TheStageMusic();
