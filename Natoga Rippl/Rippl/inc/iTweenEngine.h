/************************************************************************/
/* Tween Engine Interface                                               */
/************************************************************************/
#ifndef iTweenEngine_h__
#define iTweenEngine_h__

// Forward Delcare Tween Class
class Tween;

// Callback Type Enum
typedef enum
{
	START,
	TICK,
	FINISH
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
	long lDuration;
	long lDelay;
	long lCurrentPosition;
	rTweenCallback cbOnEvent;
	R_TWEEN_EASE rteEase;

	Tween(long plDuration,
	long plDelay,
	long plCurrentPosition,
	rTweenCallback pcbOnEvent,
	R_TWEEN_EASE prteEase)
	{
		// Store Values
		lDuration = plDuration;
		lDelay = plDelay;
		lCurrentPosition = plCurrentPosition;
		cbOnEvent = pcbOnEvent;
		rteEase = prteEase;
	}

	Tween()
	{
		// Set all values to NULL/0
		lDuration = 0;
		lDelay = 0;
		lCurrentPosition = 0;
		cbOnEvent = NULL;
		rteEase = LINEAR;
	}

	char GetPercentComplete()
	{
		// Return
		return (char)((((double)lCurrentPosition) / ((double)lDuration)) * 100);
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