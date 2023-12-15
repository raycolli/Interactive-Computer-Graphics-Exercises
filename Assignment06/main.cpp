// Rachel Collier
// Homework 6

/* ShadedCube.c created from trackball.c */
/* Shading the rotating cube*/

#include <math.h>
#include <stdlib.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif

GLfloat light0_pos[4] = {0.90, 0.90, 2.25, 0.0};

typedef struct materialStruct {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular[4];
    GLfloat shininess;
    } materialStruct;

typedef struct lightingStruct {
    GLfloat ambient[4];
    GLfloat diffuse[4];
    GLfloat specular [4];
    } lightingStruct;


materialStruct colorCubeMaterials = {
    {0.2, 0.2, 0.2, 1.0},
    {0.8, 0.8, 0.8, 1.0},
    {0.0, 0.0, 0.0, 1.0},
    1.0
    };

materialStruct brassMaterials = {
    {0.33, 0.22, 0.03, 1.0},
    {0.78, 0.57, 0.11, 1.0},
    {0.99, 0.91, 0.81, 1.0},
    27.8
    };

materialStruct redPlasticMaterials = {
    {0.3, 0.0, 0.0, 1.0},
    {0.6, 0.0, 0.0, 1.0},
    {0.8, 0.6, 0.6, 1.0},
    32.0
    };

materialStruct whiteShinyMaterials = {
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    100.0
    };

lightingStruct whiteLighting = {
    {0.0, 0.0, 0.0, 1.0},
    {1.0, 1.0, 1.0, 1.0},
    {1.0, 1.0, 1.0, 1.0}
    };

lightingStruct coloredLighting = {
    {0.2, 0.0, 0.0, 1.0},
    {0.0, 1.0, 0.0, 1.0},
    {0.0, 0.0, 1.0, 1.0}
    };


materialStruct *currentMaterials;
lightingStruct *currentLighting;

#define bool int
#define false 0
#define true 1

#ifndef M_PI
#define M_PI 3.14159
#endif


int     winWidth, winHeight;

float     angle = 0.0, axis[3], trans[3];
bool     trackingMouse = false;
bool     redrawContinue = false;
bool    trackballMove = false;

/*----------------------------------------------------------------------*/
/*
** Draw the cube.
*/
GLfloat vertices[][3] = {
    {-1.0,-1.0,-1.0},{1.0,-1.0,-1.0}, {1.0,1.0,-1.0}, {-1.0,1.0,-1.0},
    {-1.0,-1.0,1.0}, {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}
};

GLfloat colors[][3] = {
    {0.0,0.0,0.0},{1.0,0.0,0.0}, {1.0,1.0,0.0}, {0.0,1.0,0.0},
    {0.0,0.0,1.0}, {1.0,0.0,1.0}, {1.0,1.0,1.0}, {0.0,1.0,1.0}
};

GLfloat normals[][3] = {{0.0,0.0,-1.0},{0.0,1.0,0.0},
    {-1.0,0.0,0.0}, {1.0,0.0,0.0}, {0.0,0.0,1.0},
    {0.0,-1.0,0.0}};


//void polygon(int a, int b, int c , int d, int face)
//{
//
//    /* draw a polygon via list of vertices */
//
//    glBegin(GL_POLYGON);
//      glColor3fv(colors[a]);
//      glVertex3fv(vertices[a]);
//      glColor3fv(colors[b]);
//      glVertex3fv(vertices[b]);
//      glColor3fv(colors[c]);
//      glVertex3fv(vertices[c]);
//      glColor3fv(colors[d]);
//      glVertex3fv(vertices[d]);
//    glEnd();
//}
//
//void colorcube(void)
//{
//
//    /* map vertices to faces */
//
//    polygon(1,0,3,2,0);
//    polygon(3,7,6,2,1);
//    polygon(7,3,0,4,2);
//    polygon(2,6,5,1,3);
//    polygon(4,5,6,7,4);
//    polygon(5,4,0,1,5);
//}

void polygon(int a, int b, int c , int d)
{

/* draw a polygon via list of vertices */

     glBegin(GL_POLYGON);
        glVertex3fv(vertices[a]);
        glVertex3fv(vertices[b]);
        glVertex3fv(vertices[c]);
        glVertex3fv(vertices[d]);
    glEnd();
                                                                                                        }

