/************************************************************************/
/* RI Container Abstract Class                                          */
/************************************************************************/
#ifndef ri_container_h__
#define ri_container_h__

// Includes
#include <list>

#include "SDL.h"

// RI Container Abstract Class Defintion
class RIContainer
{
public:
	RIContainer();
	RIContainer(SDL_Rect* sBounds, short z = 0);
	RIContainer(int x, int y, int w, int h, short z = 0);
	virtual ~RIContainer();

	/**
	 * Sets the bounds for the container
	 */
	void							SetBounds(SDL_Rect* sRect);
	void							SetBounds(int x, int y, int w, int h);

	/**
	 * Returns a pointer to the rect object
	 *	which holds the position and size for the object
	 */
	SDL_Rect*						GetBounds();

	/**
	 * Triggers the container to redraw itself, 
	 *	including all of its children.
	 */
	void							Redraw(bool bInternal = false);

	/**
	 * The Z-Index of the control
	 */
	short							Z;

protected:
	
	/**
	 * Called when the control needs to be re-drawn.
	 */
	virtual void					OnDraw() = 0;

	/**
	 * Adds a child to this container
	 */
	void							AddChild(RIContainer* ricChild);

	/**
	 * Removes a child from this container
	 */
	void							RemoveChild(RIContainer* ricChild);

	/**
	 * Called when a child needs to be redrawn
	 *	This MUST be overridden by the super-parent
	 *	(see GetSuperParent())
	 */
	virtual void							Update(RIContainer* ricChild) = 0;

	/**
	 * Retrieves the top-most parent object
	 *	The top most parent object is determined by the first
	 *	parent container with a parent set to NULL.
	 */
	RIContainer*					GetSuperParent();

	RIContainer*					_ricParent;

	SDL_Rect						_srcBounds;

	std::list<RIContainer*>			_lstChildren;
private:
	static bool					SortZ(RIContainer* a, RIContainer* b);
	static bool					DeleteAll(RIContainer*& a);
};

#endif // ri_container_h__