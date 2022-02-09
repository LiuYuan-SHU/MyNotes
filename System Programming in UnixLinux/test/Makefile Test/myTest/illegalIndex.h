#ifndef ILLEGAL_INDEX_H
#define ILLEGAL_INDEX_H

#include<exception>
#include<cstring>
#include <string>

class illegalIndex : public std::exception
{
private:
	std::string errorInfo;
public:
	illegalIndex(int index)
	{
		std::string errorInfo1 = "-----ILLEGAL INDEX " + index;
		std::string errorInfo2 = " -----\n";
		std::string errorInfo3 = __func__ + '\n' + '\n';
		errorInfo = errorInfo1 + errorInfo2 + errorInfo3;
	}

	const char* what();
};
#endif

