#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>


class Star
{
public:
    void drawStar()
    {
        glPushMatrix();
            glColor3f(1.0, 1.0, 0.5);//(R,G,B)
            glBegin(GL_POLYGON);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(0.16, 0.1, 0.0);
				//glColor3f(0.902, 0.902, 0.980);
                glVertex3f(0.05, 0.1, 0.0);
                glVertex3f(0.0, 0.23, 0.0);
				//glColor3f(0.878, 1.000, 1.000);
                glVertex3f(-0.05, 0.1, 0.0);
				//glColor3f(0.941, 0.973, 1.000);
                glVertex3f(-0.16, 0.1, 0.0);
                glVertex3f(-0.06, 0.06, 0.0);
                glVertex3f(-0.11, -0.08, 0.0);
				//glColor3f(1.000, 1.000, 0.878);
                glVertex3f(0.0, 0.0, 0.0);
                glVertex3f(0.11, -0.08, 0.0);
                glVertex3f(0.06, 0.06, 0.0);
            glEnd();
        glPopMatrix();
    }
};
