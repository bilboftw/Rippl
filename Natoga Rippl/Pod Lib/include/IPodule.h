/************************************************************************/
/* Rippl Pod Interface File                                             */
/*  Returns information about the pod to Rippl                          */
/*                                                                      */
/*  Called a Podule to deter copyright issues~!                         */
/************************************************************************/
#ifndef IPodule_h__
#define IPodule_h__

// Includes
#include <Windows.h>

// Pod Type Enum
typedef enum
{
	MIDI,
	DMX,
	AUDIO,
	FILETYPE
} R_POD_TYPE;

// Pod Information struct
typedef struct  
{
	char* Name;				// The name of the Pod
	char* Version;			// The version of the pod
	char* Author;			// The programmer/branch
	char* Manufacturer;		// The manufacturer of the device that is being interfaced
	R_POD_TYPE Type;		// The type of pod
} R_POD_INFORMATION;

// Definition
interface IPodule
{
public:
	/**
	 * Returns a struct holding the basic information about
	 *	the pod
	 */
	virtual R_POD_INFORMATION*						GetInfo() = 0;

	/**
	 * Initializes the pod instance
	 *
	 *	This function is passed an interface object that is used
	 *	to output messages. It is a pointer to a pointer, so dereference
	 *	it and then use the object dereference operator to access the properties.
	 *	This after casting it to an IOutput object first, of course.
	 *
	 *	NOTE:	This function is called in place of DLLMain. Make sure to put all
	 *			initialization code here. Errors here WILL break loading execution,
	 *			so make sure to use the DisplayMessage or DisplayError methods
	 *			on a last-resort basis.
	 */
	virtual void									Initialize(void** lpOutput) = 0;

	/**
	 * Called when the pod instance expires or is unloaded
	 *	
	 *	Put all memory management, garbage collection and/or disconnection code
	 *	here.
	 *
	 *	NOTE:	This is called in favor of the destructor, as calling of the destructor
	 *			may be unreliable between updates. DO NOT RELY ON A DESTRUCTOR.
	 *			Rely on this function to be called instead.
	 *
	 *	NOTE:	DO NOT DELETE THE IOUTPUT OBJECT! This will break the rest of the
	 *			program!
	 */
	virtual void									Unitialize() = 0;
};

/**
 * Returns a handle to the pod instance
 *	NOTE: THIS MUST BE IMPLEMENTED BY ALL PODS!
 */
extern "C" __declspec(dllexport) IPodule* GetPodule();

#endif // IPodule_h__