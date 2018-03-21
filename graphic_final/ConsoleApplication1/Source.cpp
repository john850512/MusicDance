#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <math.h>
#include <windows.h> 
#pragma comment(lib, "Winmm.lib") 
#pragma warning(disable:4996)
#define ww 500
#define wh 650
#define NULL 0
#define PAUSE 1
#define STOP 2
#define UI_Up 3
#define UI_Down 4
#define UI_Left 5
#define UI_Right 6
#define GAME_Up 7
#define GAME_Down 8
#define GAME_Left 9
#define GAME_Right 10
using namespace std;

void init();
void buttom_UI();
void top_UI();
void Arrow_LIST();//List Obj
void mymouse(int btn, int state, int x, int y);//glutMouseFunc callback
void menu();
void dis();//glutDisplayFunc callback
void play();//�C���{���X
int pick(int x, int y);//�T�{�I�줰�� 
static float distance_y = 5;//�Ÿ��C���U�����Z��
static int time_counter = 0;//dis()���榸��
static int music_Sheet_counter = 0;//����Ū�F�X�C
static int press_button_counter = 0;//����S��
static int frequence = 0;//�վ�Ū�������W�v
static int score = 0;//�վ�Ū�������W�v
static bool gameover = false;
static char text_Press_Stat[4][20] = { 0 };
//static char Music1_Name[] = "";
//static char Music2_Name[] = "";

int start = 0;//�P�_�O�_�i�J�C��
int play_music = 0;//music flag
int combo = 0;
bool f = false;//check combo

/*
���г]�p:
�C�C���C��dis����ɪ��ɶ��b�A�C����O�O�W�U���k����m
�o��n�`�N�Ptimer���t�X�A�ӹL�K���X�{���ܷ|�Ϯ׭��|
*/
int sheet_Music1[500][4] =
{
	1,0,0,0,
	0,0,0,0,
	0,0,1,0,
	0,0,0,1,
	0,1,0,0,
	0,1,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	0,0,0,0,
	0,0,0,1,
	0,0,1,0,
	0,1,0,0,
	0,1,0,0,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	0,0,0,0,
	1,0,0,0,
	0,0,0,0,
	1,0,0,0,
	0,0,0,1,
	0,0,0,0,

	1,0,0,0,
	0,0,0,0,
	1,0,0,0,
	0,0,0,1,
	1,0,0,0,
	1,0,0,0,
	0,0,1,0,
	0,0,0,0,
	0,0,0,1,
	0,0,0,1,
	0,0,0,1,

	1,0,0,0,
	0,0,0,0,
	1,0,0,0,
	0,0,0,0,
	1,0,0,0,
	0,0,0,1,
	0,0,0,0,

	1,0,0,0,
	0,0,0,0,
	1,0,0,0,
	0,0,0,1,
	1,0,0,0,
	0,0,0,0,
	1,0,0,0,
	0,0,0,1,
	0,0,0,0,
	0,0,0,1,
	0,0,0,1,
	0,0,0,1,

	1,0,0,0,
	0,0,0,0,
	1,0,0,0,
	1,0,0,0,
	0,0,0,1,
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1,
	0,0,0,1,

	1,0,0,0,
	0,0,0,0,
	1,0,0,0,
	1,0,0,0,
	0,0,0,1,
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1,

	1,0,0,0,
	0,1,0,0,
	0,0,1,1,
	0,0,1,1,
	1,0,0,0,
	0,0,1,1,
	0,0,1,1,
	1,0,0,0,
	0,0,0,1,
	0,0,0,1,

	1,0,0,0,
	0,1,0,0,
	0,0,1,1,
	0,0,1,1,
	1,0,0,0,
	0,0,1,1,
	0,0,1,1,
	1,0,0,0,
	0,0,0,1,
	0,0,0,1,

	1,0,0,0,
	0,1,0,0,
	0,0,1,1,
	0,0,1,1,
	1,0,0,0,
	0,0,1,1,
	0,0,1,1,
	1,0,0,0,
	0,0,0,1,
	0,0,0,1,

	0,0,1,0,
	0,0,0,1,
	0,0,1,1,
	0,0,0,0,
	0,0,1,1,
	0,0,1,1,
	1,0,0,0,
	0,1,0,0,
	0,0,0,1,
	0,0,0,1,
	1,1,1,1
};
int sheet_Music2[500][4] =
{
	0,0,0,1,
	0,0,0,0,
	0,1,0,0,
	0,0,0,0,
	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	1,0,0,1
};
bool Press_Stat[4] = { false,false,false,false };//top down left right
struct color
{
	float r, g, b;
}arrow_Exterior_color = { 0.0,1.0,0.0 }, arrow_interior_color = { 0.0,0.0,0.0 };
struct arrow
{
	int x;
	int y;
	int list_Num;
};
vector<arrow> arrow_list;
vector<arrow>::iterator it;

