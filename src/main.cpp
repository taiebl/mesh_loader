
#include "../inc/plyReader.h"
#include "../rendering/renderer.h"

#define NBR_MODELS	(2)

int main(int argc, char **argv)
{

	std::string plyFileName[] = {"../data/part1_.ply", "../data/part2_.ply"};
	const char* window[] = {"Model_1", "Model_2"};
	ply::PLYReader plyModel[NBR_MODELS];

	//Load 3D Models
	for(int i=0; i<NBR_MODELS; ++i)
	{
		plyModel[i] = ply::PLYReader(plyFileName[i]);
	}

	//Render 3D Models
	Renderer renderer = Renderer(argc, argv);
	for(int i=0; i<NBR_MODELS; ++i)
	{
		renderer.render(argc, argv, plyModel[i].getVertices(), window[i]);
	}

	renderer.loop();

	return (0);
}
