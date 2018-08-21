#include <bits/stdc++.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <windows.h>
#include <mmsystem.h>


#include "ball.h"
#include "NightSky.h"
#include "menu.h"
#include "gameOver.h"
#include "PauseScreen.h"
#include "square.h"
#include "star.h"


using  namespace std;
static int score;
static int life= 7;
float _angle = 0.0;
float px = 7.0;
//float _cameraAngle = 0.0;
float _ang_tri = 0.0;
float posx = 0;
float posy =-2.20;
float dposx1=-2.0,dposx2=0,dposx3=1.5;
float dposy1=2.9,dposy2=8,dposy3=5.5;//= 2.9;

float cposx1 = -2, cposx2 = 2, cposx3 = 0; //added this
float cposy1 = 4, cposy2 = 2, cposy3 = 0;  //added this

float z = 5, y=2.5;

float dLifeposx1=0.0;
float dLifeposy1=50.0;
bool playgame=false;
bool gameover = false;
bool gamemenu = true;
bool pause= false;
char line[10]="Point";


Ball ball;
NightSky nightSky;
Menu menu;
GameOverScreen gameOverScreen;
PauseScreen pauseScreen;
Square square;
Star star;


void displayRasterText(float x ,float y ,float z ,char *stringToDisplay) {
	int length;
	glRasterPos3f(x, y, z);
		length = strlen(stringToDisplay);

	for(int i=0 ;i<length ;i++){
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24 ,stringToDisplay[i]);
	}
}

//added comets
float RandomComet(float min, float max)
{
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}

void comet1()
{
     cposx1 = RandomComet(-2,6);
     cposy1 = RandomComet(-2,4);
}

void comet2()
{
     cposx1 = RandomComet(-4,4);
     cposy1 = RandomComet(-2,6);
}

void comet3()
{
     cposx1 = RandomComet(-1,6);
     cposy1 = RandomComet(-4,4);
}


float RandomFloat(float min, float max)
{
    float r = (float)rand() / (float)RAND_MAX;
    return min + r * (max - min);
}
void genX1Y1()
{
     dposx1 = RandomFloat(-2.0,-1.5);
     dposy1 = RandomFloat(2.5,2.9);
}
void genX2Y2()
{
    dposx2 = RandomFloat(-1,2.0);
    dposy2 = RandomFloat(4.0,5.0);
}
void genX3Y3()
{
    dposx3 = RandomFloat(1.2,2.2);
    dposy3 = RandomFloat(6.0,7.0);
}

