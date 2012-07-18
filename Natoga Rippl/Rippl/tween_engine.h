/************************************************************************/
/* Tween Engine Implementation                                          */
/************************************************************************/
#ifndef tween_engine_h__
#define tween_engine_h__

// Includes
#include <windows.h>
#include <vector>

#include "iTweenEngine.h"

// Tween Equation Typedef
typedef char (*rEaseApplyCB)(Tween* lpTween);

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
	
	inline static char		EaseLinear(Tween* lpTween);
	inline static char		EaseIn(Tween* lpTween);
	inline static char		EaseOut(Tween* lpTween);
	inline static char		EaseInOut(Tween* lpTween);

	static TweenEngine*		_oEngine;

	rEaseApplyCB*	_cbEaseFuncs[4];
	std::vector<Tween*>		_vecTweens;
	HANDLE					_hwndProcessingThread;
private:
	TweenEngine();
	~TweenEngine();
};

#endif // tween_engine_h__