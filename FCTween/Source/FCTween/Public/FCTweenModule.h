// MIT License - Copyright 2026 Jared Cook
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class FCTweenModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
