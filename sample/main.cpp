#include <mileversion/mileversion.h>

#include <iostream>

MILEVERSION_DECLARE_VERSION(3, 0, 4, 0)

int main(int argc, char* argv[])
{
	mileversion::mileversion version(argv[0]);

	if (version.haveInfo())
	{
		std::cout << "File version: " << version.fileVersion() << std::endl;
	}
	else
		std::cout << "No version info detected" << std::endl;


	return 0;
}