void drawSquare(int x, int y)//�аOpivot ���ե�
{
	GLfloat size = 3.0;
	glColor3ub((char)rand() % 256, (char)
		rand() % 256, (char)rand() % 256);
	glBegin(GL_POLYGON);
	glVertex2f(x + size, y + size);
	glVertex2f(x - size, y + size);
	glVertex2f(x - size, y - size);
	glVertex2f(x + size, y - size);
	glEnd();
}

/*void mouse(int button, int state, int x, int y) {
	int change_y = wh - y;//�ഫ�y��
	if (x >= 150 && x <= 350 && change_y >= 280 && change_y <= 340) {
		if (button == GLUT_LEFT_BUTTON &&state == GLUT_DOWN) {
			start = 1;
		}
	}
}*/

void dis()
{
	glClear(GL_COLOR_BUFFER_BIT);//�C�����e�e���M��
	if (start == 1) {
		if (play_music == 0) {
			PlaySound(L"1.wav", NULL, SND_FILENAME | SND_ASYNC);
			play_music = 1;
		}
		glClear(GL_COLOR_BUFFER_BIT);//�C�����e�e���M��
		top_UI();
		buttom_UI();
		play();
		time_counter++;
		frequence++;

		//��UI_BUTTON�p��~�t
		/*
		drawSquare(400, 40 + 5);
		drawSquare(400, 40 + 20);
		drawSquare(400, 40 + 35);
		*/
	}
		
	else { 
		menu(); 
	}

		glutSwapBuffers();
		/*
		glutFlush() �P glutSwapBuffers()�t�O:
		glutFlush()�j���X�Ȧs�Ϫ��w�ġF
		glutSwapBuffers�洫���P�Ȧs��(GLUT_DOUBLE MODE)�A�Ӧ��ɷ|���t������@��glutFlush
		*/

}
void play()
{
	int shift = 0;
	//cout<< frequence << endl;
	if (frequence == 10)
	{
		for (int i = 1; i <= 4; ++i)
		{
			if (sheet_Music1[music_Sheet_counter][(i - 1)] == 1)
			{
				glPushMatrix();
				arrow temp;
				temp.x = 75 + shift;
				temp.y = 550 - distance_y;
				temp.list_Num = GAME_Up + (i - 1);
				arrow_list.push_back(temp);
				glPopMatrix();
			}
			shift += 100;
		}
		frequence = 0;
		music_Sheet_counter++;
	}
	for (it = arrow_list.begin(); it != arrow_list.end() && !gameover; it++)
	{

		glPushMatrix();
		//cout << time_counter << ":  " << it->x << " " << it->y << " " << it->list_Num << endl;
		glTranslatef(it->x, it->y, 0.0);
		it->y -= distance_y;//�V�U����
		glCallList(it->list_Num);
		glPopMatrix();
		if (it->y < 0)
		{
			it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
			if (arrow_list.size() == 1)it--;//�̫�@�Ӥ����n�S�O�B�z �]���S���U�@�Ӧ�m 
		}
		if (arrow_list.size() == 0)
		{
			gameover = true;
			break;
		}
	}

}

