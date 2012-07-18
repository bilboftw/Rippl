/************************************************************************/
/* Tween Engine Interface                                               */
/************************************************************************/
#ifndef iTweenEngine_h__
#define iTweenEngine_h__

// Callback Type Enum
typedef enum
{
	START,
	TICK,
	FINISH
}R_TWEEN_CB_MSG;

// Tween Callback Typedef
typedef void (*rTweenCallback)(Tween* lpTween, R_TWEEN_CB_MSG rtcmMSG);

// Tween Struct Definition
class Tween 
{
public:
	unsigned double long lDuration;
	unsigned double long lDelay;
	unsigned double long lCurrentPosition;
	rTweenCallback cbOnStart;
	rTweenCallback cbOnTick;
	rTweenCallback cbOnFinish;

	Tween(unsigned double long plDuration,
	unsigned double long plDelay,
	unsigned double long plCurrentPosition,
	rTweenCallback pcbOnStart,
	rTweenCallback pcbOnTick,
	rTweenCallback pcbOnFinish)
	{
		lDuration = plDuration;
		lDelay = plDelay;
		lCurrentPosition = plCurrentPosition;
		cbOnStart = pcbOnStart;
		cbOnTick = pcbOnTick;
		cbOnFinish = pcbOnFinish;
	}

	Tween() {};

	char GetPercentComplete() { return (char)(lCurrentPosition / lDuration); };
};

// Interface Definition
interface iTweenEngine
{
public:
	virtual void			Add(Tween* lpTween) = 0;
	virtual void			Remove(Tween* lpTween) = 0;
};

#endif // iTweenEngine_h__