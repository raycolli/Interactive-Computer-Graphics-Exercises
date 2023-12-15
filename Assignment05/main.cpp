#include <stdlib.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


    GLfloat vertices[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
    {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
    {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

    GLfloat normals[][3] = {{-1.0,-1.0,-1.0},{1.0,-1.0,-1.0},
    {1.0,1.0,-1.0}, {-1.0,1.0,-1.0}, {-1.0,-1.0,1.0},
    {1.0,-1.0,1.0}, {1.0,1.0,1.0}, {-1.0,1.0,1.0}};

    void polygon(int a, int b, int c , int d)
{
    glBegin(GL_POLYGON);
         
        glNormal3fv(normals[a]);
        glVertex3fv(vertices[a]);
        
        glNormal3fv(normals[b]);
        glVertex3fv(vertices[b]);
         
        glNormal3fv(normals[c]);
        glVertex3fv(vertices[c]);
         
        glNormal3fv(normals[d]);
        glVertex3fv(vertices[d]);
    glEnd();
                                                                                                        }

void colorcube()
{
    /*  Front of MYcube counter clockwise front facing face*/
    glColor3f(1.0,0.0,0.0);       //red
    polygon(0,3,2,1);

    /*  Back of MYcube  clockwise back facing face*/
    glColor3f(0.0,1.0,0.0);      //green
    polygon(4,5,6,7);

    /*  Bottom of MYcube clockwise back facing face*/
    glColor3f(1.0,0.2,0.7);      //deep pink
    polygon(3,0,4,7);

    /*  Top of MYcube counter clockwise front facing face*/
    glColor3f(0.0,0.75388,1.0);      //blue
    polygon(1,2,6,5);
    
    /*  Right Side of MYcube counter clockwise front facing face*/
    glColor3f(1.0,1.0,0.0);      // yellow
    polygon(2,3,7,6);
     
    /*  Left Side of MYcube clockwise back facing face*/
    glColor3f(1.0,0.75,0.0);      // orange
    polygon(5,4,0,1);
}

static GLfloat theta[] = {0.0,0.0,0.0};
static GLint axis = 2;
static GLdouble viewer[]= {0.0, 0.0, 5.0}; /* initial viewer location */

void display(void)
{

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/* Update viewer position in modelview matrix */

    glLoadIdentity();
    gluLookAt(viewer[0],viewer[1],viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

/* rotate cube */

    glRotatef(theta[0], 1.0, 0.0, 0.0);
    glRotatef(theta[1], 0.0, 1.0, 0.0);
    glRotatef(theta[2], 0.0, 0.0, 1.0);

 colorcube();

 glFlush();
    glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{
    if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN) axis = 0;
    if(btn==GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) axis = 1;
    if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN) axis = 2;
    theta[axis] += 2.0;
    if( theta[axis] > 360.0 ) theta[axis] -= 360.0;
    display();
}

void keys(unsigned char key, int x, int y)
{

/* Use x, X, y, Y, z, and Z keys to move viewer */

   if(key == 'x') viewer[0]-= 1.0;
   if(key == 'X') viewer[0]+= 1.0;
   if(key == 'y') viewer[1]-= 1.0;
   if(key == 'Y') viewer[1]+= 1.0;
   if(key == 'z') viewer[2]-= 1.0;
   if(key == 'Z') viewer[2]+= 1.0;
   display();
}

void myReshape(int w, int h)
{
 glViewport(0, 0, w, h);

/* Use a perspective view */

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
    if(w<=h) glFrustum(-2.0, 2.0, -2.0 * (GLfloat) h/ (GLfloat) w,
       2.0* (GLfloat) h / (GLfloat) w, 2.0, 20.0);
    else glFrustum(-2.0, 2.0, -2.0 * (GLfloat) w/ (GLfloat) h,
       2.0* (GLfloat) w / (GLfloat) h, 2.0, 20.0);

/* Or we can use gluPerspective */

 /* gluPerspective(45.0, w/h, -10.0, 10.0); */

 glMatrixMode(GL_MODELVIEW);
}

int
main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
 glutInitWindowSize(500, 500);
 glutCreateWindow("ViewingCube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keys);
 glEnable(GL_DEPTH_TEST);
 glutMainLoop();
}


