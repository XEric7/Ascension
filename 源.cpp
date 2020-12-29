#include"通用.h"

int showscore();

//数组坐标以x y顺序（不同与传统先行后列）
#pragma comment(lib,"Winmm.lib")




struct Rank {
	char name[20];    //名字
	int score;        //分数
	int blood;        //血量
	bool randmap;     //随机地图
	int rank;         //用于排序
	int right;        //效验码
	struct Rank* next;
};

//位置信息

bool ground_position[WIDTH][HIGH];      //   地板位置信息    [0]:x_position  [1]:长度
int enemy1_position[enemy1_max][2];     //enemy1位置
int enemy1fire1left_position[enemy1_max][2];      //enemy1 fire位置 左方向   x y坐标
//int enemy1fire1right_position[enemy1_max][2] = { 0 };        //右方向 x y坐标
int tool1_position[enemy1_max][2];  //道具一位置
int screen_down;    //屏幕总共向下移动的距离  可用来计算分数 难度
int startgame();    //显示开始游戏菜单
void showrank();     //查看排行榜
void setmusic();     //设置音乐
void setgame();     //设置游戏参数
struct Rank new_rank;  //存档

int lastground_x[2] = { 10,WIDTH - 10 };   //保存上一个地的位置
int char_blood_max = 5;

