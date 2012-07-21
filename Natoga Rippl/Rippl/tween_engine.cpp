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
	// Adjust
	lpTween->Adjust();

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

	// Loop!
	while(true)
	{
		// Set up iterator
		std::vector<Tween*>::iterator i = oEngine->_vecTweens.begin();

		// Iterate through vectors
		// Check to see we don't already have it in there
		while(i != oEngine->_vecTweens.end())
		{
			// If it's still being delayed...
			if((*i)->dDelay > 0)
			{
				// Decrement
				--((*i)->dDelay);

				// Check for start
				if((*i)->dDelay == 0)
					// Invoke
					if((*i)->cbOnEvent != NULL)
						((rTweenCallback)(*i)->cbOnEvent)(*i, START);

				// Increment
				i++;
			}

			// Or, if we are performing a tick...
			else if((*i)->dDuration > (*i)->dCurrentPosition)
			{
				// Increment current position
				++((*i)->dCurrentPosition);

				// Apply tweening
				double dNew = ((rEaseApplyCB)oEngine->_cbEaseFuncs[(char)(*i)->rteEase])(*i);

				// Check differences
				if(dNew != (*i)->dEasedValue)
				{
					// Apply
					(*i)->dEasedValue = dNew;

					// Invoke
					if((*i)->cbOnEvent != NULL)
						((rTweenCallback)(*i)->cbOnEvent)(*i, PROGRESS);
				}

				// Increment
				i++;
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
				//	NOTE: This increments for us.
				i = oEngine->_vecTweens.erase(i);
			}
		}

		// Sleep for a millisecond!
		Sleep(1000 / R_TWEEN_ENGINE_FPS);
	}

	// Return success
	return 0;
}

double TweenEngine::EaseLinear(Tween *lpTween)
{
	// Return
	return (lpTween->dCurrentPosition / lpTween->dDuration);
}

double TweenEngine::EaseIn(Tween *lpTween)
{
	// Return
	return ((255 * lpTween->dCurrentPosition * lpTween->dCurrentPosition) / (lpTween->dDuration * lpTween->dDuration));
}

double TweenEngine::EaseOut(Tween* lpTween)
{
	// Return
	return ((((-255) * lpTween->dCurrentPosition * lpTween->dCurrentPosition) / (lpTween->dDuration * lpTween->dDuration)) + ((2*255*lpTween->dCurrentPosition) / lpTween->dDuration));
}

double TweenEngine::EaseInOut(Tween *lpTween)
{
	// If we're easing in
	if(lpTween->dCurrentPosition < (lpTween->dDuration / 2))
		// Return
		return ((2*255*lpTween->dCurrentPosition * lpTween->dCurrentPosition)/(lpTween->dDuration * lpTween->dDuration));
	
	// Calc diff and return
	double ts = (lpTween->dCurrentPosition - (lpTween->dDuration / 2));
	return ((((-2)* 255 * ts * ts)/(lpTween->dDuration * lpTween->dDuration)) + ((2*255*ts)/lpTween->dDuration) + 255/2);
}