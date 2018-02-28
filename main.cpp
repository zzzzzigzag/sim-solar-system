
#include "Function.h"
void main(int argc, char** argv)
{
	//读图片
	bmptexture("Data//Sky.bmp"         , &sky);
	bmptexture("Data//football.bmp"    , &football);
	bmptexture("Data//messi.bmp"       , &messi);
    bmptexture("Data//neymar.bmp"     , &neymar);
	bmptexture("Data//Cavani.bmp"     , &Cavani);
	bmptexture("Data//Aguero.bmp"     , &Aguero);
	bmptexture("Data//Alexis.bmp"      , &Alexis);
	bmptexture("Data//ray.bmp"         , &rayImg);

    glutInit(&argc, argv);                                              // 初始化GLUT库
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);          // 初始化显示模式
    glutInitWindowSize(windows_width, windows_height);                          // 初始化窗口大小
    glutInitWindowPosition(30,30);                                      // 初始化窗口位置
    glutCreateWindow(title);                                        // 建立窗口

    InitGL();                                                           // 初始化OpenGL
    glutDisplayFunc(Display);                                          //调用display函数创建三维模型
    glutReshapeFunc(sizecontrol);                                          //调用sizecontrol

    glutKeyboardFunc(control);                                         //调用键盘控制函数
    glutMouseFunc(mouse);                                               //调用鼠标控制函数

    glutIdleFunc(Display);                                              // 设置窗口空闲时的处理函数
    glutMainLoop();                                                     // 进入事件处理循环
}