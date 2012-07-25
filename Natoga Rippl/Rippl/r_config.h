/************************************************************************/
/* The Rippl Configuration Class/Setup Code                             */
/************************************************************************/
#ifndef r_config_h__
#define r_config_h__

// Includes
#include "yaml-cpp/yaml.h"

// Configuration Class Definition
class RConfig
{
public:

	/**
	 * Initializes configuration files
	 */
	static void					Init();

	/**
	 * Destroys configuration files
	 */
	static void					Destroy();

	RConfig(const wchar_t* szFile);
	~RConfig();


	/**
	 * The base theme file that values are defaulted to
	 *	if not found in derived themes
	 */
	static RConfig*					BaseTheme;
};

#endif // r_config_h__