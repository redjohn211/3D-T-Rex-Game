
//Computer graphics Final Project
// Ashim Neupane and Muhammad Talal Khan


#include <windows.h>
#include <iostream>
#include <math.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "glut.h"
#include <fstream>
#include <iostream>
#include <vector>
bool teaPot = false;

using std::vector; 
using namespace std;
bool jump = false;
bool cntrl = true; 
bool start = false;
bool ambientB = true;
bool positional1B = true;
bool positional2B = false;
bool directionalB = false;
bool filled = true;
#define PERPECTIVE_PROJECTION 1
#define PARALLEL_PROJECTION   2
#define NEAR_INITIAL    1.0
#define FAR_INITIAL    3.5
#define SHIFT_EYE_INCREMENT 0.1
#define NEAR_INCREMENT      0.1 
#define GAME_SPEED 0.01;
float speed = 0.05;
GLint polygons[100][100];
vector<int> num;
#define AXIS_LENGTH   0.2
# define pi = 3.14159
int num1;
int axis = 1;
int grid =1;
int projection = PERPECTIVE_PROJECTION;
float angle1 = 0;
float eyeX = 0;
float eyeY = 0;
float eyeZ = 2;
float nearClip = NEAR_INITIAL;
float farClip = FAR_INITIAL;
float rho = sqrt(eyeX*eyeX+eyeY*eyeY+eyeZ*eyeZ);
float theta = 1.6;
float phi = 0.8;
float temp = 0;
int width, height;  // display window width & height
int numPolygon;
int individual = 0;
int Switch = 0;
int minP;
int neupane = 0;
int khan = 0;
float xx=0;
float yy=0;
float zz=0;
float xView,yView,zView = 0;
float camX = 2.960313;
float camY = 0.229504;
float camZ = 0.299504;
int state = 0; 
int directon = 0; 
int randomNumber;
float sped = 10;
bool gameOver = false;
vector<float> obstacleX;
vector<float> obstacleY;
vector<float> obstacleZ;
vector<float> obstacle;
vector<float> dinoX;
vector<float> dinoY;
vector<float> dinoZ;
void jumpCheck();


float copper[13] = {  0.2295f, 0.08825f, 0.0275f, 1.0f,				/* ambient */
	0.5508f, 0.2118f, 0.066f, 1.0f,									/* diffuse */
	0.580594f, 0.223257f, 0.0695701f, 1.0f,							/* specular */
	50.0															/* shininess */
};


float turquoise[13] = { 0.1f, 0.18725f, 0.1745f, 0.8f,					
						0.396f, 0.74151f, 0.69102f, 0.8f,
						0.297254f, 0.30829f, 0.306678f, 0.8f,
						50.8f 
};

float green[13] = {0.0, 0.05, 0.0, 1.0, 0.4, 0.5, 0.4, 1.0, 0.04, 0.7, 0.04, 1.0, 50.0};

///////////////////////////

bool lightOn = true;
bool lightOn1 = true;
bool lightOn2 = true;
float globalAmbient = 0;
int quadrant = 1;
float lightX = 0.0, lightY = 1.0, lightZ = 1.0; 
float lightDiffuse = 3.0;
bool smoothShade = true;
vector<float> verticesLst;
vector<float> normalsLst;	


void generateObstacle();
void drawObstacle();
void placeObstacle();
void myInit(void)
{
	glClearColor (0.76, 0.698, 0.5019, 0.0);

	float vv1;
	float n1; 
	ifstream inData("normals.txt");	
	if(!inData){cout << "File1 Not Found" << endl;}
	while (!inData.eof()){
		inData >> vv1; 
		normalsLst.push_back(vv1);
	}
	inData.close();

	ifstream inData2("verts.txt");	
	if(!inData2){cout << "File Not Found" << endl;}
	while (!inData2.eof()){
		inData2 >> n1; 
		verticesLst.push_back(n1);
	}

	inData.close();
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	
}

