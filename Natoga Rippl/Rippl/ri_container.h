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
	RIContainer();
	RIContainer(SDL_Rect* sBounds);
	RIContainer(SDL_Rect* sBounds, short z);
	RIContainer(int x, int y, int w, int h);
	RIContainer(int x, int y, int w, int h, short z);
	~RIContainer();

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
	void							Redraw();

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
	void							Update(RIContainer* ricChild) { throw "Method not overridden, or object not super-parent!"; };

	/**
	 * Retrieves the top-most parent object
	 *	The top most parent object is determined by the first
	 *	parent container with a parent set to NULL.
	 */
	RIContainer*					GetSuperParent();


	RIContainer*					_ricParent;

	SDL_Rect						_srcBounds;

	std::vector<RIContainer*>		_vecChildren;
private:
	static bool						SortZ(RIContainer* a, RIContainer* b);
};

#endif // ri_container_h__