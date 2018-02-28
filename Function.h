
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
#define title "美洲杯OpenGL"
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

GLuint  picture[8];                                                    // 纹理数组

GLUquadricObj *ba_qua;   
static float footballselfrotat   = 0.0f;                                        // 足球自转速度

static float messiselfrotat  = 0.0f;                                        // messi自转速度
static float messirevolution = 0.0f;                                        // messi公转速度

static float neymarselfrotat  = 0.0f;                                        // neymar自转速度
static float neymarrevolution = 0.0f;                                        // neymar公转速度

static float Cavaniselfrotat  = 0.0f;                                        // Cavani自转速度
static float Cavanirevolution = 0.0f;                                        // Cavani公转速度

static float Agueroselfrotat   = 0.0f;                                        // Aguero自转速度
static float Aguerorevolution  = 0.0f;                                        // Aguero公转速度

static float Alexisselfrotat   = 0.0f;                                     // Alexis自转速度
static float Alexisrevolution  = 0.0f;                                     // Alexis公转速度


void sizecontrol(int width, int height)
{
	if (height==0)
		height=1;                                                        
    glViewport(0,0,width,height);                                       // 设置视口
    // 设置投影矩阵
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	gluLookAt(see[0],see[1],see[2],see[3],see[4],-5,0,1,0);
}

void bmptexture(char *filename, TEXTUREIMAGE *bmpimg)     //  载入球体表面要贴的图片
{
 int i, j;
FILE *file;
BMPFILEHEADER bmpFile;
BMPINFOHEADER imagepoint;
 int lengthpix;

// 初始化纹理数据
bmpimg->imgWidth = 0;
bmpimg->imgHeight = 0;
if (bmpimg->data != NULL)
{
delete []bmpimg->data;
}

// 打开文件
file = fopen(filename, "rb");
if (file == NULL)
{
return;
}

// 获取文件头
rewind(file);
fread(&bmpFile, sizeof(BMPFILEHEADER), 1, file);
fread(&imagepoint, sizeof(BMPINFOHEADER), 1, file);

// 验证文件类型
if (bmpFile.bfType != 0x4D42)
{
return;
}

// 获取图像色彩数
lengthpix = imagepoint.biBitCount >> 3;

// 读取文件数据
bmpimg->data = new unsigned char[imagepoint.biWidth * imagepoint.biHeight * lengthpix];
for(i = 0 ; i < imagepoint.biHeight; i++)
{
fseek(file, bmpFile.bfOffBits + (imagepoint.biHeight - i - 1) * imagepoint.biWidth *lengthpix, SEEK_SET);
for (j = 0; j < imagepoint.biWidth; j++)
{
// 红色分量
fread(bmpimg->data + (i * imagepoint.biWidth + j) * lengthpix + 2,
sizeof(unsigned char), 1, file);
// 绿色分量
fread(bmpimg->data + (i * imagepoint.biWidth + j) * lengthpix + 1,
sizeof(unsigned char), 1, file);
// 蓝色分量
fread(bmpimg->data + (i * imagepoint.biWidth + j) * lengthpix + 0,
sizeof(unsigned char), 1, file);
// Alpha 分量
if (lengthpix == 4)
{
fread(bmpimg->data + (i * imagepoint.biWidth + j) * lengthpix + 3,
sizeof(unsigned char), 1, file);
}
}
}
// 记录图像相关参数
bmpimg->imgWidth = imagepoint.biWidth;
bmpimg->imgHeight = imagepoint.biHeight;
bmpimg->byteCount = lengthpix;
fclose(file);
}

void texturetranform(TEXTUREIMAGE bmpimg, GLuint * texName) //转换为纹理
{

       	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
glGenTextures(1,texName);
glBindTexture(GL_TEXTURE_2D , *texName);
//一下四个函数都是对图像进行滤波以形成纹理
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
bmpimg.imgWidth,bmpimg.imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE,
bmpimg.data);
}
// 初始化OpenGL

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

    // 载入纹理
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