void drawFloorGrid(void){
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, turquoise);
	for(double x = -0.5; x< -0.25; x+=0.25){
		glBegin(GL_POLYGON);
		glVertex3f(width*10,0,x);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-width*10,0,x);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-width*10,0,x-0.5);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(width*10,0,x-0.5);
		glNormal3f(0.0, 1.0, 0.0);
		glEnd();
	}
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, green);
	for(double x = 0.00; x< 0.25; x+=0.25){
		glBegin(GL_POLYGON);
		glVertex3f(width*10,0,x);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-width*10,0,x);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-width*10,0,x-0.5);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(width*10,0,x-0.5);
		glNormal3f(0.0, 1.0, 0.0);
		glEnd();
	}

	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, turquoise);
	for(double x = 0.5; x< 0.75; x+=0.25){
		glBegin(GL_POLYGON);
		glVertex3f(width*10,0,x);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-width*10,0,x);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(-width*10,0,x-0.5);
		glNormal3f(0.0, 1.0, 0.0);
		glVertex3f(width*10,0,x-0.5);
		glEnd();
	}
}

void drawDino1(void){
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, copper);
	glPushMatrix();
	jumpCheck();
	glTranslatef(xx,0.14,-0.25+zz);
glScalef(0.05,0.05,0.05);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	for (int i = 0; i != 8928; i += 3){
		glBegin(GL_TRIANGLE_FAN);
		glNormal3f(teapot_normals[i], teapot_normals[i+1], teapot_normals[i+2]);
		glVertex3f(teapot_vertex_points[i], teapot_vertex_points[i+1], teapot_vertex_points[i+2]);
	}
	glEnd();
	glPopMatrix();


}
void placeObstacle(){
	for(int x = 0;x<2000;x+=1){
		
		glPushMatrix();
		if(x%3 == 0)
			glTranslatef(0,0,0.5);
		if(x%3 == 1)
			glTranslatef(0,0,-0.5);
		glTranslatef(-x,0,0);
		drawObstacle();
		glPopMatrix();
	}
}
void drawObstacle(){
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, copper);
	glPushMatrix();
	glScalef(0.1,1,0.3);
	glTranslatef(-0.7,0.1,-0.8);
	glutSolidCube(0.15);
	glPopMatrix();
}

void drawDino(){
	glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, copper);
	glPushMatrix();
	jumpCheck();
	glTranslatef(xx,0.14,-0.25+zz);
	glScalef(0.001,0.001,0.001);
	glRotatef(-90.0, 0.0, 1.0, 0.0);
	for (int i = 0; i != verticesLst.size(); i += 3){
		glBegin(GL_TRIANGLE_FAN);
		glNormal3f(normalsLst[i], normalsLst[i+1], normalsLst[i+2]);
		glVertex3f(verticesLst[i], verticesLst[i+1], verticesLst[i+2]);
	}
	glEnd();
	glPopMatrix();

}

void setLighting(void) 
{
	const GLfloat DIRECTIONAL = 0.0;
	GLfloat lmodel_ambient[] = { globalAmbient, globalAmbient, globalAmbient, 1.0 }; 
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, lmodel_ambient );
//////////////////////////////////////////////////////////////////////////////////////
	GLfloat light_position[] = { lightX, lightY, lightZ, DIRECTIONAL };  
	GLfloat light_ambient[] = { 0.5, 0.5, 0.5, 1.0 };
	GLfloat light_diffuse[] = { lightDiffuse, lightDiffuse, lightDiffuse, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
//////////////////////////////////////////////////////////////////////////////////////

	GLfloat light1_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light1_diffuse[] = { 0.0, 5.0, 0.0, 1.0 };
	GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light1_position[] = { lightX+xx, lightY, lightZ, 1.0 };  
	GLfloat spot_direction1[] = { 0.0, -1.0, -1.0 };

	glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);

	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20.0);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_direction1);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 1.0);
	glEnable(GL_LIGHT1);

//////////////////////////////////////////////////////////////////////////////////////

	GLfloat light2_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light2_diffuse[] = { 0.0, 0.0, 100.0, 1.0 };
	GLfloat light2_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light2_position[] = { lightX+xx+0.2, lightY, lightZ, 1.0 };  
	GLfloat spot_direction2[] = { -1.0, -1.0, -1.0 };

	glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
	glLightfv(GL_LIGHT2, GL_POSITION, light2_position);

	glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 20.0);
	glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, spot_direction2);
	glLightf(GL_LIGHT2, GL_SPOT_EXPONENT, 1.0);
	glEnable(GL_LIGHT2);

