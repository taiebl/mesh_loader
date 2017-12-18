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
#include <boost/make_unique.hpp>

namespace ply
{
class plyParser
{

	//Methods
public:
	plyParser();
	~plyParser();

	plyParser(plyParser&&);
	plyParser& operator=(plyParser&&);

private:


	//Attributes
private:
	class impl;
	std::unique_ptr<impl> pImpl;

};
}



#endif /* PLYPARSER_H_ */
