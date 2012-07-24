/************************************************************************/
/* RI Container Abstract Class                                          */
/************************************************************************/

// Includes
#include <algorithm>

#include "SDL.h"

#include "ri_container.h"

RIContainer::RIContainer()
{
	// Setup parent and Z
	_ricParent = NULL;
	Z = 0;

	// Default values (0, 0, 0, 0)
	memset(&_srcBounds, 0, sizeof(_srcBounds));
}

RIContainer::RIContainer(int x, int y, int w, int h)
{
	// Setup parent and Z
	_ricParent = NULL;
	Z = 0;

	// Set up bounds
	SetBounds(x, y, w, h);
}

RIContainer::RIContainer(SDL_Rect *sBounds)
{
	// Setup parent and Z
	_ricParent = NULL;
	Z = 0;

	// Store bounds
	SetBounds(sBounds);
}

RIContainer::RIContainer(int x, int y, int w, int h, short z)
{
	// Setup parent
	_ricParent = NULL;

	// Store Z
	Z = z;

	// Set up bounds
	SetBounds(x, y, w, h);
}

RIContainer::RIContainer(SDL_Rect *sBounds, short z)
{
	// Setup parent
	_ricParent = NULL;

	// Store Z
	Z = z;

	// Store bounds
	SetBounds(sBounds);
}

RIContainer::~RIContainer()
{
	// Remove from parent
	_ricParent->RemoveChild(this);
}

void RIContainer::AddChild(RIContainer *ricChild)
{
	// Check if we've already added this child
	if(std::search(_vecChildren.begin(), _vecChildren.end(), &ricChild, &ricChild) != _vecChildren.end())
		// Return
		return;

	// Add
	_vecChildren.push_back(ricChild);

	// Tell the child we're the parent
	ricChild->_ricParent = this;
}

void RIContainer::RemoveChild(RIContainer *ricChild)
{
	// Get iterator
	std::vector<RIContainer*>::iterator it = std::search(_vecChildren.begin(), _vecChildren.end(), &ricChild, &ricChild);

	// If we ding'd..
	if(it != _vecChildren.end())
		// Remove
		_vecChildren.erase(it);
}

RIContainer* RIContainer::GetSuperParent()
{
	// Setup return
	RIContainer* ret = this;

	// Recurse
	while(ret->_ricParent != NULL) ret = ret->_ricParent;

	// Return
	return ret;
}

void RIContainer::Redraw()
{
	// Signal our drawing method
	OnDraw();

	// Check if we have children
	if(_vecChildren.size() == 0)
		// Nothing to do!
		return;

	// Sort our Z-Indexes
	std::sort(_vecChildren.begin(), _vecChildren.end(), SortZ);

	// Signal all children to redraw
	std::vector<RIContainer*>::iterator it = _vecChildren.begin();
	while(it != _vecChildren.end())
		// Redraw, you!
		(*it)->Redraw();
}

bool RIContainer::SortZ(RIContainer* a, RIContainer* b)
{
	// Check Z indexes
	return (a->Z < b->Z);
}

void RIContainer::SetBounds(int x, int y, int w, int h)
{
	// Set
	_srcBounds.x = x;
	_srcBounds.y = y;
	_srcBounds.w = w;
	_srcBounds.h = h;
}

void RIContainer::SetBounds(SDL_Rect *sRect)
{
	// Store bounds
	_srcBounds = *sRect;
}

SDL_Rect* RIContainer::GetBounds()
{
	// Return
	return &_srcBounds;
}