//////////////////////////////////////////////////////////////////////////////////////

	if (directionalB){
		glEnable(GL_LIGHT0);}
	else
		glDisable(GL_LIGHT0);

	if (positional1B){
		glEnable(GL_LIGHT1);}
	else
		glDisable(GL_LIGHT1);
	if (positional2B){
		glEnable(GL_LIGHT2);}
	else
		glDisable(GL_LIGHT2);
}

void jumpCheck(){
	//1 is jump , 2 is fall , 0 is none
	if(state == 1){
		//Beep(523,200);
		yy+=0.005;
		glTranslatef(0,yy,0);
		
		if(yy>0.3){
			state = 2;
		}
	}
	else if(state == 2){
		yy-=0.005;
		
		glTranslatef(0,yy,0);
		if(yy <0.005){
			state = 0;
		}
	}
}
void collisonCheck(void){
	float dinoX = xx*-1;
	float dinoY = yy;
	if(dinoX >1.95+3*khan && dinoX<2.2+3*khan && dinoY<=0.15 && zz >-0.00001 && zz<0.00001){
		cout<<"Game over" << endl;
		cout << "Score: " << int(xx*-1) << endl;
		speed = 0;
		gameOver = true;
	}
	if(dinoX >0.95+3*khan && dinoX<1.2+3*khan && dinoY<=0.15 && zz < -0.1){
		cout<<"Game over" << endl;
		cout << "Score: " << int(xx*-1) << endl;
		speed = 0;
		gameOver = true;
	}
	if(dinoX >2.95+3*khan && dinoX<3.2+3*khan && dinoY<=0.15 && zz > 0.1){
		cout<<"Game over" << endl;
		cout << "Score: " << int(xx*-1) << endl;

		speed = 0;
		gameOver = true;
	}
	
}
void print(string a,float x,float y,float z){
	
  glColor3f( 0, 0, 0 );
  glRasterPos3f(x, y,z);
  int len, i;
  //len = (int)strlen(a);
  for (i = 0; i < a.size(); i++) {
    glutBitmapCharacter(GLUT_BITMAP_8_BY_13, a[i]);
  }
	
}
void myDisplay(void)
{
	if(filled)
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();   
	//setLighting();
	if(!start)
		gluLookAt ((rho)*sin(theta)*sin(phi)+xx, rho*cos(phi), rho*cos(theta)*sin(phi), xx, 0.0, 0.0, 0.0, 1.0, 0.0);
	else
	gluLookAt ((rho)*sin(theta)*sin(phi)+xx, rho*cos(phi), rho*cos(theta)*sin(phi), xx, 0.0, 0.0, 0.0, 1.0, 0.0);
	if(ambientB == true)
		globalAmbient = 1.0;
	else
		globalAmbient = 0;
	

	int x = (int)(xx*-1);
	//std::string gui = std::to_string(42);
	string z = "GAME OVER";
	string y = "Your score is";

	if(gameOver == true){
	print(z,xx,0.35,0.8);
	//print(y,xx,0.7,0.8);
	//print(x,xx,0.6,0.8);
	}
	placeObstacle();
	string a = "Press s to start";
	string b = "Controls:";
	string c = "Jump: w";
	string d = "Right: d";
	string e = "Left: a";
	
	glEnable( GL_NORMALIZE );
	if(!start && !teaPot){
  print(a,0,0.35,0.8);
	print(b,0,0.7,0.8);
	print(c,0,0.65,0.8);
	print(d,0,0.6,0.8);
	print(e,0,0.55,0.8);
	glPushMatrix();
	glScalef(2,2,2);
	glTranslatef(0,0,0.2);
	drawDino();
	glPopMatrix();
	}
	if(teaPot && !start){
		glPopMatrix();
	drawDino1();

	}
	glPushMatrix();
	if(teaPot && start){
		glScalef(0.1,0.1,0.1);
		drawDino1();
	}
	if(start && !teaPot)
	drawDino();
	collisonCheck();
	setLighting();
	glPopMatrix();
	drawFloorGrid();
	jumpCheck();
	if(xx*-1>sped){
		sped = sped+10;
		speed+=0.015;
	}
	if(start)
	xx-=speed;
	glFlush();
	if(xx*-1 > neupane+3+0.1){
		neupane+=3;
		khan+=1;
	}
	if (smoothShade)
     glShadeModel (GL_SMOOTH);
   else
     glShadeModel (GL_FLAT);
	
	drawDino();
	
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h); 
	width = w;
	height = h;

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();


	if (projection == PERPECTIVE_PROJECTION)

		glFrustum (-1.0, 1.0, -1.0, 1.0, nearClip, farClip);     
	else

		glOrtho (-1.0, 1.0, -1.0, 1.0, nearClip, farClip);
	 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void myKeyboard( unsigned char key, int x, int y ) 
{
	switch (key)
	{
	
	case's': start = true;break; //start
	case'w' : if(state == 0)state = 1; //jump 
		break;
	//camera
	case '8' : if(phi<3.1)phi+=0.03; break;
	case'7':	phi-=0.03;break;
	case '1': theta+=0.03;break;
	case '2' : theta-=0.03;break;
	//
	case 'a' : if(zz<0.1)zz+=0.45;break;
	case 'd' : if(zz>-0.1)zz-=0.45;break;
	case '$' : smoothShade = !smoothShade;break;//smooth shade
	case 't' : teaPot = !teaPot;break;
	case 'x':  	nearClip -= NEAR_INCREMENT;
		if (nearClip < 0.1)
			nearClip = 0.1;
		break;
	case 'z':  	nearClip += NEAR_INCREMENT;
		if (nearClip > farClip)
			nearClip = farClip - 0.1;
		break;
	

	}

	reshape(width, height);
	glutPostRedisplay();
}
void idle()
{
	if (cntrl == true){
		Sleep(20);
		glutPostRedisplay();}
}
void processLight(){
	for(int x = 0; x<4;x++){
		glutRemoveMenuItem(1);
	}
	if(ambientB)
		glutAddMenuEntry("Global Ambient Light*", 1);
	else
		glutAddMenuEntry("Global Ambient Light", 1);
	if(positional1B)
		glutAddMenuEntry("Positional light 1*",2);
	else
		glutAddMenuEntry("Positional light 1",2);
	if(positional2B)
		glutAddMenuEntry("Positional light 2*",3);
	else
		glutAddMenuEntry("Positional light 2",3);
	if(directionalB)
		glutAddMenuEntry("Directional light*",4);
	else
		glutAddMenuEntry("Directional light 2",4);
	glutPostRedisplay();
	
}

