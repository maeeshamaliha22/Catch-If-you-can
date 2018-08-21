#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

class Square
{
public:
    void drawSquare()
    {
        glPushMatrix();
            glColor3f(1, 1, 1);
            glPointSize(5);
            glBegin(GL_POLYGON);
                glVertex2i(100, 50);
                glVertex2i(100, 130);
                glVertex2i(150, 130);
                glVertex2i(150, 50);
            glEnd();
        glPopMatrix();
        glFlush ();
    }
};

