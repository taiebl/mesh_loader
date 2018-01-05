

//C++ Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <vector>
#include <queue>

// OpenGL Graphics includes
#include <helper_gl.h>
#include <GL/freeglut.h>

/*#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>
#include <GL/glxext.h>*/

// CUDA Includes
#include <cuda_gl_interop.h>

// User Includes
#include "renderer.h"

#define MAX_EPSILON_ERROR 10.0f
#define THRESHOLD          0.30f
#define REFRESH_DELAY     10 //ms


////////////////////////////////////////////////////////////////////////////////
// constants
const unsigned int window_width  = 1024;
const unsigned int window_height = 1024;

const unsigned int mesh_width    = 256;
const unsigned int mesh_height   = 256;

// vbo variables
GLuint vbo;

std::vector<ply::Vertex> g_vertices;
std::vector<ply::Face> g_faces;

// mouse controls
int mouse_old_x, mouse_old_y;
int mouse_buttons = 0;
float rotate_x = 0.0, rotate_y = 0.0;
float translate_z = -3.0;

////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
bool render( int argc, char **argv, const ply::PLYReader& model );
bool renderVertices(std::vector<ply::Vertex>& vertices);
bool renderFaces(std::vector<ply::Face>& faces);
void cleanup();

// GL functionality
bool initGL(int *argc, char **argv);
void createVBO(GLuint *vbo);
void deleteVBO(GLuint *vbo);

// rendering callbacks
void display();
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);
void motion(int x, int y);
void reshape(int w, int h);
void timerEvent(int value);

class Renderer::impl
{
public:

	////////////////////////////////////////////////////////////////////////////////
	//! Initialize GL
	////////////////////////////////////////////////////////////////////////////////
	bool initGL(int *argc, char **argv, const char* windowTitle)
	{
	    //glutInit(argc, argv);
	    //glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	    glutInitWindowSize(window_width, window_height);
	    glutCreateWindow(windowTitle);

	    glutDisplayFunc(display);
	    glutKeyboardFunc(keyboard);
	    glutMotionFunc(motion);
	    glutReshapeFunc(reshape);
	    glutTimerFunc(REFRESH_DELAY, timerEvent,0);

	    // initialize necessary OpenGL extensions
	    if (! isGLVersionSupported(2,0))
	    {
	        fprintf(stderr, "ERROR: Support for necessary OpenGL extensions missing.");
	        fflush(stderr);
	        return (false);
	    }

	    // default initialization
	    glClearColor(0.0, 0.0, 0.0, 1.0);
	    glDisable(GL_DEPTH_TEST);

	    // viewport
	    glViewport(0, 0, window_width, window_height);

	    // projection
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(60.0, (GLfloat)window_width / (GLfloat)window_height, 0.1, 50.0);

	    return (true);
	}

private:

	std::vector<ply::Vertex> m_vertices;
};


////////////////////////////////////////////////////////////////////////////////
//Renderer Constructors
////////////////////////////////////////////////////////////////////////////////
Renderer::Renderer():
		p_impl(new impl)
{

}

Renderer::Renderer(int argc, char **argv):
		p_impl(new impl)
{
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
}

////////////////////////////////////////////////////////////////////////////////
//Renderer Destructor
////////////////////////////////////////////////////////////////////////////////
Renderer::~Renderer()
{
	delete(p_impl);
}

////////////////////////////////////////////////////////////////////////////////
//Main Rendering Function
////////////////////////////////////////////////////////////////////////////////
bool Renderer::render( int argc, char **argv, const ply::PLYReader& model, const char* windowTitle)
{

    // Initialize OpenGL context
    if ( false == p_impl->initGL(&argc, argv, windowTitle) )	//p_impl->init(&argc, argv, windowTitle) )
    {
        return (false);
    }

    //Read Vertices
    g_vertices = model.getVertices();
    g_faces = model.getFaces();

	// Register callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutCloseFunc(cleanup);

    // Start rendering mainloop
    //glutMainLoop();
}

void Renderer::loop()
{
    // Start rendering mainloop
    glutMainLoop();
}

