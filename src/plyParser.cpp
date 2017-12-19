

#include "../inc/plyParser.h"

//STL
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

//Boost
#include <boost/make_unique.hpp>


namespace ply
{


class PLYParser::impl
{
public:


	//========================================================================================
	//Main processing to parse a .PLY file
	//========================================================================================
	void run()
	{
		std::string line = "";
		std::vector<std::string> items;
		Vertex vertex;

		bool recordVertex = false;
		//while()
		for(int i=0; i<10000; ++i)
		{
			std::getline(m_plyFile, line);

			if(line.compare("end_header") == 0)
			{
				recordVertex = true;
				continue;
			}

			if(recordVertex)
			{
				//std::cout<<line<<std::endl;
				items = split(line, ' ');
				vertex.position.x = std::atof(items[0].c_str());
				vertex.position.y = std::atof(items[1].c_str());
				vertex.position.z = std::atof(items[2].c_str());

				vertex.color.r = std::atof(items[3].c_str());
				vertex.color.g = std::atof(items[4].c_str());
				vertex.color.b = std::atof(items[5].c_str());
				vertex.color.a = std::atof(items[5].c_str());

				m_vertices.push_back(vertex);
			}
		}

		m_plyFile.close();
	}

	//========================================================================================
	//Split string according to a delimiter
	//========================================================================================
	std::vector<std::string> split(const std::string &iString, char iDelimiter)
	{
		std::stringstream ss(iString);
		std::string item = "";
		std::vector<std::string> items;

		while(std::getline(ss, item, iDelimiter))
		{
			items.push_back(item);
		}

		return items;
	}


	//========================================================================================
	//Display Vertices Positions
	//========================================================================================
	void displayVerticesPos()
	{
		std::for_each(m_vertices.begin(), m_vertices.end(), [](const Vertex& v) { std::cout << v.position.x << ":" << v.position.y << ":" << v.position.z << std::endl; });
	}

	//========================================================================================
	//Display Vertices Positions
	//========================================================================================
	void displayVerticesColor()
	{
		std::for_each(m_vertices.begin(), m_vertices.end(), [](const Vertex& v) { std::cout << v.color.r << ":" << v.color.g << ":" << v.color.b << std::endl; });
	}


	//Attributes
public:
	std::ifstream m_plyFile;
	std::vector<Vertex> m_vertices;


};



PLYParser::PLYParser()
{
	//p_impl = boost::make_unique<impl>();
	p_impl = new impl;

}


PLYParser::~PLYParser() = default;

PLYParser::PLYParser(PLYParser&&) = default;
PLYParser& PLYParser::operator=(PLYParser&&) = default;

PLYParser::PLYParser(std::string fileName)
{
	//p_impl = std::make_unique<impl>();
	p_impl = new impl;
	p_impl->m_plyFile.open(fileName);
	p_impl->run();
	p_impl->displayVerticesPos();
}

}
