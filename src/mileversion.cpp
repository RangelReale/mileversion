#include "mileversion/mileversion.h"
#include "mileversion/exceptions.h"
#include "mileversion/mileversionimpl.h"

namespace mileversion {

mileversion::mileversion(const std::string &filename, const std::string &versionid) : 
	_pImpl(new mileversionimpl(filename, versionid))
{

}

mileversion::~mileversion()
{
	if (_pImpl) delete _pImpl;
}

bool mileversion::haveInfo()
{
	return _pImpl->haveInfo();
}

const std::string &mileversion::fileVersion()
{
	return _pImpl->fileVersion();
}


};
