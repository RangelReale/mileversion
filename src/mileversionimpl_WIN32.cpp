#include "mileversion/mileversionimpl_WIN32.h"
#include "mileversion/exceptions.h"

#include <windows.h>

namespace mileversion {

mileversionimpl::mileversionimpl(const std::string &filename, const std::string &versionid) : 
	_filename(filename), _haveinfo(false)
{
	VS_FIXEDFILEINFO *fileinfo;
	DWORD dummy;
	DWORD infoSize = GetFileVersionInfoSize(filename.c_str(), &dummy);
	if (infoSize > 0)
	{
		LPCSTR *buffer = new LPCSTR[infoSize];

		if (GetFileVersionInfo(filename.c_str(), dummy, infoSize, buffer))
		{
			LPVOID ptr;
			UINT len;

			if (VerQueryValue(buffer, "\\", &ptr, &len))
			{
				_haveinfo = true;
				fileinfo = (VS_FIXEDFILEINFO *)ptr;

				char vinfo[50];
				sprintf(vinfo, "%d.%d.%d.%d", 
					HIWORD(fileinfo->dwFileVersionMS), LOWORD(fileinfo->dwFileVersionMS),
					HIWORD(fileinfo->dwFileVersionLS), LOWORD(fileinfo->dwFileVersionLS));

				_fileversion = vinfo;
			}
		}

		delete [] buffer;
	}
}

mileversionimpl::~mileversionimpl()
{

}

bool mileversionimpl::haveInfo()
{
	return _haveinfo;
}

const std::string &mileversionimpl::fileVersion()
{
	return _fileversion;
}

};
