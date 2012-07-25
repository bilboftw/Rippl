/************************************************************************/
/* Holds Configuration about Themes                                     */
/************************************************************************/
#ifndef r_themes_h__
#define r_themes_h__

// Includes
#include "r_config.h"

// Themes Class Definition
class RTheme : public RConfig
{
public:
	/**
	 * Initializes and loads configuration
	 *	regarding themes
	 */
	static void					Init();

	/**
	 * Unloads all theme data
	 */
	static void					Unload();

	static void					LoadTheme(const char* szName);

	RTheme(const char* szName);
	~RTheme();

	static RTheme*					Loaded;

protected:

	static RTheme*					_thmBaseTheme;
};

#endif // r_themes_h__