#include"ͨ��.h"


//����������x y˳�򣨲�ͬ�봫ͳ���к��У�
#pragma comment(lib,"Winmm.lib")


IMAGE enemy1[2];
IMAGE enemy1fire1left[2];
IMAGE enemy1fire1right[2];     //����Գ� ����


//λ����Ϣ

bool ground_position[WIDTH][HIGH] = { 0 };      //   �ذ�λ����Ϣ    [0]:x_position  [1]:����
int enemy1_position[enemy1_max][2] = { 0 };     //enemy1λ��
int enemy1fire1left_position[enemy1_max][2] = { 0 };      //enemy1 fireλ�� ����   x y����
int enemy1fire1right_position[enemy1_max][2] = { 0 };        //�ҷ��� x y����
int tool1_position[enemy1_max][2];  //����һλ��
int screen_down = 0;    //��Ļ�ܹ������ƶ��ľ���  ������������� �Ѷ�

int lastground_x[2] = { 10,WIDTH - 10 };   //������һ���ص�λ��

int main() {
	//��ʼ������
	init();
	getimage_char();
	int blood = BLOOD_MAX;   //Ѫ��ϵͳ
	int blood_pluse = 0;     //�޵�ʱ��



	int top_ground = 750;   //��¼���Ϸ��ذ��y����  �������ɵ���
	while (1) {
		//��ͼ
		drawbackground();
		char_control();    //��ɫ����

		
		drawenemy1();
		enemy_control();    //���˿���
		drawheart(blood);
		drawground();
		drawtool1();
		FlushBatchDraw();

		

		//����һ�ж�
		if (blood < BLOOD_MAX) {
			for (int i = 0; i < enemy1_max; i++) {
				if (gettool(tool1_position[i][0], tool1_position[i][1])) {
					blood++;
					tool1_position[i][0] = WIDTH;
					tool1_position[i][1] = HIGH;
				}
			}
			
			
		}
		

		if (top_ground > LEVEL) {
			top_ground -= LEVEL;
			random_ground(top_ground);
		}

		//��Ļ�����ƶ�
		if (char_position[1] < HIGH / 3) {    
			everything_down(10);
			screen_down += 10;
			top_ground += 10;
		}

		////��ͼ���Դ���
		//everything_down(10);
		//screen_down += 10;
		//top_ground += 10;

		if (blood_pluse) {
			blood_pluse--;
		}
		else {
			int blood_substract = die();
			if (blood_substract > 0) {
				blood -= blood_substract;
				blood_pluse = 25;
				if (blood <= 0) {
					break;
				}
			}
		}
		
	}
	EndBatchDraw();
	printf("Game over\n");
	printf("��ķ�����%d", screen_down);
	Sleep(100);
	return 0;
}