void processRightMenuEvents(int option) {
	
	switch(option){
	case 1:
		filled = true;break;
	case 2:
		filled = false;break;
	}
		glutRemoveMenuItem(1);
		glutRemoveMenuItem(1);
		if(filled){
			glutAddMenuEntry("Filled*",1);
			glutAddMenuEntry("Wireframe",2);
		}
		else{
		glutAddMenuEntry("Filled",1);
			glutAddMenuEntry("Wireframe*",2);
		}
	
}
void processLeftMenuEvents(int option) {
	switch(option){
			case 1:
				ambientB = !ambientB;
				processLight();
				break;
			case 2:
				positional1B = !positional1B;processLight();
				break;
			case 3:
				positional2B = !positional2B;processLight();
				break;
			case 4:
				directionalB = !directionalB; processLight();
				break;
		
	
	}
}
//<<<<<<<<<<<<<<main>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
int main(int argc, char** argv)

{
	
	
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(700,700);
	glutInitWindowPosition(100,100);
	glutCreateWindow("3D-Trex");
	myInit();
	glutDisplayFunc(myDisplay);
	glutReshapeFunc(reshape);
	

	glutKeyboardFunc( myKeyboard );
	glutIdleFunc(idle);
	int lightMenu;
	lightMenu = glutCreateMenu(processLeftMenuEvents);
	glutAddMenuEntry("Global Ambient Light*", 1);
	glutAddMenuEntry("Positional Light 1*",2);
	glutAddMenuEntry("Positional Light 2",3);
	glutAddMenuEntry("Directional Light",4);
	glutCreateMenu(processLeftMenuEvents);
	glutAddSubMenu("Light",lightMenu);
	glutAttachMenu(GLUT_LEFT_BUTTON);

	int shadingMenu;
	shadingMenu = glutCreateMenu(processRightMenuEvents);
	glutAddMenuEntry("Filled*", 1);
	glutAddMenuEntry("Wireframe",2);
	
	glutCreateMenu(processRightMenuEvents);
	glutAddSubMenu("Shading",shadingMenu);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop( );

	return 0;
}
