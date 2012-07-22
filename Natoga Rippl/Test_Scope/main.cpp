/************************************************************************/
/* Class scope theory                                                   */
/************************************************************************/

#include <iostream>

class A
{
public:
	A(int p, int pr){prot = p; priv = pr;}

	void Fu(A* obj)
	{
		printf("Prot: %u\nPriv %u\n\n", obj->prot, obj->priv);
	}
protected:
	int prot;
private:
	int priv;
};

int main()
{
	A foo(5, 6);
	A bar(7, 8);

	foo.Fu(&bar);

	system("pause");
	return 0;
}