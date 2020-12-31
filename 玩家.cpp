#include"ͨ��.h"
IMAGE chara1[2];

IMAGE chara1_runr[8][2];
IMAGE chara1_runl[8][2];
IMAGE chara1_left[2];
IMAGE chara1_right[2];
IMAGE chara1_jump[2][6][2];  //0��1��
IMAGE chara1_fightn[2][7][2];   //�չ�

//��ɫλ����Ϣ
int char_position[2];

void drawchar_runr();
void drawchar_runl();
void draw_jump();
void fightn();   //��ͨ����
#define FIGHT_DELAY 3
int fight_count;

int jump_count;
static char last;  //�ж���һʱ��״̬  

void char_init(){
	char_position[0] = 100;
	char_position[1] = 680;
	fight_count = 6 * FIGHT_DELAY;
	jump_count = 0;
	last = 'r';
}

void getimage_char() {
	//���ұ���
	loadimage(&chara1_runr[0][0], _T("picture\\char1\\right\\1_0.png"));
	loadimage(&chara1_runr[0][1], _T("picture\\char1\\right\\1_1.png"));
	loadimage(&chara1_runr[1][0], _T("picture\\char1\\right\\2_0.png"));
	loadimage(&chara1_runr[1][1], _T("picture\\char1\\right\\2_1.png"));
	loadimage(&chara1_runr[2][0], _T("picture\\char1\\right\\3_0.png"));
	loadimage(&chara1_runr[2][1], _T("picture\\char1\\right\\3_1.png"));
	loadimage(&chara1_runr[3][0], _T("picture\\char1\\right\\4_0.png"));
	loadimage(&chara1_runr[3][1], _T("picture\\char1\\right\\4_1.png"));
	loadimage(&chara1_runr[4][0], _T("picture\\char1\\right\\5_0.png"));
	loadimage(&chara1_runr[4][1], _T("picture\\char1\\right\\5_1.png"));
	loadimage(&chara1_runr[5][0], _T("picture\\char1\\right\\6_0.png"));
	loadimage(&chara1_runr[5][1], _T("picture\\char1\\right\\6_1.png"));
	loadimage(&chara1_runr[6][0], _T("picture\\char1\\right\\7_0.png"));
	loadimage(&chara1_runr[6][1], _T("picture\\char1\\right\\7_1.png"));
	loadimage(&chara1_runr[7][0], _T("picture\\char1\\right\\8_0.png"));
	loadimage(&chara1_runr[7][1], _T("picture\\char1\\right\\8_1.png"));

	//������
	loadimage(&chara1_runl[0][0], _T("picture\\char1\\left\\1_0.png"));
	loadimage(&chara1_runl[0][1], _T("picture\\char1\\left\\1_1.png"));
	loadimage(&chara1_runl[1][0], _T("picture\\char1\\left\\2_0.png"));
	loadimage(&chara1_runl[1][1], _T("picture\\char1\\left\\2_1.png"));
	loadimage(&chara1_runl[2][0], _T("picture\\char1\\left\\3_0.png"));
	loadimage(&chara1_runl[2][1], _T("picture\\char1\\left\\3_1.png"));
	loadimage(&chara1_runl[3][0], _T("picture\\char1\\left\\4_0.png"));
	loadimage(&chara1_runl[3][1], _T("picture\\char1\\left\\4_1.png"));
	loadimage(&chara1_runl[4][0], _T("picture\\char1\\left\\5_0.png"));
	loadimage(&chara1_runl[4][1], _T("picture\\char1\\left\\5_1.png"));
	loadimage(&chara1_runl[5][0], _T("picture\\char1\\left\\6_0.png"));
	loadimage(&chara1_runl[5][1], _T("picture\\char1\\left\\6_1.png"));
	loadimage(&chara1_runl[6][0], _T("picture\\char1\\left\\7_0.png"));
	loadimage(&chara1_runl[6][1], _T("picture\\char1\\left\\7_1.png"));
	loadimage(&chara1_runl[7][0], _T("picture\\char1\\left\\8_0.png"));
	loadimage(&chara1_runl[7][1], _T("picture\\char1\\left\\8_1.png"));

	//��ֹ״̬
	loadimage(&chara1_right[0], _T("picture\\char1\\static\\r0.png"));
	loadimage(&chara1_right[1], _T("picture\\char1\\static\\r1.png"));
	loadimage(&chara1_left[0], _T("picture\\char1\\static\\l0.png"));
	loadimage(&chara1_left[1], _T("picture\\char1\\static\\l1.png"));

	//������Ծ
	loadimage(&chara1_jump[1][0][0], _T("picture\\char1\\jump\\right\\1_0.png"));
	loadimage(&chara1_jump[1][0][1], _T("picture\\char1\\jump\\right\\1_1.png"));
	loadimage(&chara1_jump[1][1][0], _T("picture\\char1\\jump\\right\\2_0.png"));
	loadimage(&chara1_jump[1][1][1], _T("picture\\char1\\jump\\right\\2_1.png"));
	loadimage(&chara1_jump[1][2][0], _T("picture\\char1\\jump\\right\\3_0.png"));
	loadimage(&chara1_jump[1][2][1], _T("picture\\char1\\jump\\right\\3_1.png"));
	loadimage(&chara1_jump[1][3][0], _T("picture\\char1\\jump\\right\\4_0.png"));
	loadimage(&chara1_jump[1][3][1], _T("picture\\char1\\jump\\right\\4_1.png"));
	loadimage(&chara1_jump[1][4][0], _T("picture\\char1\\jump\\right\\5_0.png"));
	loadimage(&chara1_jump[1][4][1], _T("picture\\char1\\jump\\right\\5_1.png"));
	loadimage(&chara1_jump[1][5][0], _T("picture\\char1\\jump\\right\\6_0.png"));
	loadimage(&chara1_jump[1][5][1], _T("picture\\char1\\jump\\right\\6_1.png"));

	//������Ծ
	loadimage(&chara1_jump[0][0][0], _T("picture\\char1\\jump\\left\\1_0.png"));
	loadimage(&chara1_jump[0][0][1], _T("picture\\char1\\jump\\left\\1_1.png"));
	loadimage(&chara1_jump[0][1][0], _T("picture\\char1\\jump\\left\\2_0.png"));
	loadimage(&chara1_jump[0][1][1], _T("picture\\char1\\jump\\left\\2_1.png"));
	loadimage(&chara1_jump[0][2][0], _T("picture\\char1\\jump\\left\\3_0.png"));
	loadimage(&chara1_jump[0][2][1], _T("picture\\char1\\jump\\left\\3_1.png"));
	loadimage(&chara1_jump[0][3][0], _T("picture\\char1\\jump\\left\\4_0.png"));
	loadimage(&chara1_jump[0][3][1], _T("picture\\char1\\jump\\left\\4_1.png"));
	loadimage(&chara1_jump[0][4][0], _T("picture\\char1\\jump\\left\\5_0.png"));
	loadimage(&chara1_jump[0][4][1], _T("picture\\char1\\jump\\left\\5_1.png"));
	loadimage(&chara1_jump[0][5][0], _T("picture\\char1\\jump\\left\\6_0.png"));
	loadimage(&chara1_jump[0][5][1], _T("picture\\char1\\jump\\left\\6_1.png"));

	//�չ�
	loadimage(&chara1_fightn[0][0][0], _T("picture\\char1\\fightn\\left\\0_0.png"));
	loadimage(&chara1_fightn[0][0][1], _T("picture\\char1\\fightn\\left\\0_1.png"));
	loadimage(&chara1_fightn[0][1][0], _T("picture\\char1\\fightn\\left\\1_0.png"));
	loadimage(&chara1_fightn[0][1][1], _T("picture\\char1\\fightn\\left\\1_1.png"));
	loadimage(&chara1_fightn[0][2][0], _T("picture\\char1\\fightn\\left\\2_0.png"));
	loadimage(&chara1_fightn[0][2][1], _T("picture\\char1\\fightn\\left\\2_1.png"));
	loadimage(&chara1_fightn[0][3][0], _T("picture\\char1\\fightn\\left\\3_0.png"));
	loadimage(&chara1_fightn[0][3][1], _T("picture\\char1\\fightn\\left\\3_1.png"));
	loadimage(&chara1_fightn[0][4][0], _T("picture\\char1\\fightn\\left\\4_0.png"));
	loadimage(&chara1_fightn[0][4][1], _T("picture\\char1\\fightn\\left\\4_1.png"));
	loadimage(&chara1_fightn[0][5][0], _T("picture\\char1\\fightn\\left\\5_0.png"));
	loadimage(&chara1_fightn[0][5][1], _T("picture\\char1\\fightn\\left\\5_1.png"));
	loadimage(&chara1_fightn[0][6][0], _T("picture\\char1\\fightn\\left\\6_0.png"));
	loadimage(&chara1_fightn[0][6][1], _T("picture\\char1\\fightn\\left\\6_1.png"));

	loadimage(&chara1_fightn[1][0][0], _T("picture\\char1\\fightn\\right\\0_0.png"));
	loadimage(&chara1_fightn[1][0][1], _T("picture\\char1\\fightn\\right\\0_1.png"));
	loadimage(&chara1_fightn[1][1][0], _T("picture\\char1\\fightn\\right\\1_0.png"));
	loadimage(&chara1_fightn[1][1][1], _T("picture\\char1\\fightn\\right\\1_1.png"));
	loadimage(&chara1_fightn[1][2][0], _T("picture\\char1\\fightn\\right\\2_0.png"));
	loadimage(&chara1_fightn[1][2][1], _T("picture\\char1\\fightn\\right\\2_1.png"));
	loadimage(&chara1_fightn[1][3][0], _T("picture\\char1\\fightn\\right\\3_0.png"));
	loadimage(&chara1_fightn[1][3][1], _T("picture\\char1\\fightn\\right\\3_1.png"));
	loadimage(&chara1_fightn[1][4][0], _T("picture\\char1\\fightn\\right\\4_0.png"));
	loadimage(&chara1_fightn[1][4][1], _T("picture\\char1\\fightn\\right\\4_1.png"));
	loadimage(&chara1_fightn[1][5][0], _T("picture\\char1\\fightn\\right\\5_0.png"));
	loadimage(&chara1_fightn[1][5][1], _T("picture\\char1\\fightn\\right\\5_1.png"));
	loadimage(&chara1_fightn[1][6][0], _T("picture\\char1\\fightn\\right\\6_0.png"));
	loadimage(&chara1_fightn[1][6][1], _T("picture\\char1\\fightn\\right\\6_1.png"));
}

