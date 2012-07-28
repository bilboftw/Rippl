/************************************************************************/
/* Pod Main Entry Point Code                                            */
/************************************************************************/

// Includes
#include "IPodule.h"
#include "IOutput.h"

#include "PodMain.h"

// Module returner
extern "C" __declspec(dllexport) IPodule* GetPodule()
{
	// Return new instance!
	return new GenericMidiModule();
}

bool GenericMidiModule::Initialize(void** lpOutput)
{
	// Setup info
	memset(&_oPodInfo, 0, sizeof(R_POD_INFORMATION));
	_oPodInfo.Name = "Generic MIDI Interface";
	_oPodInfo.Author = "Qix";
	_oPodInfo.Manufacturer = "Natoga Technologies";
	_oPodInfo.Version = "0.0.1";
	_oPodInfo.Type = PODTYPE_MIDI;

	// Store output object pointer
	_oOutput = (IOutputHandler**)lpOutput;

	// Log
	(*_oOutput)->DisplayMessage("Loaded win midi!");

	// Return
	return true;
}

R_POD_INFORMATION* GenericMidiModule::GetInfo()
{
	// Return
	return &_oPodInfo;
}

void GenericMidiModule::Unitialize()
{
	// Nothing
}