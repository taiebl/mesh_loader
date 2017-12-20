

//C++ Includes
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <assert.h>

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
const unsigned int window_width  = 512;
const unsigned int window_height = 512;

const unsigned int mesh_width    = 256;
const unsigned int mesh_height   = 256;

// vbo variables
GLuint vbo;

// mouse controls
int mouse_old_x, mouse_old_y;
int mouse_buttons = 0;
float rotate_x = 0.0, rotate_y = 0.0;
float translate_z = -3.0;

////////////////////////////////////////////////////////////////////////////////
// Forward Declarations
bool render(int argc, char **argv);
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
void timerEvent(int value);


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
    glutTimerFunc(REFRESH_DELAY, timerEvent,0);

    // initialize necessary OpenGL extensions
    if (! isGLVersionSupported(2,0))
    {
        fprintf(stderr, "ERROR: Support for necessary OpenGL extensions missing.");
        fflush(stderr);
        return false;
    }

    // default initialization
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glDisable(GL_DEPTH_TEST);

    // viewport
    glViewport(0, 0, window_width, window_height);

    // projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat)window_width / (GLfloat) window_height, 0.1, 10.0);

    return true;
}

////////////////////////////////////////////////////////////////////////////////
//Render Function
////////////////////////////////////////////////////////////////////////////////
bool render(int argc, char **argv)
{

    // Initialize OpenGL context
    if ( false == initGL(&argc, argv) )
    {
        return false;
    }

	// Register callbacks
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
#if defined (__APPLE__) || defined(MACOSX)
    atexit(cleanup);
#else
    glutCloseFunc(cleanup);
#endif

    // Create VBO
    createVBO(&vbo);

    // Run the cuda part
    //runCuda(&cuda_vbo_resource);

    // Start rendering mainloop
    glutMainLoop();
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
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0.0, 0.0, translate_z);
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 1.0, 0.0);

    // render from the vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexPointer(4, GL_FLOAT, 0, 0);

    glEnableClientState(GL_VERTEX_ARRAY);
    glColor3f(1.0, 0.0, 0.0);
    glDrawArrays(GL_POINTS, 0, mesh_width * mesh_height);
    glDisableClientState(GL_VERTEX_ARRAY);

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
    }
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
