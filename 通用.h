//存放宏定义，函数声明

#pragma once
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#include<string.h>
#define LEVEL 200           //层高
#define WIDTH 1500
#define HIGH 800
#define enemy1_max 5
#define blood_max 5

//函数声明
void drawbackground(void);
int ground_under(int x, int y);
int ground_below();
void drawground();
void char_control();
void random_ground(int y, int x[2]);
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


//变量声明
extern bool ground_position[WIDTH][HIGH];      //   地板位置信息    [0]:x_position  [1]:长度
extern int enemy1_position[enemy1_max][2];     //enemy1位置
extern int enemy1fire1left_position[enemy1_max][2];     //enemy1 fire位置 左方向   x y坐标
extern int enemy1fire1right_position[enemy1_max][2];       //右方向 x y坐标
extern int char_position[2];         //角色位置信息