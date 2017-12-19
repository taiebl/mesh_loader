
#include "../inc/plyParser.h"


int main(int argc, char **argv)
{
	std::string plyFileName = "../data/part1_.ply";
	ply::PLYParser *parser = new ply::PLYParser(plyFileName);

	return 0;
}
