/*
 * plyParser.h
 *
 *  Created on: Dec 18, 2017
 *      Author: taieb
 */

#ifndef PLYPARSER_H_
#define PLYPARSER_H_

#pragma once

#include <memory>
#include <string>

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
	Point3 position;
	RGBAColor color;

}Vertex;


//.PLY file Parser
class PLYParser
{
	//Methods
public:
	PLYParser();
	~PLYParser();

	PLYParser(PLYParser&&);
	PLYParser& operator=(PLYParser&&);

	PLYParser(std::string fileName);

private:


	//Attributes
private:
	class impl;
	//std::unique_ptr<impl> p_impl;
	impl *p_impl;
};
}



#endif /* PLYPARSER_H_ */
