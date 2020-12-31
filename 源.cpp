#include"ͨ��.h"

int showscore();

//����������x y˳�򣨲�ͬ�봫ͳ���к��У�
#pragma comment(lib,"Winmm.lib")

struct Rank {
	char name[20];    //����
	int score;        //����
	int blood;        //Ѫ��
	bool randmap;     //�����ͼ
	int rank;         //��������
	int right;        //Ч����
	struct Rank* next;
};

//λ����Ϣ

bool ground_position[WIDTH][HIGH];      //   �ذ�λ����Ϣ    [0]:x_position  [1]:����
int enemy1_position[enemy1_max][2];     //enemy1λ��
int enemy1fire1left_position[enemy1_max][2];      //enemy1 fireλ�� ����   x y����
//int enemy1fire1right_position[enemy1_max][2] = { 0 };        //�ҷ��� x y����
int tool1_position[enemy1_max][2];  //����һλ��
int screen_down;    //��Ļ�ܹ������ƶ��ľ���  ������������� �Ѷ�
int startgame();    //��ʾ��ʼ��Ϸ�˵�
void showrank();     //�鿴���а�
void setmusic();     //��������
void setgame();     //������Ϸ����
struct Rank new_rank;  //�浵
void about();

int lastground_x[2] = { 10,WIDTH - 10 };   //������һ���ص�λ��
int char_blood_max = 5;

int main() {
	BEGIN:
	srand(1);
	new_rank.randmap = 0;
	//��ʼ������
	START:
	init();
	if (startgame()) {
		goto START;
	}
	getimage_char();
	int blood = char_blood_max;   //Ѫ��ϵͳ
	int blood_pause = 0;     //�޵�ʱ��



	int top_ground = 750;   //��¼���Ϸ��ذ��y����  �������ɵ���
	while (1) {
		//��ͼ
		drawbackground();
		char_control();    //��ɫ����

		enemy_control();    //���˿���
		drawenemy1();
		drawheart(blood);
		drawground();
		drawtool1();
		FlushBatchDraw();

		

		//����һ�ж�
		if (blood < char_blood_max) {
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

		if (blood_pause) {
			blood_pause--;
		}
		else {
			int blood_substract = die();
			if (blood_substract > 0) {
				blood -= blood_substract;
				blood_pause = 25;
				if (blood <= 0) {
					break;
				}
			}
		}
		
	}
	FlushBatchDraw();
	if (showscore() == 1) {
		goto BEGIN;
	}
	return 0;
}

//��ʼ�� ֻ�ڿ�ʼʱִ��
void init() {
	char_init();
	mciSendString(_T("open  bkmusic.mp3 alias bkmusic") ,NULL, 0, NULL);
	mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
	for (int m = 0; m < WIDTH; m++) {
		for (int n = 0; n < HIGH; n++) {
			ground_position[m][n] = 0;
		}
	}
	for (int i = 0; i < enemy1_max; i++) {
		enemy1_position[i][0] = 0;
		enemy1_position[i][1] = 0;
		enemy1fire1left_position[i][0] = 0;
		enemy1fire1left_position[i][1] = 0;
		tool1_position[i][0] = 0;
		tool1_position[i][1] = 0;
		screen_down = 0;
	}
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
		//enemy1fire1right_position[i][1] = HIGH;
	}

	//Ѫ��
	for (int i = 0; i < enemy1_max; i++) {
		tool1_position[i][0] = WIDTH;
		tool1_position[i][1] = HIGH;
	}

	enemy_init();
	for (int i = 0; i < 20; i++) {
		new_rank.name[i] = 0;
	}
}

