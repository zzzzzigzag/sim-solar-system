
#ifndef LOADTEXTURE
#define LOADTEXTURE

// ����ͼ��ṹ
typedef struct
{
	int imgWidth;				// ������
	int imgHeight;				// ����߶�
	unsigned char byteCount;	// ÿ�����ض�Ӧ���ֽ�����3��24λͼ��4����alphaͨ����24λͼ
	unsigned char *data;		// ��������
}TEXTUREIMAGE;

// BMP�ļ�ͷ
#pragma pack(2)
typedef struct {
	unsigned short	bfType;			// �ļ�����
	unsigned long   bfSize;			// �ļ���С
	unsigned short	bfReserved1;	// ����λ
	unsigned short	bfReserved2;	// ����λ
	unsigned long	bfOffBits;		// ����ƫ��λ��
}BMPFILEHEADER;
#pragma pack()

// BMP��Ϣͷ
typedef struct {
	unsigned long	biSize;			// �˽ṹ��С
	long			biWidth;		// ͼ����
	long			biHeight;		// ͼ��߶�
	unsigned short	biPlanes;		// ��ɫ������
	unsigned short	biBitCount;		// ÿ�����ض�Ӧ��λ����24��24λͼ��32����alphaͨ����24λͼ
	unsigned long	biCompression;	// ѹ��
	unsigned long	biSizeImage;	// ͼ���С
	long			biXPelsPerMeter;// ����ֱ���
	long			biYPelsPerMeter;// ����ֱ���
	unsigned long	biClrUsed;		// ��ɫʹ����
	unsigned long	biClrImportant;	// ��Ҫ��ɫ��
}BMPINFOHEADER;
 
//����BMPλͼ�ļ�
void LoadBmp(char *filename,  TEXTUREIMAGE *textureImg);

//��������
void MakeTexture(TEXTUREIMAGE textureImg, GLuint * texName);

#endif