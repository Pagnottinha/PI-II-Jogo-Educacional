#define _CRT_SECURE_NO_WARNINGS
#include "../../Background.h"
#include <stdio.h>


typedef struct {
	char path[5][50];
	int size;
	Background background;
} Backgrounds;

int pegarBackgrounds(Backgrounds* back);