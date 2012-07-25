/************************************************************************/
/* Holds Configuration about Themes                                     */
/************************************************************************/

// Includes
#include <string>

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
	std::string 
	_nConf[0]["MainWindow"]["background"] >> bgst;
	LOGD("Testing: %s", bgst);
}

RTheme::~RTheme()
{
	
}