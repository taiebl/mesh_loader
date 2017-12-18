

#include "../inc/plyParser.h"

namespace ply
{
class plyParser::impl
{
public:
	void run()
	{

	}
};

plyParser::plyParser():
		pImpl{boost::make_unique<impl>()}
{
	pImpl->run();
}

plyParser::~plyParser() = default;

plyParser::plyParser(plyParser&&) = default;
plyParser& plyParser::operator=(plyParser&&) = default;
}