////////////////////////////////////////////////////////////////////////////////
//! Initialize GL
////////////////////////////////////////////////////////////////////////////////
bool initGL(int *argc, char **argv)
{
    glutInit(argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(window_width, window_height);
    glutCreateWindow("3D Model Rendering");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);
    glutTimerFunc(REFRESH_DELAY, timerEvent,0);

    // initialize necessary OpenGL extensions
    if (! isGLVersionSupported(2,0))
    {
        fprintf(stderr, "ERROR: Support for necessary OpenGL extensions missing.");
        fflush(stderr);
        return (false);
    }

    // default initialization
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDisable(GL_DEPTH_TEST);

    // viewport
    glViewport(0, 0, window_width, window_height);

    // projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)window_width / (GLfloat)window_height, 0.1, 50.0);

    return (true);
}

////////////////////////////////////////////////////////////////////////////////
//Render Function
////////////////////////////////////////////////////////////////////////////////
bool render( int argc, char **argv, const ply::PLYReader& model )
{
    // Initialize OpenGL context
    if ( false == initGL(&argc, argv) )
    {
        return (false);
    }

	// Register callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutReshapeFunc(reshape);

#if defined (__APPLE__) || defined(MACOSX)
    atexit(cleanup);
#else
    glutCloseFunc(cleanup);
#endif

    // Create VBO
    //createVBO(&vbo);

    // Run the cuda part
    //runCuda(&cuda_vbo_resource);

    // Start rendering mainloop
    glutMainLoop();
}

////////////////////////////////////////////////////////////////////////////////
//Render Vertices Function
////////////////////////////////////////////////////////////////////////////////
bool renderVertices(std::vector<ply::Vertex>& vertices)
{
	glPointSize(5);
	glColor3f(1.f,1.f, 1.f);

	for(auto it = vertices.begin(); it != vertices.end(); ++it)
	{
		ply::Vertex vertex = *it;

		glBegin(GL_POINTS);
		glColor4f( vertex.color.r / 255.f, vertex.color.g / 255.f, vertex.color.b / 255.f, vertex.color.a / 255.f);
		glVertex3f( vertex.position.x, vertex.position.y, vertex.position.z );
		glEnd();
	}

	return (true);
}

////////////////////////////////////////////////////////////////////////////////
//Render Faces Function
////////////////////////////////////////////////////////////////////////////////
bool renderFaces(std::vector<ply::Face>& faces)
{
	glPointSize(5);
	glColor3f(1.f,1.f, 1.f);

	for(auto it = faces.begin(); it != faces.end(); ++it)
	{
		ply::Face face = *it;

		glBegin(GL_TRIANGLE_STRIP);
		//glColor4f( vertex.color.r / 255.f, vertex.color.g / 255.f, vertex.color.b / 255.f, vertex.color.a / 255.f);
		//glVertex3f( vertex.position.x, vertex.position.y, vertex.position.z );
		for(int i=0; i<3; ++i)
		{
			glVertex3f(g_vertices[face.vertexID[i]].position.x, g_vertices[face.vertexID[i]].position.y, g_vertices[face.vertexID[i]].position.z);
		}

		glEnd();
	}

	return (true);
}

////////////////////////////////////////////////////////////////////////////////
//! Create VBO
////////////////////////////////////////////////////////////////////////////////
void createVBO(GLuint *vbo)
{
    assert(vbo);

    // create buffer object
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);

    // initialize buffer object
    unsigned int size = mesh_width * mesh_height * 4 * sizeof(float);
    glBufferData(GL_ARRAY_BUFFER, size, 0, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // register this buffer object with CUDA
    //checkCudaErrors(cudaGraphicsGLRegisterBuffer(vbo_res, *vbo, vbo_res_flags));

    //SDK_CHECK_ERROR_GL();
}

////////////////////////////////////////////////////////////////////////////////
//! Delete VBO
////////////////////////////////////////////////////////////////////////////////
void deleteVBO(GLuint *vbo)
{

    // unregister this buffer object with CUDA
    //checkCudaErrors(cudaGraphicsUnregisterResource(vbo_res));

    glBindBuffer(1, *vbo);
    glDeleteBuffers(1, vbo);

    *vbo = 0;
}

