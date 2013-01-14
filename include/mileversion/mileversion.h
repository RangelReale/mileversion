#ifndef H__MILEVERSION__H
#define H__MILEVERSION__H

#include <string>

namespace mileversion {

class mileversionimpl;

class mileversion
{
public:
	mileversion(const std::string &filename, const std::string &versionid);
	virtual ~mileversion();

	bool haveInfo();
	const std::string &fileVersion();
private:
	mileversionimpl *_pImpl;
};

};


#endif // H__MILEVERSION__H