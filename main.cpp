#include "Pin.h"
#include "PinType.h"

#include <iostream>

using namespace gpio;

int main(int argc, char** argv) {
	Pin pin_1(1);
	Pin pin_2(2);

	std::cout << "pin_1.index: " << (int)pin_1.GetIndex() << std::endl;
	std::cout << "pin_2.index: " << (int)pin_2.GetIndex() << std::endl;

	PinType read = PinType::INPUT;

	std::cout << "Read pin type: " << (int)read << std::endl;

	return 0;
}
