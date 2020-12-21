#include"通用.h"
void getimage_enemy(void);
void getimage_enemy();
void ghost();


//ghost
IMAGE ghost_p[2][2];
struct enemy ghost_a[enemy1_max];

void enemy_init() {
	getimage_enemy();
	for (int i = 0; i < enemy1_max; i++) {
		ghost_a[i].high = 50;
		ghost_a[i].x = WIDTH;
		ghost_a[i].y = HIGH;
		ghost_a[i].point = &ghost_a[i];
	}
}

void enemy_control() {
	//初始代码
	//int enemy1fire1left_position[enemy1_max][2] = { 0 };
	static int enemyfire1_speed = 5;
	if (screen_down > enemyfire1_speed * 1000) {
		enemyfire1_speed++;
	}
	for (int i = 0; i < enemy1_max; i++) {
		if (enemy1fire1left_position[i][0] < -40 && enemy1_position[i][0]>200) {
			enemy1fire1left_position[i][0] = enemy1_position[i][0] - 20;
		}
		else if (enemy1fire1left_position[i][0] < -100) {
			enemy1fire1left_position[i][0] = enemy1_position[i][0] - 20;
		}
		enemy1fire1left_position[i][0] -= enemyfire1_speed;
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
}

int enemy_go(struct enemy*enemy,int speed) {
	enemy->x += speed;
	if (ground_position[enemy->x][enemy->y - enemy->high] == 0) {
		speed= -speed;
		enemy->x += speed;
	}
	return speed;
}

void ghost() {
	for (int i = 0; i < enemy1_max; i++) {
		putimage(ghost_a[i].x, ghost_a[i].y, &ghost_p[0][1], NOTSRCERASE);
		putimage(ghost_a[i].x, ghost_a[i].y, &ghost_p[0][0], SRCINVERT);	
	}
}