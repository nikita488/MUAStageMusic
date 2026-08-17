#include <Windows.h>
#include <vector>

#include <safetyhook/safetyhook.hpp>

#include "IStageMusic.h"

void OnInitializeHook()
{
#if _DEBUG
	AllocConsole();

	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);
#endif

	static std::vector<SafetyHookMid> hooks;

	//CMenuTeam::StartOpen
	hooks.push_back(safetyhook::create_mid(0x6FEC28, [](SafetyHookContext& ctx)
	{
		TheStageMusic().Initialize();
		TheStageMusic().Play();
	}));

	//CMenuTeam::FinishClose
	hooks.push_back(safetyhook::create_mid(0x6FC0D5, [](SafetyHookContext& ctx)
	{
		TheStageMusic().Stop();
	}));

	//CMenuTeam::~CMenuTeam
	hooks.push_back(safetyhook::create_mid(0x6F8D33, [](SafetyHookContext& ctx)
	{
		TheStageMusic().Shutdown();
	}));
}
