/************************************************************************/
/* The Rippl Configuration Class/Setup Code                             */
/************************************************************************/

// Includes
#include "yaml-cpp/yaml.h"

#include "r_config.h"

void RConfig::Init()
{
	// Create new log files
	BaseTheme = new RConfig("theme.yml");
}

void RConfig::Destroy()
{
	// Delete config files
	delete BaseTheme;
}

RConfig::RConfig(const wchar_t* szFile)
{
	// Create file
	
}