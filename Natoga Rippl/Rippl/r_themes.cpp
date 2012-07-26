/************************************************************************/
/* Holds Configuration about Themes                                     */
/************************************************************************/

// Includes
#include <string>

#include "Macros.h"

#include "ri_image.h"
#include "r_themes.h"

// Using Definitions
using std::string;

// Static Defines
RTheme* RTheme::Loaded = NULL;
RTheme* RTheme::_thmBaseTheme = NULL;

void RTheme::Init()
{
	// Load Base 
	_thmBaseTheme = new RTheme("system/theme/Rippl/theme.rth");
	Loaded = _thmBaseTheme;
}

void RTheme::Unload()
{

}

void RTheme::LoadTheme(const char* szName)
{
	// Unload Old Configuration if needed
	if(Loaded != NULL)
		delete Loaded;

	// Load
	Loaded = new RTheme(szName);
}

/**
 * This constructor assumes ALL of the data will be there!
 *	This is based off the base theme.
 */
RTheme::RTheme(const char* szName) : RConfig(szName)
{
	// Zero the constructed theme data
	memset(&Theme, 0, sizeof(Theme));

	// Get name
	Theme.ThemeInfo.Name = GetNameFromNode();

	// Setup Base Path
	_strBasePath = "system/theme/";
	_strBasePath.append(Theme.ThemeInfo.Name);
	_strBasePath.append("/");

	// Pull data
	LOGD("Retrieving theme info");
	_nConf["ThemeInfo"]["Author"] >> Theme.ThemeInfo.Author;
	_nConf["ThemeInfo"]["Website"] >> Theme.ThemeInfo.Website;

	Theme.UI.MainWindow.Background = GetImageFromNode(&_nConf["UI"]["MainWindow"], "Background");
}

string RTheme::GetNameFromNode()
{
	// Get ThemeInfo block
	if(_nConf.FindValue("ThemeInfo") == 0)
	{
		LOGE("Theme file does not contain theme info!");
		return string();
	}
	
	// Get name and return
	string ret;
	_nConf["ThemeInfo"]["Name"] >> ret;
	return ret;
}

RIImage* RTheme::GetImageFromNode(const YAML::Node* BaseNode, const char* ChildNode)
{
	// Setup string
	string pthname;
	
	// Get String name
	(*BaseNode)[ChildNode] >> pthname;
	
	// Append to basepath
	pthname.insert(0, _strBasePath);

	// Return new image object
	return new RIImage(pthname.c_str());
}

RTheme::~RTheme()
{
	// Unload all images

}