void genLifeX1Y1()
{
    dLifeposx1 = RandomFloat(-1.2,2.2);
    dLifeposy1 = RandomFloat(5.0,6.0);
}
//Initializes 3D rendering
void initRendering() {
	glEnable(GL_DEPTH_TEST);
}
void handleResize(int w, int h) {
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}
//Draws the 3D scene
void drawScene() {
	glClearColor(0.0, 0.0, 0.1, 1.0); //added this
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW); //Switch to the drawing perspective
	glLoadIdentity(); //Reset the drawing perspective
	//glRotatef(-_cameraAngle, 0.0, 1.0, 0.0); //Rotate the camera
	glTranslatef(0.0, 0.0, -7.0);//Move forward 7 unit
    glColor3f(1,1,1);
    nightSky.displaySky();

    if(gameover){
        ofstream myfile;
        myfile.open ("score.txt");
        myfile << score;
        myfile.close();
        ifstream scorefromfile("score.txt");
        string myscore;
        getline(scorefromfile, myscore);
        const char *ch = myscore.c_str();

        scorefromfile.close();
        glColor3f(1.0,0.0, 0.0);
        gameOverScreen.drawGameOverScreen();
        glColor3f(0.5,0.2, 0.8);
        gameOverScreen.drawText("Your Score is:  ", 16, -0.33, 0.2);
        glColor3f(1.0,1.0, 1.0);
        gameOverScreen.drawText(ch, 2, 0.15, 0.2);
        gameOverScreen.drawText("Restart? Press R", 16, -0.33, -0.40);
        nightSky.x=-3.0;
        nightSky.y=-0.5;
        nightSky.cloudx1=-1.5;
        nightSky.cloudx2=6;
    }

    if(pause){
        pauseScreen.drawText("GAME  PAUSED !!", 16, -0.33, 0.2);
    }

    if(gamemenu)
        menu.createMenu();

    if(playgame){
            //added this comet
            glPushMatrix();
                glTranslatef(cposx1, cposy1, 0.0);
                    ball.drawComet();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(cposx2, cposy2, 0.0);
                    ball.drawComet();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(cposx3, cposy3, 0.0);
                    ball.drawComet();
            glPopMatrix();

            //red ring
            glColor3f(0,1,0);
            glPushMatrix(); //Save the current state of transformations
            glTranslatef(posx, posy, 0.0);
            glRotatef(55, 1.0, 0.0, 0.0);
            glutWireTorus(0.03,0.4,20,30);
            glPopMatrix();

            //falling objects
            glPushMatrix(); //Save the current state of transformations
            glTranslatef(dposx1, dposy1, 0.0);
                ball.drawBall();
            glPopMatrix();

            //glColor3f(1.0,1,0);
            glPushMatrix(); //Save the current state of transformations
            glTranslatef(dposx2, dposy2, 0.0);
                star.drawStar();
            glPopMatrix();

            //glColor3f(1.0,1,0);
            glPushMatrix(); //Save the current state of transformations
            glTranslatef(dposx3, dposy3, 0.0);
                ball.drawBall();
            glPopMatrix();


            glPushMatrix(); //Save the current state of transformations
            glTranslatef(dLifeposx1, dLifeposy1, 0.0);
                //ball.drawBall();
                square.drawSquare();

            glColor3f(1,1,1);
            glutWireTorus(.01,.16,30,20);
            glPopMatrix();

            char temp[40];
            glPushMatrix();
            sprintf(temp,"SCORE : %d",score);
            displayRasterText(-2.3 ,2.5,0,temp);
            glPopMatrix();


            char temp1[40];
            glPushMatrix();
            sprintf(temp1,"LIFE : %d",life);
            displayRasterText(1.5,2.5,0,temp1);
            glPopMatrix();
    }
    glutSwapBuffers();

}

void Keyboard(unsigned char key, int x, int y){
    if(key=='d'  || key=='D'){
        if(posx<1.8){
            posx+=.5;
        }
    }
    if(key=='a' || key=='A'){
        if(posx>=-1.8){
            posx-=.5;
        }
    }
    if(key=='q'|| key=='Q')
        exit(0);
    if(key=='R'|| key=='r'){
        life= 7;
        score = 0;
        genX1Y1();
        genX2Y2();
        genX3Y3();
        genLifeX1Y1();
        //menu.createMenu();
        gameover= false;
        playgame = true;
    }
    if(key=='p'|| key=='P'){
        if(playgame){
            playgame = false;
            pause = true;
        }
        else{
             playgame =true;
             pause= false;
        }
    }
}
void SpecialInput(int key, int x, int y){
    if(key == GLUT_KEY_RIGHT){
        if(posx<1.8){
            posx+=.5;
        }
    }
    if(key == GLUT_KEY_LEFT ){
        if(posx>=-1.8){
            posx-=.5;
        }
    }
}


