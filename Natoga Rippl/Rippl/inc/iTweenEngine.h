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
}R_TWEEN_CB_MSG;

// TODO: Implement Easing

// Tween Callback Typedef
typedef void (*rTweenCallback)(Tween* lpTween, R_TWEEN_CB_MSG rtcmMSG);

// Tween Struct Definition
class Tween 
{
public:
	unsigned long lDuration;
	unsigned long lDelay;
	unsigned long lCurrentPosition;
	rTweenCallback cbOnEvent;

	Tween(unsigned long plDuration,
	unsigned long plDelay,
	unsigned long plCurrentPosition,
	rTweenCallback pcbOnEvent)
	{
		// Store Values
		lDuration = plDuration;
		lDelay = plDelay;
		lCurrentPosition = plCurrentPosition;
		cbOnEvent = pcbOnEvent;
	}

	Tween()
	{
		// Set all values to NULL/0
		lDuration = 0;
		lDelay = 0;
		lCurrentPosition = 0;
		cbOnEvent = NULL;
	}

	char GetPercentComplete()
	{
		// Get double
		double p = ((double)lCurrentPosition) / ((double)lDuration);
		
		// Return
		return (char)(p * 100);
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