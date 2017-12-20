

#include "../inc/plyReader.h"

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

enum DATA
{
	VERTEX_POSITION,
	VERTEX_COLOR,
	FACE
};

class PLYReader::impl
{
public:


	//========================================================================================
	//Main processing to parse a .PLY file
	//========================================================================================
	void run()
	{
		m_plyFile.open(m_fileName);

		//Read Header
		readHeader();

		//Read Vertices
		readVertices();

		//Read Faces
		readFaces();

		m_plyFile.close();
	}

	//========================================================================================
	//Display Data
	//========================================================================================
	void displayData(DATA data)
	{
		switch (data)
		{
		case VERTEX_POSITION:
			displayVerticesPos();
			break;
		case VERTEX_COLOR:
			displayVerticesColor();
			break;
		case FACE:
			displayFaceVertices();
			break;
		}
	}

private:

	//========================================================================================
	//Read Header
	//========================================================================================
	void readHeader()
	{
		std::string line = "";
		std::vector<std::string> items;
		Vertex vertex;

		bool readVertexEnabled = false;
		bool readFaceEnabled = false;

		m_nbrVertexProps = 0;
		m_nbrVertices = 0;

		while(line.compare("end_header") != 0)
		{
			std::getline(m_plyFile, line);
			items = split(line, ' ');

			if(items[0].compare("element") == 0)
			{
				if(items[1].compare("vertex") == 0)
				{
					m_nbrVertices = std::atof(items[2].c_str());
					readVertexEnabled = true;
				}
				else if(items[1].compare("face") == 0)
				{
					m_nbrFaces = std::atof(items[2].c_str());
					readFaceEnabled = true;
					readVertexEnabled = false;
				}
			}

			if( readVertexEnabled && items[0].compare("property") == 0 )
			{
				m_nbrVertexProps++;
			}
		}
	}

	//========================================================================================
	//Read Vertices
	//========================================================================================
	void readVertices()
	{
		std::string line = "";
		std::vector<std::string> items;
		Vertex vertex;

		int numVertex = 0;

		for(int i=0; i<m_nbrVertices; ++i)
		{
			std::getline(m_plyFile, line);
			items = split(line, ' ');

			if(items.size() == m_nbrVertexProps)
			{
				vertex.id = numVertex++;
				vertex.position.x = std::atof(items[0].c_str());
				vertex.position.y = std::atof(items[1].c_str());
				vertex.position.z = std::atof(items[2].c_str());

				vertex.color.r = std::atof(items[3].c_str());
				vertex.color.g = std::atof(items[4].c_str());
				vertex.color.b = std::atof(items[5].c_str());
				vertex.color.a = std::atof(items[6].c_str());

				m_vertices.push_back(vertex);
			}
		}
	}

	//========================================================================================
	//Read Faces
	//========================================================================================
	void readFaces()
	{
		std::string line = "";
		std::vector<std::string> items;
		Face face;

		int numFaces = 0;

		for(int i=0; i<m_nbrFaces; ++i)
		{
			std::getline(m_plyFile, line);
			items = split(line, ' ');

			face.id = numFaces++;
			face.vertexID[0] = std::atof(items[0].c_str());
			face.vertexID[1] = std::atof(items[1].c_str());
			face.vertexID[2] = std::atof(items[2].c_str());

			m_faces.push_back(face);
		}
	}

	//========================================================================================
	//Display Vertices Position
	//========================================================================================
	void displayVerticesPos()
	{
		std::for_each(m_vertices.begin(), m_vertices.end(), [](const Vertex& v) { std::cout << v.id << ":" << v.position.x << ":" << v.position.y << ":" << v.position.z << std::endl; });
	}

	//========================================================================================
	//Display Vertices Color
	//========================================================================================
	void displayVerticesColor()
	{
		std::for_each(m_vertices.begin(), m_vertices.end(), [](const Vertex& v) { std::cout << v.id << ":" << v.color.r << ":" << v.color.g << ":" << v.color.b << std::endl; });
	}

	//========================================================================================
	//Display Face Vertices
	//========================================================================================
	void displayFaceVertices()
	{
		std::for_each(m_faces.begin(), m_faces.end(), [](const Face& f) { std::cout << f.id << ":" << f.vertexID[0] << ":" << f.vertexID[1] << ":" << f.vertexID[2] << std::endl; });
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


	//Attributes
public:
	std::string m_fileName;
	std::ifstream m_plyFile;

	int m_nbrVertices;
	int m_nbrVertexProps;
	int m_nbrFaces;

	std::vector<Vertex> m_vertices;
	std::vector<Face> m_faces;

};



PLYReader::PLYReader()
{
	//p_impl = boost::make_unique<impl>();
	p_impl = new impl;

}


PLYReader::~PLYReader() = default;

PLYReader::PLYReader(PLYReader&&) = default;
PLYReader& PLYReader::operator=(PLYReader&&) = default;

PLYReader::PLYReader(std::string fileName)
{
	//p_impl = std::make_unique<impl>();
	p_impl = new impl;
	p_impl->m_fileName = fileName;
	p_impl->run();
	p_impl->displayData(FACE);
}

}
