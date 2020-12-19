#include"ͨ��.h"
IMAGE chara1[2];

//��ɫλ����Ϣ
int char_position[2] = { 100,680 };
void drawchar() {
	loadimage(&chara1[0], _T("chara1_0.png"));
	loadimage(&chara1[1], _T("chara1_1.png"));
	putimage(char_position[0], char_position[1], &chara1[1], NOTSRCERASE);
	putimage(char_position[0], char_position[1], &chara1[0], SRCINVERT);
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
		if ((GetAsyncKeyState(VK_SPACE) & 0x8000)) {
			char1_speed = -15;
		}
	}
	else {
		if (speedwait++ % 2 == 0)
			char1_speed++;
		if (char1_speed > 15 && ground_under(char_position[0], char_position[1] + 15)) {     //��ֹ�ٶȹ��������ж�
			char1_speed =15;
		}
	}
	char_position[1] += char1_speed;

	if (ground_left() == 0) {
		if ((GetAsyncKeyState(0x41) & 0x8000)) //a
			char_position[0] -= 5;
	}
	if(ground_right()==0){
		if ((GetAsyncKeyState(0x44) & 0x8000)) //d
			char_position[0] += 5;
	}
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
	for (int i = 0; i < 20; i++) {
		for (int q = 0; q < 30; q++) {
			if (ground_position[x + 20 + q][y + 50 + i])
				return 1;
		}

	}
	return 0;
}

//�жϽ�ɫ�Ϸ��Ƿ����컨��  1Ϊ�� 0Ϊ��
int ground_below() {
	for (int i = 0; i < 10; i++) {
		for (int q = 0; q < 30; q++) {
			if (ground_position[char_position[0] + 20 + q][char_position[1] - i])
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
		return blood_max;
	}
	for (int p = -30; p < 65;p++) {
		for (int q=-10;q<60;q++) {
			for (int i = 0; i < enemy1_max; i++) {
				if (char_position[0] + p == enemy1fire1left_position[i][0] && char_position[1] + q == enemy1fire1left_position[i][1])
					return 1;
			}
			
		}
	}
	return 0;
}