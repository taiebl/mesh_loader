
/*
 * renderer.h
 *
 *  Created on: Dec 18, 2017
 *      Author: taieb
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#pragma once

#include "../inc/plyReader.h"
#include <string>


class Renderer
{
public:
	Renderer();
	Renderer(int argc, char **argv);
	~Renderer();

	bool render( int argc, char **argv, const ply::PLYReader& model, const char* windowTitle );
	void loop();
private:
	class impl;
	impl* p_impl;
};

#endif
