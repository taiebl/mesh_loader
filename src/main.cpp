
#include "../inc/plyParser.h"


int main(int argc, char **argv)
{
	std::string plyFileName = "/home/taieb/workspace/applications/colmap/projects/distributed_lionHanau/part1/part1_.ply";
	ply::PLYParser *parser = new ply::PLYParser(plyFileName);

	return 0;
}
