
/*
 * renderer.h
 *
 *  Created on: Dec 18, 2017
 *      Author: taieb
 */

#ifndef RENDERER_H_
#define RENDERER_H_

#pragma once

#include"../inc/plyReader.h"

bool render( int argc, char **argv, const ply::PLYReader& model );
bool renderVertices();
void cleanup();


#endif
