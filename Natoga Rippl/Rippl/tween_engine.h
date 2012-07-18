/************************************************************************/
/* Tween Engine Implementation                                          */
/************************************************************************/
#ifndef tween_engine_h__
#define tween_engine_h__

// Includes
#include <windows.h>
#include <vector>

#include "iTweenEngine.h"

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

	static TweenEngine*		_oEngine;

	std::vector<Tween*>		_vecTweens;
	HANDLE					_hwndProcessingThread;
private:
	TweenEngine();
	~TweenEngine();
};

#endif // tween_engine_h__