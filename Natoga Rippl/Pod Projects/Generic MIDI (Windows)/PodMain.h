/************************************************************************/
/* Pod Main Entry Point Code                                            */
/************************************************************************/
#ifndef PodMain_h__
#define PodMain_h__

// Includes
#include <windows.h>
#include "IPodule.h"

#include "IOutput.h"

// Windows Midi class
class GenericMidiModule : public IPodule
{
public:
	R_POD_INFORMATION*			GetInfo();
	bool						Initialize(void** lpOutput);
	void						Unitialize();

private:
	R_POD_INFORMATION			_oPodInfo;
	IOutputHandler**			_oOutput;
};

#endif // PodMain_h__