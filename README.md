mileversion
===========

A multi-platform C++ library for executable file version reading .

```cpp
#include <mileversion/mileversion.h>

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
```

Windows
-------
On Windows, the library reads the VS_FIXEDFILEINFO from the target file.

You must ensure that the file contains it, for example using an .rc file in your source project.

Linux
-----
Linux binaries don't have embedded version info like Windows, so a workaround needed to be found.

mileversion reads the binary file using 'libelf' and tries to find a variable with a name in this format:

```cpp
mileversion_versioninfo_XX_XX_XX_XX
```

the version info will be the 4 numbers embedded in the variable name.

The macro "MILEVERSION_DECLARE_VERSION(MH, ML, NH, NL)" can be used to declare a variable with the correct name.

Note that the binary file will depend on libelf to run.


Author
------
Rangel Reale
