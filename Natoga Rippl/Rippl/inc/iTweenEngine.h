/************************************************************************/
/* Tween Engine Interface                                               */
/************************************************************************/
#ifndef iTweenEngine_h__
#define iTweenEngine_h__

// Define FPS
#define R_TWEEN_ENGINE_FPS 100

// Forward Delcare Tween Class
class Tween;

// Callback Type Enum
typedef enum
{
	START,
	FINISH,
	PROGRESS
} R_TWEEN_CB_MSG;

// Easing Methods
typedef enum
{
	LINEAR,
	EIN,
	EOUT,
	INOUT
} R_TWEEN_EASE;

// Tween Callback Typedef
typedef void (*rTweenCallback)(Tween* lpTween, R_TWEEN_CB_MSG rtcmMSG);

// Tween Struct Definition
class Tween 
{
public:
	double dDuration;
	double dDelay;
	double dCurrentPosition;
	double dEasedValue;
	rTweenCallback cbOnEvent;
	R_TWEEN_EASE rteEase;

	union
	{
		long void* lpVoid;
		long int iInt;
	} uArg;

	Tween(long plDuration,
	long plDelay,
	rTweenCallback pcbOnEvent,
	R_TWEEN_EASE prteEase)
	{
		// Store Values
		dDuration = plDuration;
		dDelay = plDelay;
		dCurrentPosition = 0;
		cbOnEvent = pcbOnEvent;
		rteEase = prteEase;
		dEasedValue = 0;
	}

	Tween()
	{
		// Set all values to NULL/0
		dDuration = 0;
		dDelay = 0;
		dCurrentPosition = 0;
		dEasedValue = 0;
		cbOnEvent = NULL;
		rteEase = LINEAR;
	}

	unsigned char GetCharProg()
	{
		// Return
		return (unsigned char)((dCurrentPosition / dDuration) * 255);
	}

	void Adjust()
	{
		dDuration /= (1000/R_TWEEN_ENGINE_FPS);
		dDelay /= (1000/R_TWEEN_ENGINE_FPS);
	}
};

// Interface Definition
interface iTweenEngine
{
public:
	virtual void			Add(Tween* lpTween) = 0;
	virtual void			Remove(Tween* lpTween) = 0;
};

#endif // iTweenEngine_h__