//����1��������
int startgame() {
	IMAGE start;
	loadimage(&start, _T("picture\\start.png"), WIDTH, HIGH);
	while (1) {
		
		putimage(0, 0, &start);
		FlushBatchDraw();
		if ((GetKeyState(VK_SPACE) & 0x8000)) {
			break;
		}
		else if (GetKeyState(0x50) & 0x8000) {   //P:���а�
			showrank();
			return 1;
		}
		else if (GetKeyState(0x4D) & 0x8000) {   //M:����
			setmusic();
		}
		else if (GetKeyState(0x4C) & 0x8000) {   //L����Ϸ����
			setgame();
		}
		else if (GetKeyState(0x41) & 0x8000) {   //����
			about();
		}
	}
	return 0;
}


void setmusic() {
	IMAGE setmusic;
	loadimage(&setmusic, _T("picture\\setmusic.png"), WIDTH, HIGH);
	while (1) {
		putimage(0, 0, &setmusic);
		if ((GetKeyState(0x30) & 0x8000)|| (GetKeyState(0x60) & 0x8000)) {   //0
			mciSendString(_T("close bkmusic"), NULL, 0, NULL);
			mciSendString(_T("open bkmusic.mp3 alias bkmusic"), NULL, 0, NULL);
			mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
		}
		else if ((GetKeyState(0x31) & 0x8000)|| (GetKeyState(0x61) & 0x8000)) {   //1:Es Rappelt Im Karton
			mciSendString(_T("close bkmusic"), NULL, 0, NULL);
			mciSendString(_T("open music\\bkmusic1.mp3 alias bkmusic"), NULL, 0, NULL);
			mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
		}
		else if ((GetKeyState(0x32) & 0x8000) || (GetKeyState(0x62) & 0x8000)) {   //2:Hello
			mciSendString(_T("close bkmusic"), NULL, 0, NULL);
			mciSendString(_T("open music\\bkmusic2.mp3 alias bkmusic"), NULL, 0, NULL);
			mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
		}
		else if ((GetKeyState(0x33) & 0x8000) || (GetKeyState(0x63) & 0x8000)) {    //3: Pacific Rim
			mciSendString(_T("close bkmusic"), NULL, 0, NULL);
			mciSendString(_T("open music\\bkmusic3.mp3 alias bkmusic"), NULL, 0, NULL);
			mciSendString(_T("play bkmusic repeat"), NULL, 0, NULL);
		}
		else if ((GetKeyState(0x1B) & 0x8000)) {     //Esc: �˳�
			return;
		}
		FlushBatchDraw();
	}
}


