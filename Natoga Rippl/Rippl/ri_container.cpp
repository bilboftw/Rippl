/************************************************************************/
/* RI Container Abstract Class                                          */
/************************************************************************/

// Includes
#include "SDL.h"

#include "ri_container.h"

RIContainer::RIContainer(int x, int y, int w, int h)
{
	// Store parent
	_ricParent = NULL;

	// Set up bounds
	_srcBounds.x = x;
	_srcBounds.y = y;
	_srcBounds.w = w;
	_srcBounds.h = h;
}