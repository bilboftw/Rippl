/************************************************************************/
/* The Rippl Configuration Class/Setup Code                             */
/************************************************************************/
#ifndef r_config_h__
#define r_config_h__

// Includes
#include <fstream>

#include "yaml-cpp/yaml.h"

// Configuration Class Definition
class RConfig
{
public:
	RConfig(const char* szFile);
	~RConfig();

protected:
	std::ifstream					_iStream;
	YAML::Node						_nConf;
	YAML::Parser					_prsParser;
};

#endif // r_config_h__