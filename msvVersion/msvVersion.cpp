// msvVersion.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>


int main()
{

	std::cout << "Current MSC version is: " << _MSC_VER << std::endl;
	std::cout << "Current *** version is: " << _MSC_FULL_VER << std::endl;
	std::cin.get();
    return 0;
}

