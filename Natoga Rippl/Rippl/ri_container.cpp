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
	// If there is a parent...
	if(_ricParent != NULL)
		// Remove from parent
		_ricParent->RemoveChild(this);

	// Remove all children (if we have any)
	while(!_lstChildren.empty())
	{
		delete _lstChildren.front();
	}
}

void RIContainer::AddChild(RIContainer* ricChild)
{
	// Check if we've already added this child
	if(std::find(_lstChildren.begin(), _lstChildren.end(), ricChild) != _lstChildren.end())
		// Return
		return;

	// Add
	_lstChildren.push_back(ricChild);

	// Set parent
	ricChild->_ricParent = this;
}

void RIContainer::RemoveChild(RIContainer* ricChild)
{
	// Check length
	if(_lstChildren.size() < 1)
		// Return
		return;

	// Get iterator
	std::list<RIContainer*>::iterator it = std::find(_lstChildren.begin(), _lstChildren.end(), ricChild);

	// If we ding'd..
	if(it != _lstChildren.end())
		// Remove
		_lstChildren.erase(it);
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

void RIContainer::Redraw(bool bInternal)
{
	// Signal our drawing method
	OnDraw();

	int sz = _lstChildren.size();

	// Check if we have children
	if(_lstChildren.size() == 0)
		// Nothing to do!
		return;

	// Sort our Z-Indexes
	_lstChildren.sort(SortZ);

	// Signal all children to redraw
	std::list<RIContainer*>::iterator it = _lstChildren.begin();
	while(it != _lstChildren.end())
	{
		// Redraw, you!
		(*it)->Redraw();

		// Increment
		++it;
	}

	// Update parent if not internal call
	if(!bInternal)
		// Get super parent and call update
		GetSuperParent()->Update(this);
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

void RIContainer::SetBounds(SDL_Rect* sRect)
{
	// Store bounds
	_srcBounds = *sRect;
}

SDL_Rect* RIContainer::GetBounds()
{
	// Return
	return &_srcBounds;
}

bool RIContainer::DeleteAll(RIContainer*& a)
{
	// Delete
	delete a;

	// Return true
	return true;
}