#ifndef H__MILEVERSION_EXCEPTIONS__H
#define H__MILEVERSION_EXCEPTIONS__H

#include <stdexcept>
#include <string>

namespace muleversion {

class Exception : public std::exception
{
public:
	Exception() : std::exception() {}
	Exception(const std::string &message) : std::exception(), _message(message) {}
	~Exception() throw() {}
	
	const char* what() const throw() { return _message.c_str(); }
private:
	std::string _message;
};

};


#endif // H__MILEVERSION_EXCEPTIONS__H