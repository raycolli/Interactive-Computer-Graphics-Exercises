//Collier, Rachel
/* basicshapes.c  This program draws a white rectangle on a black background. */

#include <GLUT/glut.h>         /* glut.h includes gl.h and glu.h*/

void drawScene(void)
{
     glClear(GL_COLOR_BUFFER_BIT);
    
    //Triangle
    glBegin(GL_TRIANGLES); //Begin triangle coordinates
        glVertex2f(0.25, 0);
        glVertex2f(0.75, 0);
        glVertex2f(0.5, 0.5);
    glEnd(); //End triangle coordinates

    //Trapezoid
    glBegin(GL_QUADS); //Begin quadrilateral coordinates
        glVertex2f(-0.75, -0.75);
        glVertex2f(-0.25, -0.75);
        glVertex2f(-0.33, -0.25);
        glVertex2f(-0.67, -0.25);
    glEnd(); //End quadrilateral coordinates

     glFlush();
}

int main(int argc, char** argv)
{
     glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500,500);
    glutInitWindowPosition(0,0);
    glutCreateWindow("basic shapes");
    glutDisplayFunc(drawScene);
    glutMainLoop();
}

