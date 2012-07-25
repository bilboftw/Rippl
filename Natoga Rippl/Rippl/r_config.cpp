/************************************************************************/
/* The Rippl Configuration Class/Setup Code                             */
/************************************************************************/

// Includes
#include <fstream>

#include "Macros.h"
#include "yaml-cpp/yaml.h"
#include "yaml-cpp/node.h"

#include "r_config.h"

RConfig::RConfig(const char* szFile) : _iStream(szFile), _prsParser(_iStream)
{
	// Check that things worked with the ISTREAM
	if(_iStream.fail() || !_iStream.is_open())
		// Log
		LOGE("Could not open configuration file \"%s\"!", szFile);

	// Associate parser with document
	if(!_prsParser.GetNextDocument(_nConf))
		// Log
		LOGE("Could not enumerate document for YAML parser for config file %s", szFile);
}

RConfig::~RConfig()
{
	// Close stream
	_iStream.close();
}