void setgame() {
	IMAGE setgame;
	loadimage(&setgame, _T("picture\\setgame.png"), WIDTH, HIGH);
	while (1) {
		putimage(0, 0, &setgame);
		
		if ((GetKeyState(0x30) & 0x8000) || (GetKeyState(0x60) & 0x8000)) {   //0:   �����ͼ
			srand(time(NULL));
			new_rank.randmap = 1;
		}
		for (int i = 1; i <= 9; i++) {
			int a = i + 48;
			int b = i + 96;
			if ((GetKeyState(a) & 0x8000) || (GetKeyState(b) & 0x8000)) {   //����Ѫ��
				char_blood_max = i;
			}
		}
		drawheart(char_blood_max);
		FlushBatchDraw();
		if ((GetKeyState(0x1B) & 0x8000)) {   //Esc:�˳�
			break;
		}
	}
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

	for (int i = 0; i < char_blood_max; i++) {
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
	} while (b-a<100 || lastground_x[0]-a > max_jump / 6 && b - lastground_x[1] > max_jump / 6 || lastground_x[0] - b > max_jump || a - lastground_x[1] > max_jump);     //��ֹ������ɵ����޷�����ȥ
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

void showrank() {
	//�ļ���ȡ
	FILE* rk;
	rk = fopen("rank", "r");
	int count = 0;
	struct Rank* head = NULL;
	struct Rank* prank;
	if (rk != NULL) {
		while (1) {
			while ((prank = (struct Rank*)malloc(sizeof(struct Rank))) == NULL);
			if (fread(prank, sizeof(struct Rank), 1, rk) == 0) {
				break;
			}
			
			//���Ч����
			int right = 0;
			for (int i = 0; i < 20; i++) {
				right += prank->name[i] ^ prank->rank;
			}
			right += (prank->blood + prank->randmap);

			if (right != prank->right) {
				continue;
			}
			
			count++;
			if (count == 1) {
				prank->next = NULL;
				head = prank;
			}
			else if (prank->rank >= head->rank) {
				prank->next = head;
				head = prank;
			}
			else {
				struct Rank* ptr1 = head;
				struct Rank* ptr2 = head->next;
				while (1) {
					if (ptr2 == NULL) {
						ptr1->next = prank;
						prank->next = NULL;
						break;
					}
					if (ptr1->rank >= prank->rank && prank->rank >= ptr2->rank) {
						ptr1->next = prank;
						prank->next = ptr2;
						break;
					}
					ptr1 = ptr1->next;
					ptr2 = ptr2->next;
				}
			}
		}
		fclose(rk);
	}


	//���а����
	IMAGE img_rank;
	loadimage(&img_rank, _T("picture\\rank.png"), WIDTH, HIGH);
	setbkmode(TRANSPARENT);
		putimage(0, 0, &img_rank);
		if (count == 0) {   //�����а���Ϣ
			settextstyle(50, 0, _T("Consolas"));
			settextcolor(BLACK);
			outtextxy(600,HIGH/2,_T("�����а���Ϣ"));
		}
		else {     //�������
			prank = head;
			settextstyle(40, 0, _T("Consolas"));
			settextcolor(BLACK);
			TCHAR top_rank[3];
			//TCHAR outname[20];   //����
			TCHAR outscore[10];  //����
			TCHAR outblood[2];   //Ѫ��
			for (int i = 1; i <= count; i++) {   //������а� �Ҳ�����������뷶Χ
				_stprintf(top_rank, _T("%d"), i);
				//_stprintf(outname, L"%s", prank->name);
				USES_CONVERSION;
				TCHAR* outname = A2T(prank->name);    //ת��δunicode
				_stprintf(outscore, _T("%d"), prank->score);
				_stprintf(outblood, _T("%d"), prank->blood);
				_stprintf(top_rank, _T("%d"), i);
				outtextxy(50, 200+50*i, top_rank);   //����
				outtextxy(230, 200 + 50 * i, outname);   //����
				outtextxy(980, 200 + 50 * i, outscore);     //����
				outtextxy(1200, 200 + 50 * i, outblood);
				if (prank->randmap) {   //��ͼ���
					outtextxy(1350, 200 + 50 * i, _T("��"));
				}
				else {
					outtextxy(1350, 200 + 50 * i, _T("��"));
				}
  				prank = prank->next;
			}
		}
		FlushBatchDraw();
		while (1) {
			if ((GetKeyState(0x1B) & 0x8000)) {
				break;
			}
		}
}


//����1�����¿�ʼ��Ϸ
int showscore() {
	IMAGE img_gameover;
	loadimage(&img_gameover, _T("picture\\gameover0.png"), WIDTH, HIGH);
	setbkmode(TRANSPARENT);
	putimage(0, 0, &img_gameover);
	settextstyle(50, 0, _T("Consolas"));
	settextcolor(RED);
	TCHAR outscore[10];
	_stprintf(outscore, _T("%d"), screen_down);
	outtextxy(310, 250, outscore);
	FlushBatchDraw();
	char input;
	while (_getch() != 13);
	loadimage(&img_gameover, _T("picture\\gameover1.png"), WIDTH, HIGH);
	putimage(0, 0, &img_gameover);
	outtextxy(310, 250, outscore);
	FlushBatchDraw();
	for (int i = 0; i < 20; i++) {
		putimage(0, 0, &img_gameover);
		outtextxy(310, 250, outscore);
		input = _getch();

		if (input == 0x0D) {
			break;
		}
		else if (input == 0x08) {
			if (i == 0) {
				i--;
				continue;
			}
			else {
				new_rank.name[--i] = 0;
				i--;
			}
		}
		else {
			new_rank.name[i] = input;
		}
		USES_CONVERSION;
		TCHAR* outname = A2T(new_rank.name);
		outtextxy(200, 500, outname);   //����
		FlushBatchDraw();
	}
	//�������
	new_rank.score = screen_down;
	new_rank.blood = char_blood_max;
	new_rank.rank = screen_down / char_blood_max;
	if (new_rank.randmap) {
		new_rank.rank *= 1.2;
	}

	//����Ч����
	new_rank.right = 0;
	for (int i = 0; i < 20; i++) {
		new_rank.right += new_rank.name[i] ^ new_rank.rank;
	}
	new_rank.right += (new_rank.blood + new_rank.randmap);

	//д�����

	FILE* rk;
	if (((rk = fopen("rank", "a")) != NULL)) {
		if ((fwrite(&new_rank, sizeof(struct Rank), 1, rk) == 1)) {
			printf("\n���а�д��ɹ�\n");
		}
		else {
			printf("\n���а�д��ʧ��\n");
		}
		fclose(rk);
	}
	else {
		printf("\n���а�д��ʧ��\n");
	}

	return 1;
}

void about() {
	IMAGE img_about;
	loadimage(&img_about, _T("picture\\about.png"), WIDTH, HIGH);
	setbkmode(TRANSPARENT);
	settextstyle(50, 0, _T("Consolas"));
	settextcolor(RED);
	for (int i = 0; i < 1100; i++) {
		putimage(0, 0, &img_about);
		outtextxy(310, HIGH-i/2, _T("�����ˣ����ż�"));
		FlushBatchDraw();
	}
	for (int i = 0; i < 1100; i++) {
		putimage(0, 0, &img_about);
		outtextxy(310, HIGH - 1100 / 2, _T("�����ˣ����ż�"));
		outtextxy(800, HIGH - i / 2, _T("������"));
		FlushBatchDraw();
	}
	for (int i = 0; i < 900; i++) {
		settextstyle(50, 0, _T("Consolas"));
		putimage(0, 0, &img_about);
		outtextxy(310, HIGH - 1100 / 2, _T("�����ˣ����ż�"));
		outtextxy(800, HIGH - 1100 / 2, _T("������"));
		settextstyle(100, 0, _T("Consolas"));
		outtextxy(500, HIGH-i/2, _T("�ر���л"));
		FlushBatchDraw();
	}
	
	for (int i = 0; i < 600; i++) {
		settextstyle(50, 0, _T("Consolas"));
		putimage(0, 0, &img_about);
		outtextxy(310, HIGH - 1100 / 2, _T("�����ˣ����ż�"));
		outtextxy(800, HIGH - 1100 / 2, _T("������"));
		settextstyle(100, 0, _T("Consolas"));
		outtextxy(500, HIGH - 900 / 2, _T("�ر���л"));
		settextstyle(50, 0, _T("Consolas"));
		outtextxy(310, HIGH-i/2, _T("��Ϸ��ϯ����٣�������"));
		FlushBatchDraw();
	}

	for (int i = 0; i < 400; i++) {
		settextstyle(50, 0, _T("Consolas"));
		putimage(0, 0, &img_about);
		outtextxy(310, HIGH - 1100 / 2, _T("�����ˣ����ż�"));
		outtextxy(800, HIGH - 1100 / 2, _T("������"));
		settextstyle(100, 0, _T("Consolas"));
		outtextxy(500, HIGH - 900 / 2, _T("�ر���л"));
		settextstyle(50, 0, _T("Consolas"));
		outtextxy(310, HIGH - 600 / 2, _T("��Ϸ��ϯ����٣�������"));
		settextstyle(40, 0, _T("Consolas"));
		outtextxy(310, HIGH-i/2, _T("��Ŀ��ַ��https://github.com/XEric7/Ascension"));
		outtextxy(600, HIGH+60-i/2, _T("��ӭ��������"));
		FlushBatchDraw();
	}

	while (1) {
		if ((GetKeyState(0x1B) & 0x8000))
			break;
	}
}