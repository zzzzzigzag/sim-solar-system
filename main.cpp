
#include "Function.h"
void main(int argc, char** argv)
{
	//��ͼƬ
	bmptexture("Data//Sky.bmp"         , &sky);
	bmptexture("Data//football.bmp"    , &football);
	bmptexture("Data//messi.bmp"       , &messi);
    bmptexture("Data//neymar.bmp"     , &neymar);
	bmptexture("Data//Cavani.bmp"     , &Cavani);
	bmptexture("Data//Aguero.bmp"     , &Aguero);
	bmptexture("Data//Alexis.bmp"      , &Alexis);
	bmptexture("Data//ray.bmp"         , &rayImg);

    glutInit(&argc, argv);                                              // ��ʼ��GLUT��
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);          // ��ʼ����ʾģʽ
    glutInitWindowSize(windows_width, windows_height);                          // ��ʼ�����ڴ�С
    glutInitWindowPosition(30,30);                                      // ��ʼ������λ��
    glutCreateWindow(title);                                        // ��������

    InitGL();                                                           // ��ʼ��OpenGL
    glutDisplayFunc(Display);                                          //����display����������άģ��
    glutReshapeFunc(sizecontrol);                                          //����sizecontrol

    glutKeyboardFunc(control);                                         //���ü��̿��ƺ���
    glutMouseFunc(mouse);                                               //���������ƺ���

    glutIdleFunc(Display);                                              // ���ô��ڿ���ʱ�Ĵ�����
    glutMainLoop();                                                     // �����¼�����ѭ��
}