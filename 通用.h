//��ź궨�壬��������

#pragma once
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include "atlstr.h"
#define LEVEL 200           //���
#define WIDTH 1500
#define HIGH 800
#define enemy1_max 5

//��������
void drawbackground(void);
int ground_under(int x, int y);
int ground_below();
void drawground();
void char_control();

void everything_down(int y);
int die(void);
void init();
void swap(int* a, int* b);
void enemy_control();
void drawchar();
void drawenemy1(void);
void drawheart(int blood);
int ground_left(void);
int ground_right(void);
void drawtool1(void);
int gettool(int x, int y);
void getimage_char();


//��������
extern bool ground_position[WIDTH][HIGH];      //   �ذ�λ����Ϣ    [0]:x_position  [1]:����
extern int enemy1_position[enemy1_max][2];     //enemy1λ��
extern int enemy1fire1left_position[enemy1_max][2];     //enemy1 fireλ�� ����   x y����
//extern int enemy1fire1right_position[enemy1_max][2];       //�ҷ��� x y����
extern int char_position[2];         //��ɫλ����Ϣ


//Դ.cpp
extern int lastground_x[2];
void random_ground(int y);
extern int screen_down;    //��Ļ�ܹ������ƶ��ľ���  ������������� �Ѷ�
void rand_heart(int x, int y);
extern int char_blood_max;


//����.cpp
void rand_enemy(int ground_y, struct enemy* enemy);
void enemy_init();
int ghost_beat();
int enemy1_beat();
struct enemy {
	int x;          //x����
	int y;			//y����
	int high;       //���˸߶�
	int blood_max;  //���Ѫ��
	int blood;		//��ǰѪ��
	struct enemy* point;
	int speed;      //����Ϊ������
};

extern struct enemy ghost_a[enemy1_max];


//���.cpp
extern void char_init();