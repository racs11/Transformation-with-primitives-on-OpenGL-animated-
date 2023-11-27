/*
Raul Antonio Castillejos Santillan
Transformation on primitives Showcase
    "q" <- to change animation
    "c" <- to quit

*/
#include <GL/glut.h>
#include <time.h>
#include <iostream>
#include <math.h>

bool flag = true;
void timer(int);


//Window Size
int windowX = 400;
int windowY = 500;

int transformDisp = 0;

float theta = 0 * (M_PI / 180);

//Values for transformations
float Escala = 0.1;
float translate = 0;
float shearValX = 0;
float shearValY = 0;

using namespace std;

void triangleScale(void){

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0, 0);
  glBegin(GL_POLYGON);
  //Scaling triangle through time
  glVertex2i(200*Escala + ((windowX/2)*(1-Escala)),125*Escala + ((windowY/2)*(1-Escala)));
  glVertex2i(100*Escala + ((windowX/2)*(1-Escala)),375*Escala + ((windowY/2)*(1-Escala)));
  glVertex2i(300*Escala + ((windowX/2)*(1-Escala)),375*Escala + ((windowY/2)*(1-Escala)));
  glEnd();

}
void Translation(void){
  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0, 0);
  glBegin(GL_POLYGON);
  //translating Square primitive
  //do clockwise!!!
  glVertex2f(0 + translate,300);
  glVertex2f(50 + translate,300);
  glVertex2f(50 + translate,250);
  glVertex2f(0 + translate,250);

  glEnd();
}
void RotationPivot(void){

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0, 0);
  glBegin(GL_POLYGON);
  //rotating through pivot point primitive
  glVertex2f(windowX/2 + (200-(windowX/2)) * cos(theta) - (200 -windowY/2) * sin(theta), windowY/2 + (200-(windowX/2))* sin(theta) + (200 -windowY/2) * cos(theta));
  glVertex2f(windowX/2 + (100-(windowX/2)) * cos(theta) - (375 -windowY/2) * sin(theta), windowY/2 + (100-(windowX/2))* sin(theta) + (375 -windowY/2) * cos(theta));
  glVertex2f(windowX/2 + (300-(windowX/2)) * cos(theta) - (375 -windowY/2) * sin(theta), windowY/2 + (300-(windowX/2))* sin(theta) + (375 -windowY/2) * cos(theta));
  glEnd();

}

void shearX(void){

  glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0, 0);
  glBegin(GL_POLYGON);
  //shearing on primitive square
  //do clockwise!!!
  glVertex2f(windowX/2 +shearValX,windowY/2+50);
  glVertex2f(windowX/2+50 + shearValX,windowY/2+50);
  glVertex2f(windowX/2+50 ,windowY/2);
  glVertex2f(windowX/2,windowY/2);

  glEnd();

}
void shearY(void){

    glClear(GL_COLOR_BUFFER_BIT);
  glColor3f(1.0, 0, 0);
  glBegin(GL_POLYGON);
  //shearing on primitive square
  //do clockwise!!!
  glVertex2f(windowX/2 ,windowY/2+50);
  glVertex2f(windowX/2+50,windowY/2+50 -shearValY);
  glVertex2f(windowX/2+50 ,windowY/2 -shearValY);
  glVertex2f(windowX/2,windowY/2 );

  glEnd();

}

void reflection(void){


    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0,1.0,0);

    //horizontal middle line
    glBegin(GL_LINES);
    glVertex2f(0 ,windowY/2);
    glVertex2f(windowX ,windowY/2);
    glEnd();

    //vertical middle line
    glBegin(GL_LINES);
    glVertex2f(windowX/2 ,0);
    glVertex2f(windowX/2 ,windowY);
    glEnd();

    //normal triangle primitive
    glColor3f(1.0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2i(300, 375);
    glVertex2i(250, 475);
    glVertex2i(350, 475);
    glEnd();

    //Reflected triangle with reflection point on the middle of the screen

    int xc = 200;
    int yc = 250;

    glColor3f(1.0, 0, 0);
    glBegin(GL_POLYGON);

    glVertex2i(2*xc - 300, 2*yc - 375);
    glVertex2i(2*xc - 250, 2*yc - 475);
    glVertex2i(2*xc - 350, 2*yc - 475);
    glEnd();

}

void displayCB(void){

     //changing states and printing current state

    if(transformDisp == 0){
        cout<<"Scaling"<<endl;
        triangleScale();
    }else if(transformDisp == 1){
        cout<<"Translating"<<endl;
        Translation();
    }else if(transformDisp == 2){
        cout<<"Rotating"<<endl;
        RotationPivot();
    }else if(transformDisp == 3){
        cout<<"Shearing on X"<<endl;
        shearX();
    }else if(transformDisp == 4){
        cout<<"Shearing on Y"<<endl;
        shearY();
    }else if(transformDisp == 5){
        cout<<"Reflecting"<<endl;
        reflection();
    }
    else{
        transformDisp = 0;
    }
  glutSwapBuffers();
}

void keyCB(unsigned char key, int x, int y)	/* called on key press */
{
  //detecting inputs
  if( key == 'q' ){
    transformDisp++;
  }
  if( key == 'c'){
    exit(0);
  }
}

void mouseFunc (GLint button, GLint action, GLint xMouse, GLint yMouse)
{
    //detecting mouse input
    if (button == GLUT_LEFT_BUTTON && action == GLUT_DOWN){
        shearValY = yMouse - windowY/2;
        shearValX = xMouse - windowX/2;
    }


}


int main(int argc, char *argv[])
{
  int win;

  glutInit(&argc, argv);

  //Display setup
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(windowX,windowY);
  win = glutCreateWindow("Transformations with primitives");

  glClearColor(0.0,0.0,0.0,0.0);
  gluOrtho2D(0,400,0,500);

  //set functions
  glutDisplayFunc(displayCB);
  glutTimerFunc(1000, timer,0);
  glutKeyboardFunc(keyCB);
  glutMouseFunc (mouseFunc);
  glutMainLoop();

  return 0;
}
void timer (int){

    //runs 60 times per second (60 fps)

    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0);
    if(Escala < 1){
        Escala += 0.01;
    }else{
        Escala = 0.1;
    }

    if(translate < 500){
        translate += 5;
    }else{
        translate = -100;
    }
    if(theta < 2*M_PI){
        theta += 1 * (M_PI / 180);
    }else{
        theta = 0;
    }

}
