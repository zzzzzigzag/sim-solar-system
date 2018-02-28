
#ifndef FUNCTION
#define FUNCTION
#include <windows.h>
#include <glut.h>
#include <math.h>
#include "loadTexture.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>
#include <iostream>
using namespace std;
#define title "���ޱ�OpenGL"
const int windows_width = 800;
const int windows_height = 600;
GLfloat liposition[] = { 0.0f, 0.0f, 0.0f, 1.0f };                   
GLfloat amreflection[] = { 10.0f, 10.0f, 10.0f, 10.0f };               
GLfloat difreflection[] = { 1.0f, 1.0f, 1.0f, 0.0f };                    
double currenttime;                         
double lastime;                           
                                            
float  pasetime=0.0f;
GLfloat z_angle;                                                        
float  spmod = 2;
float angle=0.0;
static GLdouble see[]= {0,-0.8,0,0,0};                             
bool   pause = true;                                               
TEXTUREIMAGE  sky;
TEXTUREIMAGE  football;
TEXTUREIMAGE  messi;
TEXTUREIMAGE  neymar;
TEXTUREIMAGE  Cavani;
TEXTUREIMAGE  Aguero;
TEXTUREIMAGE  Alexis;
TEXTUREIMAGE  rayImg;

GLuint  picture[8];                                                    // ��������

GLUquadricObj *ba_qua;   
static float footballselfrotat   = 0.0f;                                        // ������ת�ٶ�

static float messiselfrotat  = 0.0f;                                        // messi��ת�ٶ�
static float messirevolution = 0.0f;                                        // messi��ת�ٶ�

static float neymarselfrotat  = 0.0f;                                        // neymar��ת�ٶ�
static float neymarrevolution = 0.0f;                                        // neymar��ת�ٶ�

static float Cavaniselfrotat  = 0.0f;                                        // Cavani��ת�ٶ�
static float Cavanirevolution = 0.0f;                                        // Cavani��ת�ٶ�

static float Agueroselfrotat   = 0.0f;                                        // Aguero��ת�ٶ�
static float Aguerorevolution  = 0.0f;                                        // Aguero��ת�ٶ�

static float Alexisselfrotat   = 0.0f;                                     // Alexis��ת�ٶ�
static float Alexisrevolution  = 0.0f;                                     // Alexis��ת�ٶ�


void sizecontrol(int width, int height)
{
	if (height==0)
		height=1;                                                        
    glViewport(0,0,width,height);                                       // �����ӿ�
    // ����ͶӰ����
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(see[0],see[1],see[2],see[3],see[4],-5,0,1,0);
}

void bmptexture(char *filename, TEXTUREIMAGE *bmpimg)     //  �����������Ҫ����ͼƬ
{
 int i, j;
FILE *file;
BMPFILEHEADER bmpFile;
BMPINFOHEADER imagepoint;
 int lengthpix;

// ��ʼ����������
bmpimg->imgWidth = 0;
bmpimg->imgHeight = 0;
if (bmpimg->data != NULL)
{
delete []bmpimg->data;
}

// ���ļ�
file = fopen(filename, "rb");
if (file == NULL)
{
return;
}

// ��ȡ�ļ�ͷ
rewind(file);
fread(&bmpFile, sizeof(BMPFILEHEADER), 1, file);
fread(&imagepoint, sizeof(BMPINFOHEADER), 1, file);

// ��֤�ļ�����
if (bmpFile.bfType != 0x4D42)
{
return;
}

// ��ȡͼ��ɫ����
lengthpix = imagepoint.biBitCount >> 3;

// ��ȡ�ļ�����
bmpimg->data = new unsigned char[imagepoint.biWidth * imagepoint.biHeight * lengthpix];
for(i = 0 ; i < imagepoint.biHeight; i++)
{
fseek(file, bmpFile.bfOffBits + (imagepoint.biHeight - i - 1) * imagepoint.biWidth *lengthpix, SEEK_SET);
for (j = 0; j < imagepoint.biWidth; j++)
{
// ��ɫ����
fread(bmpimg->data + (i * imagepoint.biWidth + j) * lengthpix + 2,
sizeof(unsigned char), 1, file);
// ��ɫ����
fread(bmpimg->data + (i * imagepoint.biWidth + j) * lengthpix + 1,
sizeof(unsigned char), 1, file);
// ��ɫ����
fread(bmpimg->data + (i * imagepoint.biWidth + j) * lengthpix + 0,
sizeof(unsigned char), 1, file);
// Alpha ����
if (lengthpix == 4)
{
fread(bmpimg->data + (i * imagepoint.biWidth + j) * lengthpix + 3,
sizeof(unsigned char), 1, file);
}
}
}
// ��¼ͼ����ز���
bmpimg->imgWidth = imagepoint.biWidth;
bmpimg->imgHeight = imagepoint.biHeight;
bmpimg->byteCount = lengthpix;
fclose(file);
}

