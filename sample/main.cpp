#include <mileversion/mileversion.h>

#include <iostream>

static char *mileversion_app = "3.0.4.0";

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