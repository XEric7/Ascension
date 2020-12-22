#include"通用.h"
void getimage_enemy(void);
void getimage_enemy();
void ghost();
void enemy_go(struct enemy* enemy);


//ghost
IMAGE ghost_p[2][2];
struct enemy ghost_a[enemy1_max];

void enemy_init() {
	getimage_enemy();
	for (int i = 0; i < enemy1_max; i++) {
		ghost_a[i].high = 45;
		ghost_a[i].x = WIDTH;
		ghost_a[i].y = HIGH;
		ghost_a[i].point = &ghost_a[i];
		ghost_a[i].speed = (i==0? 1:ghost_a[i-1].speed);
		ghost_a[i].blood_max = ghost_a[i].blood = 2;
	}
}

void enemy_control() {
	//初始代码
	//int enemy1fire1left_position[enemy1_max][2] = { 0 };
	static int enemyfire1_speed = 5;
	if (screen_down > enemyfire1_speed * 1000) {
		enemyfire1_speed++;
	}
	/*static int ghost_speed[enemy1_max] = {1};
	for (int i = 1; i < enemy1_max; i++) {
		ghost_speed[i] = -ghost_speed[i - 1];
	}*/
	for (int i = 0; i < enemy1_max; i++) {
		if (enemy1fire1left_position[i][0] < -40 && enemy1_position[i][0]>200) {
			enemy1fire1left_position[i][0] = enemy1_position[i][0] - 20;
		}
		else if (enemy1fire1left_position[i][0] < -100) {
			enemy1fire1left_position[i][0] = enemy1_position[i][0] - 20;
		}
		enemy1fire1left_position[i][0] -= enemyfire1_speed;
		enemy_go(ghost_a[i].point);
	}

	//ghost
	ghost();
}


//导入图片
void getimage_enemy() {
	//ghost
	loadimage(&ghost_p[0][0], _T("picture\\enemy_ghost\\0_0.png"));
	loadimage(&ghost_p[0][1], _T("picture\\enemy_ghost\\0_1.png"));
	loadimage(&ghost_p[1][0], _T("picture\\enemy_ghost\\1_0.png"));
	loadimage(&ghost_p[1][1], _T("picture\\enemy_ghost\\1_1.png"));
}

//生成随机敌人 high高度  struct 敌人
void rand_enemy(int ground_y, struct enemy* enemy) {
	enemy->y = ground_y - enemy->high;
	enemy->x = rand() % (lastground_x[1] - lastground_x[0]) + lastground_x[0];
	enemy->blood = enemy->blood_max;
}

void enemy_go(struct enemy*enemy) {
	enemy->x += enemy->speed;
	if (ground_position[enemy->x][enemy->y + enemy->high] == 0) {
		enemy->speed = -enemy->speed;
		enemy->x += enemy->speed;
	}
}

void ghost() {
	for (int i = 0; i < enemy1_max; i++) {
		int dir = (ghost_a[i].speed >= 0 ? 1 : 0);
		if (ghost_a[i].blood > 0) {
			putimage(ghost_a[i].x, ghost_a[i].y, &ghost_p[dir][1], NOTSRCERASE);
			putimage(ghost_a[i].x, ghost_a[i].y, &ghost_p[dir][0], SRCINVERT);
		}
	}
}


int ghost_beat() {
	for (int i = 0; i < enemy1_max; i++) {
		if (ghost_a[i].blood <= 0) {
			continue;
		}
		for (int p = 15; p < 65; p++) {
			for (int q = -10; q < 60; q++) {
				if (char_position[0] + p == ghost_a[i].x && char_position[1] + q == ghost_a[i].y) {
					if (p < 40) {
						char_position[0] += 50;
					}
					else {
						char_position[0] -= 50;
					}
					char_position[1] -= 50;
					return 1;
				}
			}
		}
	}
	return 0;
}

int enemy1_beat() {
	for (int p = 0; p < 65; p++) {
		for (int q = -10; q < 60; q++) {
			for (int i = 0; i < enemy1_max; i++) {
				if (char_position[0] + p == enemy1fire1left_position[i][0] && char_position[1] + q == enemy1fire1left_position[i][1])
					return 1;
			}

		}
	}
	return 0;
}