void menu()
{
	int shift = 0;
	char game_name[] ="MUSIC DANCING";
	glColor3f(1.0f, 0.0f, 0.0f);//MUSIC NAME
	shift = 0;
	for (int i = 0; i < strlen(game_name); ++i)
	{
		glRasterPos2i(155 + shift, 400);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, game_name[i]);
		shift += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, game_name[i]);
	}
	glBegin(GL_QUADS);
	glColor3f(1.0, 1.0, 0.0);
	glVertex2i(150, 340);
	glVertex2i(360, 340);
	glVertex2i(360, 280);
	glVertex2i(150, 280);
	glEnd();
	int shift1 = 0;
	char start_game[] = "START GAME";
	glColor3f(0.0f, 0.0f, 0.0f);
	shift1 = 0;
	for (int i = 0; i < strlen(start_game); ++i)
	{
		glRasterPos2i(180 + shift1, 300);
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, start_game[i]);
		shift1 += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, start_game[i]);
	}
	for (int i = 0; i < 500; i += 200)
	{
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(15 + i, 0);
		glVertex2f(35 + i, 0);
		glVertex2f(35 + i, 20);
		glVertex2f(15 + i, 20);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(50 + i, 20);
		glVertex2f(25 + i, 40);
		glVertex2f(0 + i, 20);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(65 + i, 40);
		glVertex2f(85 + i, 40);
		glVertex2f(85 + i, 20);
		glVertex2f(65 + i, 20);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(100 + i, 20);
		glVertex2f(75 + i, 0);
		glVertex2f(50 + i, 20);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(100+ i, 10);
		glVertex2f(100+ i, 30);
		glVertex2f(125+ i, 30);
		glVertex2f(125+ i, 10);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(125+ i, 40);
		glVertex2f(125+ i, 0);
		glVertex2f(150+ i, 20);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(200+ i, 10);
		glVertex2f(200+ i, 30);
		glVertex2f(175+ i, 30);
		glVertex2f(175+ i, 10);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(175+ i, 40);
		glVertex2f(175+ i, 0);
		glVertex2f(150+ i, 20);
		glEnd();
		
	}
	for (int i = 0; i < 500; i += 200)
	{
		glColor3f(0.0, 1.0, 0.0);
		glBegin(GL_POLYGON);
		glVertex2f(15 + i, 610);
		glVertex2f(35 + i, 610);
		glVertex2f(35 + i, 630);
		glVertex2f(15 + i, 630);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(50 + i, 630);
		glVertex2f(25 + i, 650);
		glVertex2f(0 + i, 630);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(65 + i, 650);
		glVertex2f(85 + i, 650);
		glVertex2f(85 + i, 630);
		glVertex2f(65 + i, 630);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(100 + i, 630);
		glVertex2f(75 + i, 610);
		glVertex2f(50 + i, 630);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(100 + i, 640);
		glVertex2f(100 + i, 620);
		glVertex2f(125 + i, 620);
		glVertex2f(125 + i, 640);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(125 + i, 610);
		glVertex2f(125 + i, 650);
		glVertex2f(150 + i, 630);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(200 + i, 640);
		glVertex2f(200 + i, 620);
		glVertex2f(175 + i, 620);
		glVertex2f(175 + i, 640);
		glEnd();
		glBegin(GL_POLYGON);
		glVertex2f(175 + i, 610);
		glVertex2f(175 + i, 650);
		glVertex2f(150 + i, 630);
		glEnd();

	}
}