void Display(void)                                                   //建立三维模型
{
	glLoadIdentity();
	// 设置观察点的位置和观察的方向
	gluLookAt(see[0],see[1],see[2],see[3],see[4],-5,0,1,0);

	// 获得系统时间使球体有动态效果
	currenttime = timeGetTime();
    pasetime = (float)((currenttime - lastime) * 0.0005);
	/*cout<<pasetime<<endl;*/
    lastime    = currenttime;
	
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode( GL_MODELVIEW );
	
    glTranslatef(0.0f, 0.0f, -5.0f);                                  
    glRotatef(10, 1.0f ,0.0f, 0.0f);                                    
    glEnable(GL_LIGHT0);                                                

    //绘制背景
    glPushMatrix ();                                                    
    glTranslatef(-5.0f, 3.0f, 0.0f);                                   //将当前坐标系原点移到（-5，3）处
    glEnable(GL_TEXTURE_2D);                                       
    glBindTexture(GL_TEXTURE_2D, picture[6]);                           
    glBegin(GL_QUADS);
	//绘制背景
    glNormal3f( 0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-50.0f, -50.0f, -50.0f);
    glTexCoord2f(6.0f, 0.0f); glVertex3f( 50.0f, -50.0f, -50.0f);
    glTexCoord2f(6.0f, 6.0f); glVertex3f( 50.0f,  50.0f, -50.0f);
    glTexCoord2f(0.0f, 6.0f); glVertex3f(-50.0f,  50.0f, -50.0f);
    glEnd();
	 glPopMatrix ();                                                     // 当前模型矩阵出栈

    //绘制足球
    glBindTexture(GL_TEXTURE_2D, picture[7]);                          
    glEnable(GL_BLEND);                                                
    glDisable(GL_DEPTH_TEST);                                           

    glDisable(GL_LIGHTING);                                             
    glBlendFunc(GL_SRC_ALPHA,GL_ONE);                                   
    glColor4f(1.5f, 1.5f, 1.5f, 0.0f);                                  // 设置RGBA值
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
    glBindTexture(GL_TEXTURE_2D, picture[5]);                           // 足球纹理
	// 控制足球自转
	glRotatef(footballselfrotat,0,1,0);        //足球以footballselfrotat的速度绕y轴自转
    gluSphere(ba_qua, 0.6f, 32, 32);                        // 绘制足球球体，半径为0.6经纬度均为32

    //绘制messi
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D );                                           // 开启纹理
    glPushMatrix ();                                                     
	// 控制messi公转
	//glRotatef(messirevolution, 0.0f,0.0f, 1.0f);  //本函数使球体以速度messiorbit绕某轴公转，轴的设定由后三个参数决定，顺序为x,y,z
	//glRotatef(messirevolution, 0.0f,1.0f, 0.0f); 
	glRotatef(messirevolution, 0.0f,0.0f, 1.0f);
	glTranslatef(2.0*cos(1.25), 0, -2.0*sin(1.25));   //将当前坐标系原点移到括号中三个参数所在的点，其中三个参数顺序为x,y,z                                
    glBindTexture(GL_TEXTURE_2D, picture[0]);   // messi纹理
	glRotatef(-90,1.0f, 0.0f, 0.0f); //将坐标系绕x轴转90度
	//  控制messi自转
	glRotatef(messiselfrotat , 1.0f, 0.0f,1.0f);//本函数使messi球体以messiselfrotat的速度绕y轴自转
    gluSphere(ba_qua, 0.3f, 32, 32);                                  // 绘制messi球体半径为0.3
    glPopMatrix ();                                                      
	

	//绘制neymar
	//过程和绘制messi球体一模一样，使用的函数也一模一样，所以功能参照messi球体的绘制//
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D );                                          
	glPushMatrix ();                                                    
	// 控制neymar公转
	//glRotatef(neymarrevolution , 0.0f, 0.0f, 1.0f);
	//glRotatef(neymarrevolution , 0.0f, 1.0f, 0.0f);
	glRotatef(neymarrevolution , 0.0f, 1.0f, 1.0f);
    glTranslatef(2.0*cos(2.51), 0,-2.0*sin(2.51 ));                                   
    glBindTexture(GL_TEXTURE_2D, picture[1]);                           // neymar纹理
	// 控制neymar自转
	glRotatef(-90,1.0f, 0.0f, 0.0f);   //将坐标系绕x轴转90度
	glRotatef(neymarselfrotat , 0.0f, 0.0f, 1.0f);
    gluSphere(ba_qua, 0.3f, 32, 32);                                  // neymar球体
    glPopMatrix ();

	//绘制
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D );                                           // 开启纹理
	glPushMatrix ();                                                  
	// 控制Cavani公转
	//glRotatef(Cavanirevolution , 0.0f, 0.0f,1.0f);
	//glRotatef(Cavanirevolution , 0.0f, 1.0f,0.0f);
	glRotatef(Cavanirevolution , 1.0f, 2.0f,2.0f);
    glTranslatef(2.0*cos(3.77),0 , -2.0*sin(3.77));                                   
    glBindTexture(GL_TEXTURE_2D, picture[2]);                           // Cavani纹理
	// 控制Cavani自转
	glRotatef(-90,1.0f, 0.0f, 0.0f);   //将坐标系绕x轴转90度
	glRotatef(Cavaniselfrotat , 0.0f, 0.0f, 1.0f);
    gluSphere(ba_qua, 0.3f, 32, 32);                                  // Cavani球体
    glPopMatrix ();

	//绘制Aguero
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D );                                           // 开启纹理
    glPushMatrix ();                                                    
	// 控制Aguero公转
	//glRotatef(Aguerorevolution  , 0.0f, 0.0f, 1.0f);
	//glRotatef(Aguerorevolution  , 0.0f, 1.0f, 0.0f);
	glRotatef(Aguerorevolution  , 1.0f, 0.0f, 1.0f);
    glTranslatef(2.0*cos(5.03),0, -2.0*sin(5.03));                                   
    glBindTexture(GL_TEXTURE_2D, picture[3]);                           // Aguero纹理
	// 控制Aguero自转
	glRotatef(-90,1.0f, 0.0f, 0.0f);   //将坐标系绕x轴转90度
	glRotatef(Agueroselfrotat , 0.0f, 0.0f, 1.0f);
	gluSphere(ba_qua, 0.3f, 32, 32);                                  // Aguero球体
    glPopMatrix ();

    //绘制Alexis
    glDisable(GL_LIGHT0);
    glEnable(GL_TEXTURE_2D );                                           // 开启纹理
	glPushMatrix ();                                                   
	// 控制Alexis公转
    //glRotatef(Alexisrevolution  ,0.0f, 0.0f, 1.0f);
	glRotatef(Alexisrevolution  ,1.0f, 1.0f, 1.0f);
	//glRotatef(Alexisrevolution  , 0.0f, 1.0f, 0.0f);
	glTranslatef(2.0f, 0.0f, 0.0f);                                     
    glBindTexture(GL_TEXTURE_2D, picture[4]);                           // Alexis纹理
	// 控制Alexis自转
	glRotatef(-90,1.0f, 0.0f, 0.0f);   //将坐标系绕x轴转90度
    glRotatef(Alexisselfrotat , 0.0f, 0.0f, 1.0f);
    gluSphere(ba_qua, 0.3f, 32, 32);                                  // Alexis球体
    glPopMatrix ();

 //控制速度
if( pause == true )
	{//其中spmod是一个常数，大小可调，g_fElppasedTime表示当前时刻和上次程序运行完时刻的时间差）
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
		 z_angle += 0.0f;                                                  // 背景不旋转
    glutSwapBuffers();                                                  
	glFlush();
}
}

void control(unsigned char key, int x, int y)            //用键盘控制球体加速，减速//
{
	switch(key) {
		
		case'+':
	   // 加速,减速,暂停
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

void mouse(int btn, int state, int x, int y)                    // 用鼠标控制视角的远近，其中左键让物体变近，右键让物体变远        
{
	if(btn==GLUT_RIGHT_BUTTON && state == GLUT_DOWN)                // 远近视角
		see[2]+=0.3;
	if(btn==GLUT_LEFT_BUTTON && state == GLUT_DOWN&&see[2]>=-4)
		see[2]-=0.3;
}
#endif