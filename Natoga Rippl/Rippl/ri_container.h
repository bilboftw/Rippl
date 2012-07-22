/************************************************************************/
/* RI Container Abstract Class                                          */
/************************************************************************/
#ifndef ri_container_h__
#define ri_container_h__

// Includes
#include <vector>

#include "SDL.h"

// RI Container Abstract Class Defintion
class RIContainer
{
public:
	RIContainer(SDL_Rect* sBounds);
	RIContainer(int x, int y, int w, int h);
	~RIContainer();

	/**
	 * Sets the bounds for the container
	 */
	void							SetBounds(SDL_Rect* sRect);
	void							SetBounds(int x, int y, int w, int h);

	/**
	 * Triggers the container to redraw itself, 
	 *	including all of its children.
	 */
	void							Redraw();

protected:
	
	/**
	 * Adds a child to this container
	 */
	void							AddChild(RIContainer* ricChild);

	/**
	 * Called when a child needs to be redrawn
	 *	This MUST be overridden by the super-parent
	 *	(see GetSuperParent())
	 */
	void							Update(RIContainer* ricChild) { throw "Method not overridden, or object not super-parent!"; };

	/**
	 * Retrieves the top-most parent object
	 *	The top most parent object is determined by the first
	 *	parent container with a parent set to NULL.
	 */
	RIContainer*					GetSuperParent();


	RIContainer*					_ricParent;

	SDL_Surface*					_sfSurface;
	SDL_Rect						_srcBounds;

	std::vector<RIContainer*>		_vecChildren;
};

#endif // ri_container_h__