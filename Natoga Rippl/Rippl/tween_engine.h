/************************************************************************/
/* Tween Engine Implementation                                          */
/************************************************************************/
#ifndef tween_engine_h__
#define tween_engine_h__

// Includes
#include <windows.h>
#include <list>

#include "iTweenEngine.h"

// Tween Equation Typedef
typedef double (*rEaseApplyCB)(Tween* lpTween);

// Tween Engine Implementation Class Declaration
class TweenEngine : public iTweenEngine
{
public:
	static TweenEngine*		Get();

	void					Add(Tween* lpTween);
	void					Remove(Tween* lpTween);

	void					Pause();
	void					Resume();
protected:
	static DWORD			ThreadEP(PVOID arg);
	
	inline static double	EaseLinear(Tween* lpTween);
	inline static double	EaseIn(Tween* lpTween);
	inline static double	EaseOut(Tween* lpTween);
	inline static double	EaseInOut(Tween* lpTween);

	static TweenEngine*		_oEngine;

	rEaseApplyCB*			_cbEaseFuncs[4];

	std::list<Tween*>		_lstTweens;

	HANDLE					_hwndProcessingThread;
private:
	TweenEngine();
	~TweenEngine();
};

#endif // tween_engine_h__