////////////////////////////////////////////////////////////////////////////////
//! Display callback
////////////////////////////////////////////////////////////////////////////////
void display()
{
    //sdkStartTimer(&timer);

    // run CUDA kernel to generate vertex positions
    //runCuda(&cuda_vbo_resource);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set view matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, translate_z);
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    // render from the vbo
    /*glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(4, GL_FLOAT, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1.0, 0.0, 0.0);
    glDrawArrays(GL_POINTS, 0, mesh_width * mesh_height);
    glDisableClientState(GL_VERTEX_ARRAY);*/

    //Render Vertices
    //renderVertices(g_vertices);
    renderFaces(g_faces);

    glutSwapBuffers();

    //g_fAnim += 0.01f;

    //sdkStopTimer(&timer);
    //computeFPS();
}

////////////////////////////////////////////////////////////////////////////////
//! Display callback
////////////////////////////////////////////////////////////////////////////////
void display_1()
{
    std::cout<<"Rendering 1 .....\n";

    //sdkStartTimer(&timer);

    // run CUDA kernel to generate vertex positions
    //runCuda(&cuda_vbo_resource);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set view matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, translate_z);
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    // render from the vbo
    /*glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(4, GL_FLOAT, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1.0, 0.0, 0.0);
    glDrawArrays(GL_POINTS, 0, mesh_width * mesh_height);
    glDisableClientState(GL_VERTEX_ARRAY);*/

    //Render Vertices
    renderVertices(g_vertices);


    glutSwapBuffers();

    //g_fAnim += 0.01f;

    //sdkStopTimer(&timer);
    //computeFPS();
}

////////////////////////////////////////////////////////////////////////////////
//! Display callback
////////////////////////////////////////////////////////////////////////////////
void display_2()
{
	std::cout<<"Rendering 2 .....\n";

    //sdkStartTimer(&timer);

    // run CUDA kernel to generate vertex positions
    //runCuda(&cuda_vbo_resource);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // set view matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(0.0, 0.0, translate_z);
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    // render from the vbo
    /*glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(4, GL_FLOAT, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1.0, 0.0, 0.0);
    glDrawArrays(GL_POINTS, 0, mesh_width * mesh_height);
    glDisableClientState(GL_VERTEX_ARRAY);*/

    //Render Vertices
    renderVertices(g_vertices);

    glutSwapBuffers();

    //g_fAnim += 0.01f;

    //sdkStopTimer(&timer);
    //computeFPS();
}

////////////////////////////////////////////////////////////////////////////////
//! Keyboard events handler
////////////////////////////////////////////////////////////////////////////////
void keyboard(unsigned char key, int /*x*/, int /*y*/)
{
    switch (key)
    {
        case (27) :
            #if defined(__APPLE__) || defined(MACOSX)
                exit(EXIT_SUCCESS);
            #else
                glutDestroyWindow(glutGetWindow());
                return;
            #endif
    }
}

void timerEvent(int value)
{
    if (glutGetWindow())
    {
        glutPostRedisplay();
        glutTimerFunc(REFRESH_DELAY, timerEvent,0);
    }		//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(15, 0, 0);

	////glEnd();

	//glLineWidth(2.5);
	//glColor3f(1.0, 1.0, 1.0);
	////glBegin(GL_LINES);

	//glVertex3f(0.0, 0.0, 0.0);
	//glVertex3f(-1.0, 0, 0);

	//glEnd();
	//glutWireCube(10); // Draw a cube
}

void cleanup()
{
    //sdkDeleteTimer(&timer);

    if (vbo)
    {
        deleteVBO(&vbo);
    }
}

////////////////////////////////////////////////////////////////////////////////
//! Mouse event handlers
////////////////////////////////////////////////////////////////////////////////
void mouse(int button, int state, int x, int y)
{
    if (state == GLUT_DOWN)
    {
        mouse_buttons |= 1<<button;
    }
    else if (state == GLUT_UP)
    {
        mouse_buttons = 0;
    }

    mouse_old_x = x;
    mouse_old_y = y;
}

void motion(int x, int y)
{
    float dx, dy;
    dx = (float)(x - mouse_old_x);
    dy = (float)(y - mouse_old_y);

    if (mouse_buttons & 1)
    {
        rotate_x += dy * 0.2f;
        rotate_y += dx * 0.2f;
    }
    else if (mouse_buttons & 4)
    {
        translate_z += dy * 0.01f;
    }

    mouse_old_x = x;
    mouse_old_y = y;
}

////////////////////////////////////////////////////////////////////////////////
// Window Resizer
////////////////////////////////////////////////////////////////////////////////
// This is called when the window has been resized.
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
}
