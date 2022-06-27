#pragma once

#include "CoreMinimal.h"

class FCTweenModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
