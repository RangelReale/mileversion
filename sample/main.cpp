#include <mileversion/mileversion.h>

#include <iostream>

int main(int argc, char* argv[])
{
	mileversion::mileversion version(argv[0], "mileversion_app");

	if (version.haveInfo())
	{
		std::cout << "File version: " << version.fileVersion() << std::endl;
	}
	else
		std::cout << "No version info detected" << std::endl;


	return 0;
}