void drawchar_runr() {
	static int count = 0;
	if (count >= 40) {
		count = 0;
	}

	//����ͼƬ
	putimage(char_position[0], char_position[1]+12, &chara1_runr[count/5][1], NOTSRCERASE);
	putimage(char_position[0], char_position[1]+12, &chara1_runr[count/5][0], SRCINVERT);
	count++;
}

void drawchar_runl() {
	static int count = 0;
	if (count >= 40) {
		count = 0;
	}

	//����ͼƬ
	putimage(char_position[0]+40, char_position[1]+12, &chara1_runl[count / 5][1], NOTSRCERASE);
	putimage(char_position[0]+40, char_position[1]+12, &chara1_runl[count / 5][0], SRCINVERT);
	count++;
}

/*
void drawchar() {
	loadimage(&chara1[0], _T("picture\\chara1_0.png"));
	loadimage(&chara1[1], _T("picture\\chara1_1.png"));
	putimage(char_position[0], char_position[1], &chara1[1], NOTSRCERASE);
	putimage(char_position[0], char_position[1], &chara1[0], SRCINVERT);
}
*/

void draw_jump() {
	const int JUMP_DELAY = 5;
	int dir, edit=0;
	if (last == 'l'){
		dir = 0;
		edit += 40;
	}
	else {
		dir = 1;
		edit -= 12;
	}
	if (jump_count <2* JUMP_DELAY) {
		putimage(char_position[0]+edit, char_position[1], &chara1_jump[dir][jump_count/JUMP_DELAY][1], NOTSRCERASE);
		putimage(char_position[0]+ edit, char_position[1], &chara1_jump[dir][jump_count/ JUMP_DELAY][0], SRCINVERT);
		jump_count++;
	}
	else if (jump_count < 3* JUMP_DELAY) {
		putimage(char_position[0]+ edit, char_position[1], &chara1_jump[dir][jump_count / JUMP_DELAY][1], NOTSRCERASE);
		putimage(char_position[0]+ edit, char_position[1], &chara1_jump[dir][jump_count / JUMP_DELAY][0], SRCINVERT);
		if (ground_under(char_position[0], char_position[1] + 100)) {
			jump_count = 3* JUMP_DELAY;
		}
	}
	else if (jump_count<5* JUMP_DELAY) {
		putimage(char_position[0]+ edit, char_position[1], &chara1_jump[dir][jump_count/ JUMP_DELAY][1], NOTSRCERASE);
		putimage(char_position[0]+ edit, char_position[1], &chara1_jump[dir][jump_count/ JUMP_DELAY][0], SRCINVERT);
		jump_count++;
	}
	else if (jump_count >= 5* JUMP_DELAY) {
		putimage(char_position[0]+ edit, char_position[1], &chara1_jump[dir][jump_count / JUMP_DELAY][1], NOTSRCERASE);
		putimage(char_position[0]+ edit, char_position[1], &chara1_jump[dir][jump_count / JUMP_DELAY][0], SRCINVERT);
	}
}

