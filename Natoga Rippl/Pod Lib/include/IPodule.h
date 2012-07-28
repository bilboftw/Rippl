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

// Definition
interface IPodule
{
public:
	const char* 
};

#endif // IPodule_h__