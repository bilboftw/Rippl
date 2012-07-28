/************************************************************************/
/* Rippl Pod Interface File                                             */
/*  Returns information about the pod to Rippl                          */
/*                                                                      */
/*  Called a Podule to deter copyright issues~!                         */
/************************************************************************/
#ifndef IPodule_h__
#define IPodule_h__

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
};

#endif // IPodule_h__