/*
 * plyReader.h
 *
 *  Created on: Dec 18, 2017
 *      Author: taieb
 */

#ifndef PLYREADER_H_
#define PLYREADER_H_

#pragma once

#include <memory>
#include <string>
#include <vector>

namespace ply
{

typedef struct
{
	float x;
	float y;
	float z;
}Point3;

typedef struct
{
	int r;
	int g;
	int b;
}RGBColor;

typedef struct
{
	int r;
	int g;
	int b;
	int a;
}RGBAColor;


typedef struct
{
	int id;
	Point3 position;
	RGBAColor color;

}Vertex;

typedef struct
{
	int id;
	int vertexID[3];
}Face;

//.PLY file Parser
class PLYReader
{
	//Methods
public:
	PLYReader();
	~PLYReader();

	PLYReader(PLYReader&&);
	PLYReader& operator=(PLYReader&&);

	PLYReader(std::string fileName);

	std::vector<Vertex> getVertices() const;
	std::vector<Face> getFaces() const;

private:


	//Attributes
private:
	class impl;
	//std::unique_ptr<impl> p_impl;
	impl *p_impl;
};
}



#endif /* PLYPARSER_H_ */
