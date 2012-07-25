/************************************************************************/
/* Holds Configuration about Themes                                     */
/************************************************************************/

// Includes
#include "Macros.h"

#include "r_themes.h"

// Static Defines
RTheme* RTheme::Loaded = NULL;
RTheme* RTheme::_thmBaseTheme = NULL;

void RTheme::Init()
{
	// Load Base 
	_thmBaseTheme = new RTheme("system/theme/Rippl/theme.rplc");
}

void RTheme::Unload()
{
	
}

void RTheme::LoadTheme(const char* szName)
{
	// Unload Old Configuration if needed
	if(Loaded == NULL)
		delete Loaded;

	// Load
	Loaded = new RTheme(szName);
}

RTheme::RTheme(const char* szName) : RConfig(szName)
{
	// Be sure to check document size

	int a;
	_nConf[0]["test"] >> a;
	LOGD("Testing: %u", a);
}

RTheme::~RTheme()
{
	
}