void update(int value) {
if(playgame){
        //cout<<"SCORE : "<<score<<"   HP : "<<life<<endl;

         float posPosx,negPosx;
         posPosx = posx+.4;
         negPosx = posx-.4;

        if((dposx1>=negPosx && dposx1<= posPosx )&& (dposy1<=-2.2 && dposy1>-2.23) ){
                //cout<<"COLLISSION DETECTED :D dpos 1"<<endl;
                score++;
                genX1Y1();
                PlaySound("sound.wav", NULL, SND_ASYNC|SND_FILENAME);

        }
        else if(dposy1<=-2.2 && dposy1>-2.23)
        {
                //cout<<"one life gone :D dpos 1  "<<endl;
            life--;
            if(life<=0){
                    playgame = false;
                    gameover = true;
                    PlaySound("dead.wav", NULL, SND_ASYNC|SND_FILENAME);
            }
        }
        if((dposx2>=negPosx && dposx2<= posPosx )&& (dposy2<=-2.2 && dposy2>-2.23) ){
                //cout<<"COLLISSION DETECTED :D dpos2"<<endl;
                score++;
                life++;
                genX2Y2();
                PlaySound("sound.wav", NULL, SND_ASYNC|SND_FILENAME);

        }
        else if(dposy2<=-2.2 && dposy2>-2.23)
        {
                //cout<<"one life gone :D dpos 2 "<<endl;
                life-=2;
                if(life<=0){
                    playgame = false;
                    gameover = true;
                    PlaySound("dead.wav", NULL, SND_ASYNC|SND_FILENAME);
                }
        }
        if((dposx3>=negPosx && dposx3<= posPosx )&& (dposy3<=-2.2 && dposy3>-2.23) ){
                //cout<<"COLLISSION DETECTED :D dpos 3"<<endl;
                score++;
                genX3Y3();
                PlaySound("sound.wav", NULL, SND_ASYNC|SND_FILENAME);

        }
        else if(dposy3<=-2.2 && dposy3>-2.23){
                //cout<<"one life gone :D  dpos 3 "<<endl;
                life--;
                if(life<=0){
                    playgame = false;
                    gameover = true;
                    PlaySound("dead.wav", NULL, SND_ASYNC|SND_FILENAME);
                }

        }



        if((dLifeposx1>=negPosx && dLifeposx1<= posPosx )&& (dLifeposy1<=-2.2 && dLifeposy1>-2.23) ){
                //cout<<"COLLISSION DETECTED :D dpos 3"<<endl;
                score++;
                life+=3;
                genLifeX1Y1();
                PlaySound("sound.wav", NULL, SND_ASYNC|SND_FILENAME);
        }

        //added this
        if(cposx1<-3 || cposy1<-4){
            comet1();
        }
        if(cposx1<-5 || cposy1<-4){
            comet1();
        }
        if(cposx1<-2 || cposy1<-6){
            comet1();
        }
        cposx1-=0.05;
        cposy1-=0.05;
        cposx2-=0.05;
        cposy2-=0.05;
        cposx3-=0.05;
        cposy3-=0.05;

        if(dposy1< -5.5){
             genX1Y1();
        }
        if(dposy2<-5.5){
             genX2Y2();
        }
        if(dposy3<-5.5){
             genX3Y3();
        }
        if(dLifeposy1<-5.5){
             genLifeX1Y1();
        }
        dposy1-=.03;
        dposy2-=.03;
        dposy3-=.03;
        dLifeposy1-=.03;

        if(nightSky.x >3.1 && nightSky.y>3.61){
                nightSky.x=-3.5;
                nightSky.y=-0.5;
        }
        if(nightSky.cloudx1>3.5){
                nightSky.cloudx1=-1.5;
        }
        if(nightSky.cloudx2<-1.5){
                nightSky.cloudx2=6;
        }

        nightSky.cloudx1+=0.004;
        nightSky.cloudx2-=0.005;
        nightSky.x+=0.006;
        nightSky.y+=0.001;
    }
        if(y>=-0.6)
            y-=0.05;
        if(z>=0.15)
            z-=0.05;

    ball.BallUpdate();
	glutPostRedisplay();
	glutTimerFunc(13, update, 0);
}

void mouseClick(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        //cout<<(double)x<< "  "<<(double)y<<endl;
        if(x >= 245 && x <=340 && y >=245 && y <=273)
            exit(0);
        else if(x >= 245 && x <=340 && y >=205 && y <=235){
            gamemenu = false;
            playgame= true;
        }

    }
}


int main(int argc, char** argv) {
	//Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	//glutInitWindowSize(800, 600);
	//glutInitWindowPosition(500,100);

	glutInitWindowSize(600, 700);
    glutInitWindowPosition(500,00);

	//Create the window
	glutCreateWindow("Project Final");

	initRendering();

	//Set handler functions
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);
	glutTimerFunc(15, update, 0); //Add a timer
	glutSpecialFunc(SpecialInput); // for arrow keys
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(mouseClick);
    //init();

	glutMainLoop();


	return 0;
}