//��ͨ����
void fightn() {
	int dir, edit = 0;
	if (last == 'l') {
		dir = 0;
		edit -= 10;
		if (fight_count == 4 * FIGHT_DELAY) {
			for (int p = -20; p < 50; p++) {
				for (int q = -10; q < 60; q++) {
					for (int i = 0; i < enemy1_max; i++) {
						if (char_position[0] - p == ghost_a[i].x && char_position[1] + q == ghost_a[i].y) {
							ghost_a[i].blood -= 1;
							ghost_a[i].x -= 50;
							if (ghost_a[i].blood == 0) {
								rand_heart(ghost_a[i].x+50, ghost_a[i].y + 20);
							}
							goto OUTFIGHT;
						}
					}
				}
			}
		}
	}
	else {
		dir = 1;
		edit -= 10;
		if (fight_count == 4 * FIGHT_DELAY) {
			for (int p = 60; p < 120; p++) {
				for (int q = -10; q < 60; q++) {
					for (int i = 0; i < enemy1_max; i++) {
						if (char_position[0] + p == ghost_a[i].x && char_position[1] + q == ghost_a[i].y) {
							ghost_a[i].blood -= 1;
							ghost_a[i].x += 50;
							if (ghost_a[i].blood == 0) {
								rand_heart(ghost_a[i].x-50, ghost_a[i].y + 20);
							}
							goto OUTFIGHT;
						}
					}
				}
			}
		}
	}

	OUTFIGHT:

	putimage(char_position[0]+edit, char_position[1]-15, &chara1_fightn[dir][fight_count/ FIGHT_DELAY][1], NOTSRCERASE);
	putimage(char_position[0]+edit, char_position[1]-15, &chara1_fightn[dir][fight_count/ FIGHT_DELAY][0], SRCINVERT);
	fight_count++;
}