//��ʼ�� ֻ�ڿ�ʼʱִ��
void init() {
	mciSendString(_T("open  bkmusic.mp3 alias bkmusic") ,NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	initgraph(WIDTH, HIGH);
	BeginBatchDraw();
	for (int i = 10; i < WIDTH - 10; i++) {     //�������·��ĵذ�
		ground_position[i][750] = 1;
	}

	////���Դ���
	//for (int i = 500; i < 1200 - 10; i++) {     //�������·��ĵذ�
	//	ground_position[i][680] = 1;
	//}
	// ��ʼ����1��λ��  fire λ��
	for (int i = 0; i < enemy1_max;i++) {
		enemy1_position[i][1] = HIGH;
		enemy1fire1left_position[i][1] = HIGH;
		enemy1fire1right_position[i][1] = HIGH;
	}

	//Ѫ��
	for (int i = 0; i < enemy1_max; i++) {
		tool1_position[i][0] = WIDTH;
		tool1_position[i][1] = HIGH;
	}

	enemy_init();
}


void drawtool1(void) {
	IMAGE tool[2];
	loadimage(&tool[0], _T("tool_heart_0.png"));
	loadimage(&tool[1], _T("tool_heart_1.png"));
	for (int i = 0; i < enemy1_max; i++) {
		putimage(tool1_position[i][0], tool1_position[i][1], &tool[1], NOTSRCERASE);
		putimage(tool1_position[i][0], tool1_position[i][1], &tool[0], SRCINVERT);
	}

}
void drawbackground() {
	IMAGE bk;
	loadimage(&bk, _T("bk.jpg"));
	putimage(0, 0, &bk);
}

void drawheart(int blood) {
	IMAGE heart_empty[2];
	IMAGE heart_full[2];
	loadimage(&heart_empty[0], _T("heart_empty_0.png"));
	loadimage(&heart_empty[1], _T("heart_empty_1.png"));
	loadimage(&heart_full[0], _T("heart_full_0.png"));
	loadimage(&heart_full[1], _T("heart_full_1.png"));

	for (int i = 0; i < BLOOD_MAX; i++) {
		if (i < blood) {
			putimage(40 * i + 20, 10, &heart_full[1], NOTSRCERASE);
			putimage(40 * i + 20, 10, &heart_full[0], SRCINVERT);
		}
		else {
			putimage(40 * i + 20, 10, &heart_empty[1], NOTSRCERASE);
			putimage(40 * i + 20, 10, &heart_empty[0], SRCINVERT);
		}
	}
}


void drawenemy1(void) {
	//��
	loadimage(&enemy1[0], _T("enemy1_0.png"));
	loadimage(&enemy1[1], _T("enemy1_1.png"));

	//fire
	loadimage(&enemy1fire1left[0], _T("enemy1fire1_0.png"));
	loadimage(&enemy1fire1left[1], _T("enemy1fire1_1.png"));
	for (int i = 0; i < enemy1_max; i++) {
		putimage(enemy1_position[i][0], enemy1_position[i][1], &enemy1[1], NOTSRCERASE);
		putimage(enemy1_position[i][0], enemy1_position[i][1], &enemy1[0], SRCINVERT);
		putimage(enemy1fire1left_position[i][0], enemy1fire1left_position[i][1], &enemy1fire1left[1], NOTSRCERASE);
		putimage(enemy1fire1left_position[i][0], enemy1fire1left_position[i][1], &enemy1fire1left[0], SRCINVERT);
	}
}

//��ʾ��ʼ����
void drawground() {
	IMAGE brick[2];
	loadimage(&brick[0], _T("ground_0.png"));
	loadimage(&brick[1], _T("ground_1.png"));
	for (int i = 0; i < HIGH; i++) {
		for (int q = 0; q < WIDTH; q++) {
			if (ground_position[q][i]) {
				putimage(q, i, &brick[1], NOTSRCERASE);
				putimage(q, i, &brick[0], SRCINVERT);
				q += 15;
			}
		}
	}
}




//�����������      ����Ҫ���ɵĸ߶� ���ɵ�λ��  bool ground_position[WIDTH][HIGH] = {0}
void random_ground(int y) {

	int a, b;
	const int max_jump = 200;
	do {
		a = rand() % WIDTH;
		b = rand() % WIDTH;
		if (a > b) {    //��֤a<b
			swap(&a, &b);
		}
	} while (a == b || lastground_x[0]-a > max_jump / 6 && b - lastground_x[1] > max_jump / 6 || lastground_x[0] - b > max_jump || a - lastground_x[1] > max_jump);     //��ֹ������ɵ����޷�����ȥ
	//printf("%d %d\n", a, b);
	//���ɵ���
	for (int i = a; i < b; i++) {
		ground_position[i][y] = 1;
	}


	//���ɵڶ�����
	if (b - a < 200) {
		int a1, b1;
		do {
			a1 = rand() % WIDTH;
			b1 = rand() % WIDTH;
			if (a1 > b1) {    //��֤a<b
				swap(&a1, &b1);
			}
		} while (b1 - a1 < 200 || (b1 > a-50 && a1 -50< b));     //��֤��С �����ظ�
		for (int i = a1; i < b1; i++) {
			ground_position[i][y] = 1;
		}
	}




	/*
	//�������Ѫ��
	static int tool1_count = 0;
	if (tool1_count == 0) {
		tool1_position[0][0] = rand() % (b - a) + a;
		tool1_position[0][1] = y-20;

		tool1_count = 10;
	}
	else {
		tool1_count--;
	}
	*/


	//�������ɵ�λ��
	lastground_x[0] = a;
	lastground_x[1] = b;

	//������ɵ���
	static int enemy1_count = 0;
	if (enemy1_count >= enemy1_max) {
		enemy1_count = 0;
	}
	enemy1_position[enemy1_count][0] = rand() % (b - a) + a;
	enemy1_position[enemy1_count][1] = y - 63;
	enemy1fire1left_position[enemy1_count][0] = enemy1_position[enemy1_count][0] - 20;
	enemy1fire1left_position[enemy1_count][1] = enemy1_position[enemy1_count][1];

	rand_enemy(y, ghost_a[enemy1_count].point);


	enemy1_count++;
}

//���������������ƶ�    yΪ�����ƶ��ľ���
void everything_down(int y) {
	char_position[1] += y;
	for (int i = 0; i < enemy1_max; i++) {
		tool1_position[i][1] += y;
	}

	for (int q = HIGH - 1; q > HIGH - 1 - y; q--) {
		for (int i = 0; i < WIDTH; i++) {      //���������ש����
			ground_position[i][HIGH - 1] = 0;
		}
	}

	for (int q = HIGH - 1 - y; q >= 0; q--) {
		for (int i = 0; i < WIDTH; i++) {      //���е��������ƶ�
			ground_position[i][q + y] = ground_position[i][q];
		}
	}

	for (int i = 0; i < enemy1_max; i++) {
		enemy1_position[i][1] += y;
		enemy1fire1left_position[i][1] += y;
		ghost_a[i].y += y;
	}
}

//  �������Ѫ��
void rand_heart(int x,int y) {
	static int count = 0;
	if (count >= enemy1_max) {
		count = 0;
	}
	if (50000 / (screen_down + 500) > rand() % 100) {
		tool1_position[count][0] = x;
		tool1_position[count][1] = y;
	}
	count++;
}