int main() {
	BEGIN:
	new_rank.randmap = 0;
	//初始化界面
	START:
	init();
	if (startgame()) {
		goto START;
	}
	getimage_char();
	int blood = char_blood_max;   //血量系统
	int blood_pluse = 0;     //无敌时间



	int top_ground = 750;   //记录最上方地板的y坐标  用于生成地面
	while (1) {
		//绘图
		drawbackground();
		char_control();    //角色控制

		enemy_control();    //敌人控制
		drawenemy1();
		drawheart(blood);
		drawground();
		drawtool1();
		FlushBatchDraw();

		

		//道具一判定
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

		//屏幕向下移动
		if (char_position[1] < HIGH / 3) {    
			everything_down(10);
			screen_down += 10;
			top_ground += 10;
		}

		////地图测试代码
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
	FlushBatchDraw();
	if (showscore() == 1) {
		goto BEGIN;
	}
	return 0;
}

//初始化 只在开始时执行
void init() {
	char_init();
	srand(1);
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
	for (int i = 10; i < WIDTH - 10; i++) {     //绘制最下方的地板
		ground_position[i][750] = 1;
	}

	////测试代码
	//for (int i = 500; i < 1200 - 10; i++) {     //绘制最下方的地板
	//	ground_position[i][680] = 1;
	//}
	// 初始化怪1的位置  fire 位置
	for (int i = 0; i < enemy1_max;i++) {
		enemy1_position[i][1] = HIGH;
		enemy1fire1left_position[i][1] = HIGH;
		//enemy1fire1right_position[i][1] = HIGH;
	}

	//血包
	for (int i = 0; i < enemy1_max; i++) {
		tool1_position[i][0] = WIDTH;
		tool1_position[i][1] = HIGH;
	}

	enemy_init();
}

//返回1重新运行
int startgame() {
	IMAGE start;
	loadimage(&start, _T("picture\\start.png"), WIDTH, HIGH);
	while (1) {
		
		putimage(0, 0, &start);
		FlushBatchDraw();
		if ((GetKeyState(VK_SPACE) & 0x8000)) {
			break;
		}
		else if (GetKeyState(0x50) & 0x8000) {   //P:排行榜
			showrank();
			return 1;
		}
		else if (GetKeyState(0x4D) & 0x8000) {   //M:音乐
			setmusic();
		}
		else if (GetKeyState(0x4C) & 0x8000) {   //L：游戏参数
			setgame();
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
		else if ((GetKeyState(0x1B) & 0x8000)) {     //Esc: 退出
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
		
		if ((GetKeyState(0x30) & 0x8000) || (GetKeyState(0x60) & 0x8000)) {   //0:   随机地图
			srand(time(NULL));
			new_rank.randmap = 1;
		}
		for (int i = 1; i <= 9; i++) {
			int a = i + 48;
			int b = i + 96;
			if ((GetKeyState(a) & 0x8000) || (GetKeyState(b) & 0x8000)) {   //设置血量
				char_blood_max = i;
			}
		}
		drawheart(char_blood_max);
		FlushBatchDraw();
		if ((GetKeyState(0x1B) & 0x8000)) {   //Esc:退出
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




//显示初始地面
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




//生成随机地面      输入要生成的高度 生成的位置  bool ground_position[WIDTH][HIGH] = {0}
void random_ground(int y) {

	int a, b;
	const int max_jump = 200;
	do {
		a = rand() % WIDTH;
		b = rand() % WIDTH;
		if (a > b) {    //保证a<b
			swap(&a, &b);
		}
	} while (b-a<100 || lastground_x[0]-a > max_jump / 6 && b - lastground_x[1] > max_jump / 6 || lastground_x[0] - b > max_jump || a - lastground_x[1] > max_jump);     //防止随机生成导致无法跳上去
	//printf("%d %d\n", a, b);
	//生成地面
	for (int i = a; i < b; i++) {
		ground_position[i][y] = 1;
	}


	//生成第二地面
	if (b - a < 200) {
		int a1, b1;
		do {
			a1 = rand() % WIDTH;
			b1 = rand() % WIDTH;
			if (a1 > b1) {    //保证a<b
				swap(&a1, &b1);
			}
		} while (b1 - a1 < 200 || (b1 > a-50 && a1 -50< b));     //保证大小 并不重复
		for (int i = a1; i < b1; i++) {
			ground_position[i][y] = 1;
		}
	}




	/*
	//随机生成血包
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


	//保存生成的位置
	lastground_x[0] = a;
	lastground_x[1] = b;

	//随机生成敌人
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

//将所有物体向下移动    y为向下移动的距离
void everything_down(int y) {
	char_position[1] += y;
	for (int i = 0; i < enemy1_max; i++) {
		tool1_position[i][1] += y;
	}

	for (int q = HIGH - 1; q > HIGH - 1 - y; q--) {
		for (int i = 0; i < WIDTH; i++) {      //将最下面的砖清零
			ground_position[i][HIGH - 1] = 0;
		}
	}

	for (int q = HIGH - 1 - y; q >= 0; q--) {
		for (int i = 0; i < WIDTH; i++) {      //所有地面向下移动
			ground_position[i][q + y] = ground_position[i][q];
		}
	}

	for (int i = 0; i < enemy1_max; i++) {
		enemy1_position[i][1] += y;
		enemy1fire1left_position[i][1] += y;
		ghost_a[i].y += y;
	}
}

//  随机生成血包
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
	//文件读取
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
			
			//检测效验码
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


	//排行榜绘制
	IMAGE img_rank;
	loadimage(&img_rank, _T("picture\\rank.png"), WIDTH, HIGH);
	setbkmode(TRANSPARENT);
		putimage(0, 0, &img_rank);
		if (count == 0) {   //无排行榜信息
			settextstyle(50, 0, _T("Consolas"));
			settextcolor(BLACK);
			outtextxy(600,HIGH/2,_T("无排行榜信息"));
		}
		else {     //链表输出
			prank = head;
			settextstyle(40, 0, _T("Consolas"));
			settextcolor(BLACK);
			TCHAR top_rank[3];
			//TCHAR outname[20];   //名字
			TCHAR outscore[10];  //分数
			TCHAR outblood[2];   //血量
			for (int i = 1; i <= count; i++) {   //输出排行榜 且不超出最大输入范围
				_stprintf(top_rank, _T("%d"), i);
				//_stprintf(outname, L"%s", prank->name);
				USES_CONVERSION;
				TCHAR* outname = A2T(prank->name);    //转换未unicode
				_stprintf(outscore, _T("%d"), prank->score);
				_stprintf(outblood, _T("%d"), prank->blood);
				_stprintf(top_rank, _T("%d"), i);
				outtextxy(50, 200+50*i, top_rank);   //排名
				outtextxy(230, 200 + 50 * i, outname);   //名字
				outtextxy(980, 200 + 50 * i, outscore);     //分数
				outtextxy(1200, 200 + 50 * i, outblood);
				if (prank->randmap) {   //地图随机
					outtextxy(1350, 200 + 50 * i, _T("是"));
				}
				else {
					outtextxy(1350, 200 + 50 * i, _T("否"));
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


//返回1：重新开始游戏
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
		outtextxy(200, 500, outname);   //名字
		FlushBatchDraw();
	}
	//计算分数
	new_rank.score = screen_down;
	new_rank.blood = char_blood_max;
	new_rank.rank = screen_down / char_blood_max;
	if (new_rank.randmap) {
		new_rank.rank *= 1.2;
	}

	//计算效验码
	new_rank.right = 0;
	for (int i = 0; i < 20; i++) {
		new_rank.right += new_rank.name[i] ^ new_rank.rank;
	}
	new_rank.right += (new_rank.blood + new_rank.randmap);

	//写入分数

	FILE* rk;
	if (((rk = fopen("rank", "a")) != NULL)) {
		if ((fwrite(&new_rank, sizeof(struct Rank), 1, rk) == 1)) {
			printf("\n排行榜写入成功\n");
		}
		else {
			printf("\n排行榜写入失败\n");
		}
		fclose(rk);
	}
	else {
		printf("\n排行榜写入失败\n");
	}

	return 1;
}