void texturetranform(TEXTUREIMAGE bmpimg, GLuint * texName) //ת��Ϊ����
{

       	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
glGenTextures(1,texName);
glBindTexture(GL_TEXTURE_2D , *texName);
//һ���ĸ��������Ƕ�ͼ������˲����γ�����
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
bmpimg.imgWidth,bmpimg.imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
bmpimg.data);
}
// ��ʼ��OpenGL

void InitGL(void)
{
	glClearDepth(2.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_CULL_FACE);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glLightfv(GL_LIGHT1, GL_AMBIENT, amreflection);                     
    glLightfv(GL_LIGHT1, GL_DIFFUSE, difreflection);                    
	glDisable(GL_LIGHTING);                                             
    glEnable(GL_LIGHT1);                                               

    // ��������
	glEnable(GL_TEXTURE_2D);                                            
	texturetranform(messi, &picture[0]);
	texturetranform(neymar, &picture[1]);
	texturetranform(Cavani, &picture[2]);
	texturetranform(Aguero, &picture[3]);
	texturetranform( Alexis, &picture[4]);
	texturetranform(football, &picture[5]);
	texturetranform(sky, &picture[6]);
	texturetranform(rayImg, &picture[7]);
    ba_qua = gluNewQuadric();                                          
    gluQuadricTexture(ba_qua, GLU_TRUE);                              
    gluQuadricDrawStyle(ba_qua, GLU_FILL);                             
}

