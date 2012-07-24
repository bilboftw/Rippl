#include "ri_container.h"
#include "Macros.h"

class GenericChild : public RIContainer
{
public:
	GenericChild() : RIContainer(0, 0, 5, 5) {};

	void RemoveChild(RIContainer* ricChild)
	{
		LOGD("Removing child");
		RIContainer::RemoveChild(ricChild);
	}

	void Redraw()
	{
		LOGD("Redraw");
		RIContainer::Redraw();
	}

	void AddChild(RIContainer* ricChild)
	{
		LOGD("Adding child");
		RIContainer::AddChild(ricChild);
	}

	void OnDraw()
	{
		LOGD("OnDraw");
	}

};

class WinParent : public RIContainer
{
public:
	WinParent() : RIContainer(0, 0, 5, 5) {};

	void RemoveChild(RIContainer* ricChild)
	{
		LOGD("PR: Removing child");
		RIContainer::RemoveChild(ricChild);
	}

	void Redraw()
	{
		LOGD("PR: Redraw");
		RIContainer::Redraw();
	}

	void AddChild(RIContainer* ricChild)
	{
		LOGD("PR: Adding child");
		RIContainer::AddChild(ricChild);
	}

	void OnDraw()
	{
		LOGD("PR: OnDraw");
	}

	void Update(RIContainer* ricChild)
	{
		LOGD("PR: Updating");
		RIContainer::Update(ricChild);
	}
};

void TESTCONTS()
{
	// Create parent
	WinParent parent;

	// Create children
	GenericChild c1;
	GenericChild c2;
	GenericChild c3;

	parent.AddChild(&c1);
	parent.AddChild(&c2);
	parent.AddChild(&c3);

	parent.Redraw();
}