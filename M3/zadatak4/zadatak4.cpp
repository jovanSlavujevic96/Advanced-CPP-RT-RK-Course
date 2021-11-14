#include <iostream>

#include<memory>
#include "MyUniquePtr.h"

using std::cout;

static MyUniquePtr<int> a(new int);


//#define myUP std::unique_ptr
#define myUP MyUniquePtr


struct MojaKlasa {
	MojaKlasa(int a, int b, int c) : x(a), y(b), z(c) {}
	int x, y, z;
};


void foo(const MojaKlasa& x) {
	cout << x.x;
}

void bar(const MojaKlasa* x) {
	cout << x->y;
}

myUP<MojaKlasa> makeObjectUP()
{
	//return std::make_unique<myClass>();
	return myUP<MojaKlasa>(new MojaKlasa(1, 2, 3));
}


int main()
{
	myUP<MojaKlasa> p;
	p = makeObjectUP();
	foo(*p);
	bar(p.get());
	cout << p->z << std::endl; // NAPOMENA: ovo uradite poslednje, slobodno konsultujte literaturu, tj. Internet

	// GRESKE: ovo da se onemoguci
	//myUP<MojaKlasa> q{p};
	//myUP<MojaKlasa> r;
	//r = q;

	// @TODO: iz destruktora ispisati pozdrav na ekran

	std::cin.get();
	return 0;
}