void Display(void)                                                   //������άģ��
{
	glLoadIdentity();
	// ���ù۲���λ�ú͹۲�ķ���
	gluLookAt(see[0],see[1],see[2],see[3],see[4],-5,0,1,0);

	// ���ϵͳʱ��ʹ�����ж�̬Ч��
	currenttime = timeGetTime();
    pasetime = (float)((currenttime - lastime) * 0.0005);
	/*cout<<pasetime<<endl;*/
    lastime    = currenttime;
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode( GL_MODELVIEW );
	
    glTranslatef(0.0f, 0.0f, -5.0f);                                  
    glRotatef(10, 1.0f ,0.0f, 0.0f);                                    
    glEnable(GL_LIGHT0);                                                

    //���Ʊ���
    glPushMatrix ();                                                    
    glTranslatef(-5.0f, 3.0f, 0.0f);                                   //����ǰ����ϵԭ���Ƶ���-5��3����
    glEnable(GL_TEXTURE_2D);                                       
    glBindTexture(GL_TEXTURE_2D, picture[6]);                           
    glBegin(GL_QUADS);
	//���Ʊ���
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(6.0f, 0.0f); glVertex3f( 50.0f, -50.0f, -50.0f);
    glTexCoord2f(6.0f, 6.0f); glVertex3f( 50.0f,  50.0f, -50.0f);
    glTexCoord2f(0.0f, 6.0f); glVertex3f(-50.0f,  50.0f, -50.0f);
    glEnd();
	 glPopMatrix ();                                                     // ��ǰģ�;����ջ

    //��������
    glBindTexture(GL_TEXTURE_2D, picture[7]);                          
    glEnable(GL_BLEND);                                                
    glDisable(GL_DEPTH_TEST);                                           

    glDisable(GL_LIGHTING);                                             
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);                                   
    glColor4f(1.5f, 1.5f, 1.5f, 0.0f);                                  // ����RGBAֵ
    glBegin(GL_QUADS);
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f,-1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,-1.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, 0.0f);
    glEnd();
    glDisable(GL_BLEND);                                                
    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);                                              
    glLightfv(GL_LIGHT1, GL_POSITION, liposition);                   
    glBindTexture(GL_TEXTURE_2D, picture[5]);                           // ��������
	// ����������ת
	glRotatef(footballselfrotat,0,1,0);        //������footballselfrotat���ٶ���y����ת
    gluSphere(ba_qua, 0.6f, 32, 32);                        // �����������壬�뾶Ϊ0.6��γ�Ⱦ�Ϊ32

    //����messi
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D );                                           // ��������
    glPushMatrix ();                                                     
	// ����messi��ת
	//glRotatef(messirevolution, 0.0f,0.0f, 1.0f);  //������ʹ�������ٶ�messiorbit��ĳ�ṫת������趨�ɺ���������������˳��Ϊx,y,z
	//glRotatef(messirevolution, 0.0f,1.0f, 0.0f); 
	glRotatef(messirevolution, 0.0f,0.0f, 1.0f);
	glTranslatef(2.0*cos(1.25), 0, -2.0*sin(1.25));   //����ǰ����ϵԭ���Ƶ������������������ڵĵ㣬������������˳��Ϊx,y,z                                
    glBindTexture(GL_TEXTURE_2D, picture[0]);   // messi����
	glRotatef(-90,1.0f, 0.0f, 0.0f); //������ϵ��x��ת90��
	//  ����messi��ת
	glRotatef(messiselfrotat , 1.0f, 0.0f,1.0f);//������ʹmessi������messiselfrotat���ٶ���y����ת
    gluSphere(ba_qua, 0.3f, 32, 32);                                  // ����messi����뾶Ϊ0.3
    glPopMatrix ();                                                      
	

	//����neymar
	//���̺ͻ���messi����һģһ����ʹ�õĺ���Ҳһģһ�������Թ��ܲ���messi����Ļ���//
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D );                                          
	glPushMatrix ();                                                    
	// ����neymar��ת
	//glRotatef(neymarrevolution , 0.0f, 0.0f, 1.0f);
	//glRotatef(neymarrevolution , 0.0f, 1.0f, 0.0f);
	glRotatef(neymarrevolution , 0.0f, 1.0f, 1.0f);
    glTranslatef(2.0*cos(2.51), 0,-2.0*sin(2.51 ));                                   
    glBindTexture(GL_TEXTURE_2D, picture[1]);                           // neymar����
	// ����neymar��ת
	glRotatef(-90,1.0f, 0.0f, 0.0f);   //������ϵ��x��ת90��
	glRotatef(neymarselfrotat , 0.0f, 0.0f, 1.0f);
    gluSphere(ba_qua, 0.3f, 32, 32);                                  // neymar����
    glPopMatrix ();

	//����
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D );                                           // ��������
	glPushMatrix ();                                                  
	// ����Cavani��ת
	//glRotatef(Cavanirevolution , 0.0f, 0.0f,1.0f);
	//glRotatef(Cavanirevolution , 0.0f, 1.0f,0.0f);
	glRotatef(Cavanirevolution , 1.0f, 2.0f,2.0f);
    glTranslatef(2.0*cos(3.77),0 , -2.0*sin(3.77));                                   
    glBindTexture(GL_TEXTURE_2D, picture[2]);                           // Cavani����
	// ����Cavani��ת
	glRotatef(-90,1.0f, 0.0f, 0.0f);   //������ϵ��x��ת90��
	glRotatef(Cavaniselfrotat , 0.0f, 0.0f, 1.0f);
    gluSphere(ba_qua, 0.3f, 32, 32);                                  // Cavani����
    glPopMatrix ();

	//����Aguero
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D );                                           // ��������
    glPushMatrix ();                                                    
	// ����Aguero��ת
	//glRotatef(Aguerorevolution  , 0.0f, 0.0f, 1.0f);
	//glRotatef(Aguerorevolution  , 0.0f, 1.0f, 0.0f);
	glRotatef(Aguerorevolution  , 1.0f, 0.0f, 1.0f);
    glTranslatef(2.0*cos(5.03),0, -2.0*sin(5.03));                                   
    glBindTexture(GL_TEXTURE_2D, picture[3]);                           // Aguero����
	// ����Aguero��ת
	glRotatef(-90,1.0f, 0.0f, 0.0f);   //������ϵ��x��ת90��
	glRotatef(Agueroselfrotat , 0.0f, 0.0f, 1.0f);
	gluSphere(ba_qua, 0.3f, 32, 32);                                  // Aguero����
    glPopMatrix ();

    //����Alexis
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D );                                           // ��������
	glPushMatrix ();                                                   
	// ����Alexis��ת
    //glRotatef(Alexisrevolution  ,0.0f, 0.0f, 1.0f);
	glRotatef(Alexisrevolution  ,1.0f, 1.0f, 1.0f);
	//glRotatef(Alexisrevolution  , 0.0f, 1.0f, 0.0f);
	glTranslatef(2.0f, 0.0f, 0.0f);                                     
    glBindTexture(GL_TEXTURE_2D, picture[4]);                           // Alexis����
	// ����Alexis��ת
	glRotatef(-90,1.0f, 0.0f, 0.0f);   //������ϵ��x��ת90��
    glRotatef(Alexisselfrotat , 0.0f, 0.0f, 1.0f);
    gluSphere(ba_qua, 0.3f, 32, 32);                                  // Alexis����
    glPopMatrix ();

 //�����ٶ�
