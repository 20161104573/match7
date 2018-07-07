#pragma once
#ifndef _STUDENT
#define _STUDENT

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

struct Player
{
	int snum;
	char name[20];
	char sex[5];
	char act[30];
	char acte[30];
	char pacte[30];
	char sclass[20];
	long num;
	float grade;
};

struct Rater

{
	char name[20];
	char sex[5];
	long num;
};
struct Rater r[100];
struct Player p[100];
struct Player sing[100];
struct Player dance[100];
extern void p_show();
extern void r_show();
extern int samount;
extern int damount;
extern int menu_select();
extern void score();
extern void show();
extern void placing();
extern void save();
#endif