void colorcube(void)
{

/* map vertices to faces */

    glNormal3fv(normals[0]);
    polygon(0,3,2,1);
    glNormal3fv(normals[1]);
    polygon(2,3,7,6);
    glNormal3fv(normals[2]);
    polygon(0,4,7,3);
    glNormal3fv(normals[3]);
    polygon(1,2,6,5);
    glNormal3fv(normals[4]);
    polygon(4,5,6,7);
    glNormal3fv(normals[5]);
    polygon(0,1,5,4);
}


/*----------------------------------------------------------------------*/
/*
** These functions implement a simple trackball-like motion control.
*/

float lastPos[3] = {0.0F, 0.0F, 0.0F};
int curx, cury;
int startX, startY;

void
trackball_ptov(int x, int y, int width, int height, float v[3])
{
    float d, a;

    /* project x,y onto a hemi-sphere centered within width, height */
    v[0] = (2.0F*x - width) / width;
    v[1] = (height - 2.0F*y) / height;
    d = (float) sqrt(v[0]*v[0] + v[1]*v[1]);
    v[2] = (float) cos((M_PI/2.0F) * ((d < 1.0F) ? d : 1.0F));
    a = 1.0F / (float) sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    v[0] *= a;
    v[1] *= a;
    v[2] *= a;
}


void
mouseMotion(int x, int y)
{
    float curPos[3], dx, dy, dz;

    trackball_ptov(x, y, winWidth, winHeight, curPos);
if(trackingMouse)
{
    dx = curPos[0] - lastPos[0];
    dy = curPos[1] - lastPos[1];
    dz = curPos[2] - lastPos[2];

    if (dx || dy || dz) {
    angle = 90.0F * sqrt(dx*dx + dy*dy + dz*dz);

    axis[0] = lastPos[1]*curPos[2] - lastPos[2]*curPos[1];
    axis[1] = lastPos[2]*curPos[0] - lastPos[0]*curPos[2];
    axis[2] = lastPos[0]*curPos[1] - lastPos[1]*curPos[0];

    lastPos[0] = curPos[0];
    lastPos[1] = curPos[1];
    lastPos[2] = curPos[2];
    }
}
    glutPostRedisplay();
}

void
startMotion(int x, int y)
{

    trackingMouse = true;
    redrawContinue = false;
    startX = x; startY = y;
    curx = x; cury = y;
    trackball_ptov(x, y, winWidth, winHeight, lastPos);
    trackballMove=true;
}

void
stopMotion(int x, int y)
{

    trackingMouse = false;

    if (startX != x || startY != y) {
    redrawContinue = true;
    } else {
    angle = 0.0F;
    redrawContinue = false;
    trackballMove = false;
    }
}

/*----------------------------------------------------------------------*/

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    /* view transform */

    if (trackballMove) {
        glRotatef(angle, axis[0], axis[1], axis[2]);

    }
    colorcube();

    glutSwapBuffers();
}

/*----------------------------------------------------------------------*/

void mouseButton(int button, int state, int x, int y)
{
    if(button==GLUT_RIGHT_BUTTON) exit(0);
    if(button==GLUT_LEFT_BUTTON) switch(state)
    {
    case GLUT_DOWN:
    y=winHeight-y;
    startMotion( x,y);
    break;
    case GLUT_UP:
    stopMotion( x,y);
    break;
    }
}

void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    winWidth = w;
    winHeight = h;
}

void spinCube()
{
    if (redrawContinue) glutPostRedisplay();
}

void key(unsigned char k, int x, int y)
{
    switch(k)
    {
        case '1':
            glutIdleFunc(NULL);
            break;
        case '2':
            glutIdleFunc(spinCube);
            break;
        case '3':
            currentMaterials = &redPlasticMaterials;
            break;
        case '4':
            currentMaterials = &colorCubeMaterials;
            break;
        case '5':
            currentMaterials = &brassMaterials;
            break;
        case '6':
            currentLighting = &whiteLighting;
            break;
        case '7':
            currentLighting = &coloredLighting;
            break;
        case 'q':
            exit(0);
            break;
    }
    glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
    glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);

    glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);

        glutPostRedisplay();
}

void init()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    currentMaterials = &redPlasticMaterials;

    glMaterialfv(GL_FRONT, GL_AMBIENT, currentMaterials->ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, currentMaterials->diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, currentMaterials->specular);
    glMaterialf(GL_FRONT, GL_SHININESS, currentMaterials->shininess);

    currentLighting = &whiteLighting;

    glLightfv(GL_LIGHT0, GL_AMBIENT, currentLighting->ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, currentLighting->diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, currentLighting->specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
}


int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Shaded Cube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(spinCube);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    init();
    glutMainLoop();
}




