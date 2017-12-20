
#include "../inc/plyReader.h"
#include "../rendering/renderer.h"

int main(int argc, char **argv)
{
	std::string plyFileName = "../data/part1_.ply";
	ply::PLYReader *parser = new ply::PLYReader(plyFileName);

	render(argc, argv);
	return 0;
}