if( pause == true )
	{//����spmod��һ����������С�ɵ���g_fElppasedTime��ʾ��ǰʱ�̺��ϴγ���������ʱ�̵�ʱ��
		footballselfrotat -= spmod * (pasetime * 10.0f);

		messiselfrotat -= spmod * (pasetime * 10.0f);
		messirevolution -= spmod * (pasetime * 20.0f);

		neymarselfrotat -= spmod * (pasetime * 10.0f);
		neymarrevolution -= spmod * (pasetime * 20.0f);

		Cavaniselfrotat  -= spmod * (pasetime * 10.0f);
		Cavanirevolution -= spmod * (pasetime * 20.0f);

		Agueroselfrotat -= spmod * (pasetime *10.0f);
		Aguerorevolution -= spmod * (pasetime * 20.0f);

		Alexisselfrotat -= spmod * (pasetime * 10.0f);
		Alexisrevolution -= spmod * (pasetime * 20.0f);
		 z_angle += 0.0f;                                                  // ��������ת
    glutSwapBuffers();                                                  
	glFlush();
}
}

void control(unsigned char key, int x, int y)            //�ü��̿���������٣�����//
{
	switch(key) {
		
		case'+':
	   // ����,����,��ͣ
		spmod+=0.5;
		glutPostRedisplay();
		break;

		case ' ':
		pause = !pause;
		glutPostRedisplay();
		break;

		case'-':
		spmod-=0.5;
		glutPostRedisplay();
		break;
        default:
		break;
	   }
}

void mouse(int btn, int state, int x, int y)                    // ���������ӽǵ�Զ����������������������Ҽ��������Զ        
{
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)                // Զ���ӽ�
		see[2]+=0.3;
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN&&see[2]>=-4)
		see[2]-=0.3;
}
#endif