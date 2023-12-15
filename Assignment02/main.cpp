/* MYcube.c */

#include <stdlib.h>
#ifdef __APPLE_
#include <GLUT/glut.h>
#else
#include <GLUT/glut.h>
#endif

typedef float vertex[3];

/* initial MYcube */
vertex vertices[]={
         {-.5,  -.5, .5}, //0
           {-.5,   .5, .5}, //1
           { .5,   .5, .5}, //2
           { .5,  -.5, .5}, //3
         {-.5, -.5, -.5}, //4
           {-.5,  .5, -.5}, //5
           { .5,  .5, -.5}, //6
         { .5, -.5, -.5}  //7
          };

static GLfloat theta[] = {0.0,0.0,0.0};

/* display one polygon using a line loop for wire frame, a single
normal for constant shading, or three normals for interpolative shading */
void face( int a, int b, int c, int d)
{
    glBegin(GL_POLYGON);
       glNormal3fv(vertices[a]);

       glVertex3fv(vertices[a]);
       glVertex3fv(vertices[b]);
       glVertex3fv(vertices[c]);
     glVertex3fv(vertices[d]);
    glEnd();
}

void MYcube()
{
   /*  Front of MYcube counter clockwise front facing face*/
    glColor3f(1.0,0.0,0.0);       //red
    face(0, 3, 2, 1);

    /*  Back of MYcube  clockwise back facing face*/
    glColor3f(0.0,1.0,0.0);      //green
    face(4, 5, 6, 7);

    /*  Top of MYcube counter clockwise front facing face*/
    glColor3f(0.0,0.75388,1.0);      //blue
    face(1, 2, 6, 5);

    /*  Bottom of MYcube clockwise back facing face*/
    glColor3f(1.0,0.2,0.7);      //deep pink
    face(3, 0, 4, 7);

    /*  Right Side of MYcube counter clockwise front facing face*/
    glColor3f(1.0,1.0,0.0);      // yellow
    face(2, 3, 7, 6);

    /*  Left Side of MYcube clockwise back facing face*/
    glColor3f(1.0,0.75,0.0);      // orange
    face(5, 4, 0, 1);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
    MYcube();
    glFlush();
}


void myReshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // for orthographic projection, as long as the object is inside the viewing box,
     // it does NOT MATTER how long the viewing box is by varying the near and far
    if (w <= h)
        glOrtho(-2.0, 2.0, -2.0 * (GLfloat) h / (GLfloat) w,
            2.0 * (GLfloat) h / (GLfloat) w, -10.0, 10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
    glutPostRedisplay();
}

int  main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("MYcube");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
    glEnable(GL_DEPTH_TEST);
    glClearColor (1.0, 1.0, 1.0, 1.0);
    glutMainLoop();
}