void char_control() {
	static int char1_speed = 0;    //y�᷽���ٶ� ����Ϊ������
	static char speedwait = 0;
	if (ground_below()) {
		if (char1_speed < 0)
			char1_speed = -char1_speed - 5;
	}
	if (ground_under(char_position[0],char_position[1])) {
		char1_speed = 0;
		if (fight_count/ FIGHT_DELAY >=7) {    //δ��ʼ����
			if ((GetAsyncKeyState(0x4B) & 0x8000)) {
				fight_count = 0;
			}
			else if ((GetAsyncKeyState(VK_SPACE) & 0x8000)) {
				char1_speed = -15;
			}
			else if (ground_left() == 0 && (GetAsyncKeyState(0x41) & 0x8000)) {   //a
				char_position[0] -= 5;
				drawchar_runl();
				last = 'l';
			}
			else if (ground_right() == 0 && (GetAsyncKeyState(0x44) & 0x8000)) {  //d
				char_position[0] += 5;
				drawchar_runr();
				last = 'r';
			}
			//��ֹ
			else if (last == 'r') {
				putimage(char_position[0], char_position[1], &chara1_right[1], NOTSRCERASE);
				putimage(char_position[0], char_position[1], &chara1_right[0], SRCINVERT);
			}
			else {
				putimage(char_position[0]+40, char_position[1], &chara1_left[1], NOTSRCERASE);
				putimage(char_position[0]+40, char_position[1], &chara1_left[0], SRCINVERT);
			}
		}
		else {
			fightn();
		}
		
		jump_count = 0;
	}
	else {   //���ڵ���
		if (speedwait++ % 2 == 0)
			char1_speed++;
		if (char1_speed > 15 && ground_under(char_position[0], char_position[1] + 15)) {     //��ֹ�ٶȹ��������ж�
			char1_speed =15;
		}
		if (ground_left() == 0 && (GetAsyncKeyState(0x41) & 0x8000)) {   //a
			char_position[0] -= 5;
			last = 'l';
		}
		else if (ground_right() == 0 && (GetAsyncKeyState(0x44) & 0x8000)) {  //d
			char_position[0] += 5;
			last = 'r';
		}
		draw_jump();
	}
	char_position[1] += char1_speed;


}