void top_UI()
{
	int shift = 0;
	char text_musicname[] = "MUSIC NAME: What Makes You Beautiful";
	char text_score[] = "SCORE:";
	char text_stop[] = "EXIT";
	char s[30] = { 0 };
	char c[30] = {0};
	//����������
	//�u���e��:5
	glColor3f(1.0f, 1.0f, 1.0f);
	glRecti(0, 580, 500, 650);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRecti(5, 585, 495, 645);
	//�����\����
	//�u���e��:3
	glColor3f(1.0f, 1.0f, 1.0f);//����:�զ�
	glRecti(422, 550, 500, 580);
	glColor3f(0.0f, 0.0f, 0.0f);//��ӥ\����
	glRecti(425, 553, 497, 580);
	//------------------------------------------------------------------------------------------------
	//|  �����\�����r                                                                            |
	//------------------------------------------------------------------------------------------------
	glColor3f(1.0f, 1.0f, 1.0f);//�զ�
								//MUSIC NAME
	shift = 0;
	for (int i = 0; i < strlen(text_musicname); ++i)
	{
		glRasterPos2i(100 + shift, 610);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text_musicname[i]);
		shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text_musicname[i]);
	}
	//SCORE
	shift = 0;
	for (int i = 0; i < strlen(text_score); ++i)
	{
		glRasterPos2i(100 + shift, 590);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text_score[i]);
		shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text_score[i]);
	}
	//SCORE VARABLE
	itoa(score, s, 10);
	shift = 0;
	glColor3f(1.0f, 0.90f, 0.0f);//����
	for (int i = 0; i < strlen(s); ++i)
	{
		glRasterPos2i(160 + shift, 590);//�����y��(160,590)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, s[i]);
		shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, s[i]);
	}

	//COMBO VARABLE
	itoa(combo, c, 10);
	shift = 0;
	if (combo != 0)
	{
		
		if (combo <= 5)
		{
			glColor3f(1.0f, 0.90f, 0.0f);//����
		}
		else if (combo <= 10)
		{
			glColor3f(1.0f, 0.60f, 0.0f);//���
		}
		else if (combo <= 15)
		{
			glColor3f(1.0f, 0.0f, 0.0f);//��
		}
		else if (combo <= 20)
		{
			glColor3f(1.0f, 0.0f, 1.0f);//��
		}
		for (int i = 0; i < strlen(c); ++i)
		{
			glRasterPos2i(40 + shift, 530);//�����y��(160,590)
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
			shift += glutBitmapWidth(GLUT_BITMAP_TIMES_ROMAN_24, c[i]);
		}
	}
	glColor3f(1.0f, 1.0f, 1.0f);//�զ�
	//EXIT	
	shift = 0;
	for (int i = 0; i < strlen(text_stop); ++i)
	{
		glRasterPos2i(445 + shift, 563);
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text_stop[i]);
		shift += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text_stop[i]);
	}
}
void buttom_UI()
{
	//����������
	//�u���e��:5
	glColor3f(1.0f, 0.0f, 0.0f);
	glRecti(0, 0, 500, 70);
	glColor3f(0.0f, 0.0f, 0.0f);
	glRecti(5, 5, 495, 65);
	glColor3f(1.0f, 0.0f, 0.0f);

	//���U�u
	int shift = 0;
	for (int i = 1; i <= 4; ++i)
	{
		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex2i(100 + shift, 70);
		glVertex2i(100 + shift, 550);
		glEnd();

		//UI:�W�U���k
		glPushMatrix();
		glTranslatef(75 + shift, 20, 0.0);
		if (Press_Stat[(i - 1)])//���U���� �}�үS��
		{
			//���s�S��
			arrow_Exterior_color.r = 1.0;
			arrow_Exterior_color.g = 1.0;
			arrow_Exterior_color.b = 0.0;
			glColor3f(arrow_Exterior_color.r, arrow_Exterior_color.g, arrow_Exterior_color.b);
			if (press_button_counter == 3)//�S�ĩ���
			{
				Press_Stat[(i - 1)] = false;
				press_button_counter = 0;
			}
			glCallList(UI_Up + (i - 1));
			press_button_counter++;
		}
		else
		{
			arrow_Exterior_color.r = 0.0;
			arrow_Exterior_color.g = 1.0;
			arrow_Exterior_color.b = 0.0;
			glColor3f(arrow_Exterior_color.r, arrow_Exterior_color.g, arrow_Exterior_color.b);
			glCallList(UI_Up + (i - 1));
		}
		glPopMatrix();
		//��r�S��
		if (Press_Stat[(i - 1)])//���U���� �}�үS��
		{
			glPushMatrix();
			int shift1 = 0;
			if (!strcmp(text_Press_Stat[(i - 1)], "Excellent"))
			{
				glColor3f(0.6f, 0.0f, 1.0f);//����
			}
			else if (!strcmp(text_Press_Stat[(i - 1)], "Great"))
			{
				glColor3f(0.0f, 1.0f, 0.0f);//���
			}
			else if (!strcmp(text_Press_Stat[(i - 1)], "Good"))
			{
				glColor3f(1.0f, 0.0f, 0.0f);//����
			}
			else
			{
				glColor3f(1.0f, 1.0f, 1.0f);//�զ�
			}
			for (int j = 0; j < strlen(text_Press_Stat[(i - 1)]); ++j)
			{
				glRasterPos2i(100 + shift + shift1, 90);
				glutBitmapCharacter(GLUT_BITMAP_9_BY_15, text_Press_Stat[(i - 1)][j]);
				shift1 += glutBitmapWidth(GLUT_BITMAP_9_BY_15, text_Press_Stat[(i - 1)][j]);
			}
			glColor3f(1.0f, 1.0f, 1.0f);//�զ�
			glPopMatrix();
		}
		shift += 100;
	}

}
void mymouse(int btn, int state, int x, int y)
{
	int change_y = wh - y;//�ഫ�y��
	if (start == 0) {
		if (x >= 150 && x <= 350 && change_y >= 280 && change_y <= 340) {
			if (btn == GLUT_LEFT_BUTTON &&state == GLUT_DOWN) {
				start = 1;
			}
		}
	}
	if (start == 1) {
		int where = 0;
		if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			glPushAttrib(GL_ALL_ATTRIB_BITS);
			where = pick(x, change_y);   // pick�|�e�^�Q��쪺button�ΰe0 
			glPopAttrib();
		}
		switch (where)
		{
		case PAUSE:printf("PAUSE"); PlaySound(NULL, NULL, SND_FILENAME); break;
		case STOP:exit(0); break;
		default:;//nothing
		}
	}
}
void mykey(int key, int xx, int yy)
{
	/*
	4��UI button�� pivot:
	drawSquare(100, 40);
	drawSquare(200, 40);
	drawSquare(300, 40);
	drawSquare(400, 40);
	*/
	if (arrow_list.size() == 0 || gameover)//�C�������N���ΰ�������
	{
		gameover = true;
	}
	else
	{
		switch (key)
		{
		case GLUT_KEY_UP:
			Press_Stat[0] = true;
			for (it = arrow_list.begin(); it != arrow_list.end() && !gameover; it++)
			{
				glPushMatrix();
				if (it->list_Num == GAME_Up)
				{
					if (abs(it->y) <= 12) //40�OUI_TOP��pivot�p��~�t
					{
						combo++;
						strcpy(text_Press_Stat[0], "Excellent");
						printf("100\n");
						score += 100*(1+((float)combo/100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else if (abs(it->y) <= 17)
					{
						combo++;
						strcpy(text_Press_Stat[0], "Great");
						printf("50\n");
						score += 50 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else if (abs(it->y) <= 32)
					{
						combo++;
						strcpy(text_Press_Stat[0], "Good");
						printf("20\n");
						score += 20 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else
					{
						combo = 0;
						strcpy(text_Press_Stat[0], "Miss");
						printf("MISS\n");
					}
					break;
				}
				glPopMatrix();
			}
			break;
		case GLUT_KEY_DOWN:
			Press_Stat[1] = true;
			for (it = arrow_list.begin(); it != arrow_list.end() && !gameover; it++)
			{
				glPushMatrix();
				if (it->list_Num == GAME_Down)
				{
					if (abs(it->y) <= 12) //40�OUI_TOP��pivot�p��~�t
					{
						combo++;
						strcpy(text_Press_Stat[1], "Excellent");
						printf("100\n");
						score += 100 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else if (abs(it->y) <= 17)
					{
						combo++;
						strcpy(text_Press_Stat[1], "Great");
						printf("50\n");
						score += 50 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else if (abs(it->y) <= 32)
					{
						combo++;
						strcpy(text_Press_Stat[1], "Good");
						printf("20\n");
						score += 20 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else
					{
						combo = 0;
						strcpy(text_Press_Stat[1], "Miss");
						printf("MISS\n");
					}
					break;
				}
				glPopMatrix();
			}
			break;
		case GLUT_KEY_LEFT:
			Press_Stat[2] = true;
			for (it = arrow_list.begin(); it != arrow_list.end() && !gameover; it++)
			{
				glPushMatrix();
				if (it->list_Num == GAME_Left)
				{
					if (abs(it->y) <= 12) //40�OUI_TOP��pivot�p��~�t
					{
						combo++;
						strcpy(text_Press_Stat[2], "Excellent");
						printf("100\n");
						score += 100 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else if (abs(it->y) <= 17)
					{
						combo++;
						strcpy(text_Press_Stat[2], "Great");
						printf("50\n");
						score += 50 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else if (abs(it->y) <= 32)
					{
						combo++;
						strcpy(text_Press_Stat[2], "Good");
						printf("20\n");
						score += 20 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else
					{
						combo = 0;
						strcpy(text_Press_Stat[2], "Miss");
						printf("MISS\n");
					}
					break;
				}
				glPopMatrix();
			}
			break;
		case GLUT_KEY_RIGHT:
			Press_Stat[3] = true;
			for (it = arrow_list.begin(); it != arrow_list.end() && !gameover; it++)
			{
				glPushMatrix();
				if (it->list_Num == GAME_Right)
				{
					if (abs(it->y) <= 12) //40�OUI_TOP��pivot�p��~�t
					{
						combo++;
						strcpy(text_Press_Stat[3], "Excellent");
						printf("100\n");
						score += 100 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else if (abs(it->y) <= 17)
					{
						combo++;
						strcpy(text_Press_Stat[3], "Great");
						printf("50\n");
						score += 50 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else if (abs(it->y) <= 32)
					{
						combo++;
						strcpy(text_Press_Stat[3], "Good");
						printf("20\n");
						score += 20 * (1 + ((float)combo / 100.0));
						it = arrow_list.erase(it);//eraser�|�^�ǤU�@�Ӧ�m
					}
					else
					{
						combo = 0;
						strcpy(text_Press_Stat[3], "Miss");
						printf("MISS\n");
					}
					break;
				}
				glPopMatrix();
			}
			break;
		}
	}
}
void timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(40, timer, 0);
}
int pick(int x, int y)//�T�{�I�줰��      
{
	//printf("%d %d\n",x,y);
	if (y >= 553 && y <= 580)
	{
		if (x < 363) return 0;
		else if (x < 425) return PAUSE;
		else if (x < 500) return STOP;
	}
	else return 0;
}
void Arrow_LIST()//List Obj
{
	//------------------------------------------------------------------------------------------------
	//|  UI�������W�U���k:                                                                           |
	//------------------------------------------------------------------------------------------------
	glNewList(UI_Up, GL_COMPILE);//�W
								 //�~�h
	glBegin(GL_POLYGON);
	glVertex2f(15, 0);
	glVertex2f(35, 0);
	glVertex2f(35, 20);
	glVertex2f(15, 20);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(50, 20);
	glVertex2f(25, 40);
	glVertex2f(0, 20);
	glEnd();

	//���h
	glPushMatrix();
	glTranslatef(25 - (25 * 0.9), 20 - (20 * 0.9), 0.0);
	glColor3f(arrow_interior_color.r, arrow_interior_color.g, arrow_interior_color.b);
	glBegin(GL_POLYGON);
	glVertex2f(15 * 0.9, 0 * 0.9);
	glVertex2f(35 * 0.9, 0 * 0.9);
	glVertex2f(35 * 0.9, 20 * 0.9 + 0.5);
	glVertex2f(15 * 0.9, 20 * 0.9 + 0.5);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(50 * 0.9, 20 * 0.9 + 0.5);
	glVertex2f(25 * 0.9, 40 * 0.9);
	glVertex2f(0 * 0.9, 20 * 0.9 + 0.5);
	glEnd();
	glPopMatrix();

	glEndList();

	glNewList(UI_Down, GL_COMPILE);//�U
								   //�~�h
	glBegin(GL_POLYGON);
	glVertex2f(15, 40);
	glVertex2f(35, 40);
	glVertex2f(35, 20);
	glVertex2f(15, 20);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(50, 20);
	glVertex2f(25, 0);
	glVertex2f(0, 20);
	glEnd();
	//���h
	glPushMatrix();
	glTranslatef(25 - (25 * 0.9), 20 - (20 * 0.9), 0.0);
	glColor3f(arrow_interior_color.r, arrow_interior_color.g, arrow_interior_color.b);
	glBegin(GL_POLYGON);
	glVertex2f(15 * 0.9, 40 * 0.9);
	glVertex2f(35 * 0.9, 40 * 0.9);
	glVertex2f(35 * 0.9, 20 * 0.9 - 1);
	glVertex2f(15 * 0.9, 20 * 0.9 - 1);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(50 * 0.9, 20 * 0.9 - 1);
	glVertex2f(25 * 0.9, 0 * 0.9);
	glVertex2f(0 * 0.9, 20 * 0.9 - 1);
	glEnd();
	glPopMatrix();
	glEndList();

	glNewList(UI_Right, GL_COMPILE);//�k
	glBegin(GL_POLYGON);
	glVertex2f(0, 10);
	glVertex2f(0, 30);
	glVertex2f(20, 30);
	glVertex2f(20, 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(20, 40);
	glVertex2f(20, 0);
	glVertex2f(40, 20);
	glEnd();
	//���h
	glPushMatrix();
	glTranslatef(20 - (20 * 0.9), 20 - (20 * 0.9), 0.0);
	glColor3f(arrow_interior_color.r, arrow_interior_color.g, arrow_interior_color.b);
	glBegin(GL_POLYGON);
	glVertex2f(0 * 0.9, 10 * 0.9);
	glVertex2f(0 * 0.9, 30 * 0.9);
	glVertex2f(20 * 0.9 + 1, 30 * 0.9);
	glVertex2f(20 * 0.9 + 1, 10 * 0.9);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(20 * 0.9 + 1, 40 * 0.9);
	glVertex2f(20 * 0.9 + 1, 0 * 0.9);
	glVertex2f(40 * 0.9, 20 * 0.9);
	glEnd();
	glPopMatrix();
	glEndList();

	glNewList(UI_Left, GL_COMPILE);//��
	glBegin(GL_POLYGON);
	glVertex2f(40, 10);
	glVertex2f(40, 30);
	glVertex2f(20, 30);
	glVertex2f(20, 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(20, 40);
	glVertex2f(20, 0);
	glVertex2f(0, 20);
	glEnd();

	//���h
	glPushMatrix();
	glTranslatef(20 - (20 * 0.9), 20 - (20 * 0.9), 0.0);
	glColor3f(arrow_interior_color.r, arrow_interior_color.g, arrow_interior_color.b);
	glBegin(GL_POLYGON);
	glVertex2f(40 * 0.9, 10 * 0.9);
	glVertex2f(40 * 0.9, 30 * 0.9);
	glVertex2f(20 * 0.9 - 1, 30 * 0.9);
	glVertex2f(20 * 0.9 - 1, 10 * 0.9);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(20 * 0.9 - 1, 40 * 0.9);
	glVertex2f(20 * 0.9 - 1, 0 * 0.9);
	glVertex2f(0 * 0.9, 20 * 0.9);
	glEnd();
	glPopMatrix();
	glEndList();

	//------------------------------------------------------------------------------------------------
	//|  GAME�������W�U���k:                                                                         |
	//------------------------------------------------------------------------------------------------
	glNewList(GAME_Up, GL_COMPILE);//�W
	glColor3f(0.0, 1.0, 0.0);
	//�~�h
	glBegin(GL_POLYGON);
	glVertex2f(15, 0);
	glVertex2f(35, 0);
	glVertex2f(35, 20);
	glVertex2f(15, 20);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(50, 20);
	glVertex2f(25, 40);
	glVertex2f(0, 20);
	glEnd();
	glEndList();

	glNewList(GAME_Down, GL_COMPILE);//�U
	glColor3f(0.0, 1.0, 0.0);
	//�~�h
	glBegin(GL_POLYGON);
	glVertex2f(15, 40);
	glVertex2f(35, 40);
	glVertex2f(35, 20);
	glVertex2f(15, 20);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(50, 20);
	glVertex2f(25, 0);
	glVertex2f(0, 20);
	glEnd();
	glEndList();

	glNewList(GAME_Right, GL_COMPILE);//�k
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(0, 10);
	glVertex2f(0, 30);
	glVertex2f(20, 30);
	glVertex2f(20, 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(20, 40);
	glVertex2f(20, 0);
	glVertex2f(40, 20);
	glEnd();
	glEndList();

	glNewList(GAME_Left, GL_COMPILE);//��
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
	glVertex2f(40, 10);
	glVertex2f(40, 30);
	glVertex2f(20, 30);
	glVertex2f(20, 10);
	glEnd();
	glBegin(GL_POLYGON);
	glVertex2f(20, 40);
	glVertex2f(20, 0);
	glVertex2f(0, 20);
	glEnd();
	glEndList();
}
void init()
{
	glViewport(0, 0, ww, wh);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, ww, 0, wh);
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	Arrow_LIST();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);//��l��glut
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	glutInitWindowSize(ww, wh);
	glutInitWindowPosition(450, 0);
	glutCreateWindow("Music Dancing");

	init();	
	glutDisplayFunc(dis);	

	/*CStatic *pStatic = (CStatic*)GetDlgItem(IDC_STATIC1); HWNDh = pStatic->GetSafeHwnd();
	CString open1;
	char buf[256];
	open1.Format("open ""C:\\Windows\\Media""One Direction - What Makes You Beautiful (online-audio-converter.com).wav Aliasmovie parent %u Style %u notify", h, WS_CHILD);
	mciSendString(open1.GetBuffer(open1.GetLength()), buf, sizeof(buf), NULL);*/

	glutMouseFunc(mymouse);
	glutSpecialFunc(mykey);//�W�U���k�n�ίS������
	glutTimerFunc(50, timer, 0);
	glutMainLoop();//glutMainLoop()�|���а���O�^�I��ƪ�function

	return 0;
}