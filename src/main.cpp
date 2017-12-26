
#include "../inc/plyReader.h"
#include "../rendering/renderer.h"

int main(int argc, char **argv)
{

	std::string plyFileName = "../data/part1_.ply";

	//Load the 3D Model
	ply::PLYReader myModel = ply::PLYReader(plyFileName);

	//Render the 3D Model
	render(argc, argv, myModel);


	return 0;
}
