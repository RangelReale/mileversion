#ifndef H__MILEVERSION__H
#define H__MILEVERSION__H

#include <string>

#define MILEVERSION_VERSION_STR		"mileversion_versioninfo_"

#define MILEVERSION_DECLARE_VERSION(MH, ML, NH, NL) \
	char mileversion_versioninfo_##MH##_##ML##_##NH##_##NL[] = "mv";

namespace mileversion {

class mileversionimpl;

class mileversion
{
public:
	mileversion(const std::string &filename);
	virtual ~mileversion();

	bool haveInfo();
	const std::string &fileVersion();
private:
	mileversionimpl *_pImpl;
};

};


#endif // H__MILEVERSION__H