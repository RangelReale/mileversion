#ifndef H__MILEVERSION_MILEVERSIONIMPL_LINUX__H
#define H__MILEVERSION_MILEVERSIONIMPL_LINUX__H

#include <string>

namespace mileversion {

class mileversionimpl
{
public:
	mileversionimpl(const std::string &filename, const std::string &versionid);
	virtual ~mileversionimpl();

	bool haveInfo();
	const std::string &fileVersion();
private:
	std::string _filename;
	bool _haveinfo;
	std::string _fileversion;
};

};


#endif // H__MILEVERSION_MILEVERSIONIMPL_LINUX__H