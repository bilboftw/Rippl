/************************************************************************/
/* Holds Configuration about Themes                                     */
/************************************************************************/
#ifndef r_themes_h__
#define r_themes_h__

// Includes
#include <string>

#include "r_config.h"

// Usings
using std::string;

// Theme object definition
typedef struct 
{
	string Name;

	struct R_THEME_INFO_IMAGES
	{
		struct R_THEME_INFO_IMAGE_DATA
		{
			string Path;
		}
			MainWindowBackgroundImage;		
		;
	}Images;
} R_THEME_INFORMATION;

// Themes Class Definition
class RTheme : public RConfig
{
public:
	/**
	 * Initializes and loads configuration
	 *	regarding themes
	 */
	static void						Init();

	/**
	 * Unloads all theme data
	 */
	static void						Unload();

	static void						LoadTheme(const char* szName);

	RTheme(const char* szName);
	~RTheme();

	static RTheme*					Loaded;

	R_THEME_INFORMATION				Theme;
protected:

	/**
	 * Builds the theme object
	 */
	void							BuildTheme();

	static RTheme*					_thmBaseTheme;
};

#endif // r_themes_h__