#pragma once

#include "IStageMusic.h"

class CStageMusic : public IStageMusic
{
private:
	int mSoundHandle;
	int mInstanceHandle;
	bool mInitialized : 1;
	bool mMusicLoaded : 1;

	void LoadMusic();

	void UnloadMusic();

public:
	CStageMusic();

	virtual void Initialize();

	virtual void Shutdown();

	virtual void Play();

	virtual void Stop();
};
