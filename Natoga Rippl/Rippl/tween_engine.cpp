/************************************************************************/
/* Tween Engine Implementation                                          */
/************************************************************************/

// Includes
#include <Windows.h>
#include <vector>

#include "iTweenEngine.h"
#include "Macros.h"

#include "tween_engine.h"

// Static Declarations
TweenEngine* TweenEngine::_oEngine = NULL;

TweenEngine* TweenEngine::Get()
{
	// Create if needed
	if(_oEngine == NULL)
		_oEngine = new TweenEngine();

	// Return
	return _oEngine;
}

TweenEngine::TweenEngine()
{
	// Set up easing functions
	_cbEaseFuncs[LINEAR] = (rEaseApplyCB*)&EaseLinear;
	_cbEaseFuncs[EIN] = (rEaseApplyCB*)&EaseIn;
	_cbEaseFuncs[INOUT] = (rEaseApplyCB*)&EaseInOut;
	_cbEaseFuncs[EOUT] = (rEaseApplyCB*)&EaseOut;

	// Attempt to create thread
	_hwndProcessingThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)&ThreadEP, this, NULL, NULL);

	// Check return value
	if(_hwndProcessingThread == INVALID_HANDLE_VALUE)
	{
		// Error and assert
		LOGE("Could not start tween engine thread: %u", GetLastError());
		assert(false);
		return;
	}else
		LOGI("Tween engine started");
}

TweenEngine::~TweenEngine()
{
	// Terminate the thread
	TerminateThread(_hwndProcessingThread, 0);

	// Iterate and delete all of the tween objects
	std::vector<Tween*>::iterator i;
	for(i = _vecTweens.begin(); i < _vecTweens.end(); i++)
		delete (*i);

	// Clear vector
	_vecTweens.clear();

	// Set Global Pointer to NULL
	TweenEngine::_oEngine = NULL;
}

void TweenEngine::Add(Tween *lpTween)
{
	// Check to see we don't already have it in there
	std::vector<Tween*>::iterator i;
	for(i = _vecTweens.begin(); i < _vecTweens.end(); i++)
		// Check pointer
		if(*i == lpTween)
			// Return
			return;

	// Push onto the end
	_vecTweens.push_back(lpTween);
}

void TweenEngine::Remove(Tween *lpTween)
{
	// Iterate and remove
	std::vector<Tween*>::iterator i;
	for(i = _vecTweens.begin(); i < _vecTweens.end(); i++)
		// Check pointer
		if(*i == lpTween)
		{
			// Remove
			_vecTweens.erase(i);

			// Return
			return;
		}
}

void TweenEngine::Pause()
{
	// Pause the thread
	//	TODO: Implement thread suspend count checks
	SuspendThread(_hwndProcessingThread);
}

void TweenEngine::Resume()
{
	// Resume the thread
	//	TODO: Implement thread suspend count checks
	ResumeThread(_hwndProcessingThread);
}

DWORD TweenEngine::ThreadEP(PVOID arg)
{
	// Convert Pointer
	TweenEngine* oEngine = (TweenEngine*)arg;

	// Set up iterator
	std::vector<Tween*>::iterator i;

	// Loop!
	while(true)
	{
		// Iterate through vectors
		// Check to see we don't already have it in there
		for(i = oEngine->_vecTweens.begin(); i < oEngine->_vecTweens.end(); i++)
		{
			// If it's still being delayed...
			if((*i)->lDelay > 0)
			{
				// Decrement
				--((*i)->lDelay);

				// Check for start
				if((*i)->lDelay == 0)
					// Invoke
					if((*i)->cbOnEvent != NULL)
						((rTweenCallback)(*i)->cbOnEvent)(*i, START);
			}

			// Or, if we are performing a tick...
			else if((*i)->lDuration > (*i)->lCurrentPosition)
			{
				// Increment current position
				++((*i)->lCurrentPosition);

				// Apply tweening
				char cNew = ((rEaseApplyCB)oEngine->_cbEaseFuncs[(char)(*i)->rteEase])(*i);

				// Check differences
				if(cNew != (*i)->cEasedValue)
				{
					// Apply
					(*i)->cEasedValue = cNew;

					// Invoke
					if((*i)->cbOnEvent != NULL)
						((rTweenCallback)(*i)->cbOnEvent)(*i, PROGRESS);
				}
			}

			// Or, the tween has finished!
			else
			{
				// Invoke callback
				if((*i)->cbOnEvent != NULL)
					((rTweenCallback)(*i)->cbOnEvent)(*i, FINISH);

				// Delete the object
				delete (*i);

				// Remove from vector
				oEngine->_vecTweens.erase(i);
			}
		}

		// Sleep for a millisecond!
		Sleep(1);
	}

	// Return success
	return 0;
}

char TweenEngine::EaseLinear(Tween *lpTween)
{
	// Return
	return lpTween->GetPercentComplete();
}

char TweenEngine::EaseIn(Tween *lpTween)
{
	// Return
	return (char)((100 * lpTween->lCurrentPosition * lpTween->lCurrentPosition) / (lpTween->lDuration * lpTween->lDuration));
}

char TweenEngine::EaseOut(Tween* lpTween)
{
	// Return
	return (char)((((-100) * lpTween->lCurrentPosition * lpTween->lCurrentPosition) / (lpTween->lDuration * lpTween->lDuration)) + ((2*100*lpTween->lCurrentPosition) / lpTween->lDuration));
}

char TweenEngine::EaseInOut(Tween *lpTween)
{
	// If we're easing in
	if(lpTween->lCurrentPosition < (lpTween->lDuration / 2))
		// Return
		return (char)((2*100*lpTween->lCurrentPosition * lpTween->lCurrentPosition)/(lpTween->lDuration * lpTween->lDuration));
	
	// Calc diff and return
	double ts = (lpTween->lCurrentPosition - (lpTween->lDuration / 2));
	return (char)((((-2)* 100 * ts * ts)/(lpTween->lDuration * lpTween->lDuration)) + ((2*100*ts)/lpTween->lDuration) + 100/2);
}