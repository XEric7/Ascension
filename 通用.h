//��ź궨�壬��������

#pragma once
#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<Windows.h>
#include<stdlib.h>
#define LEVEL 200           //���
#define WIDTH 1500
#define HIGH 800
#define enemy1_max 5
#define blood_max 5

//��������
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


//��������
extern bool ground_position[WIDTH][HIGH];      //   �ذ�λ����Ϣ    [0]:x_position  [1]:����
extern int enemy1_position[enemy1_max][2];     //enemy1λ��
extern int enemy1fire1left_position[enemy1_max][2];     //enemy1 fireλ�� ����   x y����
extern int enemy1fire1right_position[enemy1_max][2];       //�ҷ��� x y����
extern int char_position[2];         //��ɫλ����Ϣ