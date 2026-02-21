// MIT License - Copyright 2026 Jared Cook
#include "FCTweenConfig.h"

UFCTweenConfig::UFCTweenConfig()
{
	CategoryName = "Plugins";
	SectionName = "FCTween";
}

FName UFCTweenConfig::GetContainerName() const
{
	return "Project";
}