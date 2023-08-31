#include <iostream>
#include "impl.h"

int main(int argc, char *argv[]) {
	Widget w;
	w.increase();
	Widget w2;
	w2 = std::move(w);
	// std::cout << w.num() << "\n";
	std::cout << w2.num() << "\n";
	

	return 0;
}