//�������λ�� 1�õ� 0δ�õ�
int gettool(int x, int y) {
	for (int p = -10; p < 70; p++) {         //x
		for (int q = 0; q < 50; q++) {     //y
			if (char_position[0]+p==x&&char_position[1]+q==y)
				return 1;

		}
	}
	return 0;
}


//�ж��Ƿ��ڵ���    1�ڵ����� 0����        ģ������
int ground_under(int x,int y) {
	for (int i = 50; i < 70; i++) {
		for (int q = 35; q < 68; q++) {
			if (ground_position[x + q][y + i])
				return 1;
		}
	}
	return 0;
}

//�жϽ�ɫ�Ϸ��Ƿ����컨��  1Ϊ�� 0Ϊ��
int ground_below() {
	for (int i = -3; i < 7; i++) {
		for (int q = 40; q < 60; q++) {
			if (ground_position[char_position[0] + q][char_position[1] - i])
				return 1;
		}
	}
	return 0;
}
//�жϽ�ɫ�Ա��Ƿ����ڵ�  1Ϊ�� 0Ϊ��
int ground_left(void){
	//�ж����
	for (int p = 0; p < 10; p++) {         //x
		for (int q = -5; q < 50; q++) {     //y
			if (ground_position[char_position[0] - p][char_position[1] + q])
				return 1;

		}
	}

	return 0;
}

//�ж��ұ�
int ground_right(void) {
	for (int p = 0; p < 10; p++) {         //x
		for (int q = -5; q < 50; q++) {     //y
			if (ground_position[char_position[0] + 60 + p][char_position[1] + q])
				return 1;

		}
	}
	return 0;
}

//�ж�����  ����-1Ϊ����
int die() {
	if (char_position[1] > HIGH) {
		return char_blood_max;
	}
	return ghost_beat() + enemy1_beat();
}