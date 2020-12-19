#include"通用.h"
IMAGE chara1[2];

//角色位置信息
int char_position[2] = { 100,680 };
void drawchar() {
	loadimage(&chara1[0], _T("D:\\resource\\chara1_0.png"));
	loadimage(&chara1[1], _T("D:\\resource\\chara1_1.png"));
	putimage(char_position[0], char_position[1], &chara1[1], NOTSRCERASE);
	putimage(char_position[0], char_position[1], &chara1[0], SRCINVERT);
}

void char_control() {
	static int char1_speed = 0;    //y轴方向速度 向下为正方向
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
		if (char1_speed > 15 && ground_under(char_position[0], char_position[1] + 15)) {     //防止速度过快逃脱判定
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

//输入道具位置 1得到 0未得到
int gettool(int x, int y) {
	for (int p = -10; p < 70; p++) {         //x
		for (int q = 0; q < 50; q++) {     //y
			if (char_position[0]+p==x&&char_position[1]+q==y)
				return 1;

		}
	}
	return 0;
}


//判断是否在地上    1在地面上 0不在        模拟重力
int ground_under(int x,int y) {
	for (int i = 0; i < 20; i++) {
		for (int q = 0; q < 30; q++) {
			if (ground_position[x + 20 + q][y + 50 + i])
				return 1;
		}

	}
	return 0;
}

//判断角色上方是否有天花板  1为有 0为无
int ground_below() {
	for (int i = 0; i < 10; i++) {
		for (int q = 0; q < 30; q++) {
			if (ground_position[char_position[0] + 20 + q][char_position[1] - i])
				return 1;
		}
	}
	return 0;
}
//判断角色旁边是否有遮挡  1为有 0为无
int ground_left(void){
	//判断左边
	for (int p = 0; p < 10; p++) {         //x
		for (int q = -5; q < 50; q++) {     //y
			if (ground_position[char_position[0] - p][char_position[1] + q])
				return 1;

		}
	}

	return 0;
}

//判断右边
int ground_right(void) {
	for (int p = 0; p < 10; p++) {         //x
		for (int q = -5; q < 50; q++) {     //y
			if (ground_position[char_position[0] + 60 + p][char_position[1] + q])
				return 1;

		}
	}

	return 0;
}

//判断死亡  返回-1为死亡
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