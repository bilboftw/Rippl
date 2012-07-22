/************************************************************************/
/* Test Interfacing                                                     */
/*  Don't judge me, I was tired and couldn't wrap my head around        */
/*  how we were going to extend the VST interfaces......                */
/************************************************************************/

// Includes
#include <windows.h>
#include <iostream>

interface A
{
public:
	virtual void OutA() = 0;
};

interface B
{
public:
	virtual void OutB() = 0;
};

class C : public A, public B
{
public:
	void OutA();
	void OutB();
};

void C::OutA()
{
	printf("Out A\n");
}

void C::OutB()
{
	printf("Out B\n");
}

int main()
{
	C obj;
	obj.OutA();
	obj.OutB();
	
	A* ap = (A*)&obj;
	B* bp = (B*)&obj;

	ap->OutA();
	bp->OutB();

	system("pause");

	// Return
	return 0;
}