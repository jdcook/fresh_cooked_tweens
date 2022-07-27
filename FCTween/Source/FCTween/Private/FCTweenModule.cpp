#include "FCTweenModule.h"

#include "FCTween.h"
#include "Modules/ModuleManager.h"

void FCTweenModule::StartupModule()
{
	FCTween::Initialize();
}

void FCTweenModule::ShutdownModule()
{
	FCTween::Deinitialize();
}

IMPLEMENT_MODULE(FCTweenModule, FCTween)
