#include "CStageMusic.h"

#if !defined(RATL_STRING_VS_INC)
	#include <Common/Ratl/string_vs.h>
#endif

#include <Sound/CZAxisSoundSystem.h>
#include <Utils/CPluginConfig.h>

const char* MUSIC_FILE = "x_stage.zsd";
const char* DEFAULT_MUSIC_NAME = "common/menus/music/stage";

CStageMusic::CStageMusic() :
	mSoundHandle(SOUND_NULL),
	mInstanceHandle(SOUND_INSTANCE_NULL),
	mInitialized(false),
	mMusicLoaded(false)
{
}

CSoundSystem& TheCSoundSystem()
{
	return (CSoundSystem&)TheSoundSystem();
}

void CStageMusic::Initialize()
{
	if (mInitialized)
	{
		return;
	}
	
	const char* name = TheCSoundSystem().ZSD_CreatePathedName(MUSIC_FILE, false);

	if (TheCSoundSystem().ZSD_Load(name))
	{
		mInitialized = true;
	}
}

void CStageMusic::Shutdown()
{
	if (mInitialized)
	{
		UnloadMusic();
		TheCSoundSystem().ZSD_Close(MUSIC_FILE, false);
		mInitialized = false;
	}
}

void CStageMusic::LoadMusic()
{
	static bool firstLoadCheck = false;

	if (!mMusicLoaded)
	{
		ratl::string_vs<256> name(DEFAULT_MUSIC_NAME);
		PluginIni().Get("MAIN", "Name", name.c_str(), name.capacity(), DEFAULT_MUSIC_NAME);

		if (TheSoundSystem().SoundExists(name) || !firstLoadCheck)
		{
			mSoundHandle = TheSoundSystem().LoadSound(name, true, true);
		}

		mMusicLoaded = true;
	}

	firstLoadCheck = true;
}

void CStageMusic::UnloadMusic()
{
	if (mMusicLoaded)
	{
		if (TheSoundSystem().UnloadSound(mSoundHandle))
		{
			mSoundHandle = SOUND_NULL;
		}

		mInstanceHandle = SOUND_INSTANCE_NULL;
		mMusicLoaded = false;
	}
}

void CStageMusic::Play()
{
	if (!mInitialized)
	{
		return;
	}
	
	if (!mMusicLoaded)
	{
		LoadMusic();
	}

	Stop();

	int handle = TheSoundSystem().PlayMusicReturnInstance(mSoundHandle, true);

	if (handle != SOUND_INSTANCE_NULL)
	{
		mInstanceHandle = handle;
	}
}

void CStageMusic::Stop()
{
	if (!mInitialized)
	{
		return;
	}
	
	if (mInstanceHandle != SOUND_INSTANCE_NULL)
	{
		TheSoundSystem().StopSound(mInstanceHandle);
		mInstanceHandle = SOUND_INSTANCE_NULL;
	}
}

IStageMusic& TheStageMusic()
{
	static CStageMusic stageMusic;
	return stageMusic;
}
