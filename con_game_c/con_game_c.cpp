﻿#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "locale.h"
#include "string.h"
#include "windows.h"
#include "math.h"
#define levels 1
FILE* f;

int dai_chislo(int a, int b) { // Функция ввода числа
	int k, f = 1;
	printf("Введите число от %d до %d: ", a, b);
	do {
		while (scanf("%d", &k) != 1) {
			while (getchar() != '\n');
			printf("Ошибка. Введите число от %d до %d: ", a, b);
		}
		if (k <= b && k >= a) f = 0;
		else {
			printf("Ошибка. Введите число от %d до %d: ", a, b);
		}
	} while (f);
	while (getchar() != '\n');
	return k;
}
int init_map(int map[20][20], int level_num, int* m, int* n) {
	char fname[20] = "level", flevel[5], ch;
	int i, j;
	strcat(fname, _itoa(level_num, flevel, 10));
	strcat(fname, ".txt");
	f = fopen(fname, "r");
	if (f == NULL) return -1;
	i = j = 0;
	while (fscanf(f, "%c", &ch) != EOF) {
		if (ch == '9') map[i][j] = 9;
		else if (ch == 's') map[i][j] = 1;
		else if (ch == 'k') map[i][j] = 8;
		else if (ch == 'o') map[i][j] = 2;
		else if (ch == ' ') map[i][j] = 0;
		else if (ch == '\n') { i++; j = -1;}
		j++;
	}
	*(m) = i + 1;
	*(n) = j;
	fclose(f);
	return 0;
}

void print_map(int map[20][20], int m, int n){
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (map[i][j] == 9) printf("####");
			else if (map[i][j] == 1) printf("0__0");
			else if (map[i][j] == 8) printf("oooo");
			else if (map[i][j] == 2) printf("\\  /");
			else printf("    ");
		} printf("\n");
		for (j = 0; j < n; j++) {
			if (map[i][j] == 9) printf("####");
			else if (map[i][j] == 1) printf("(||)");
			else if (map[i][j] == 8) printf("o  o");
			else if (map[i][j] == 2) printf(" xx ");
			else printf("    ");
		} printf("\n");
		for (j = 0; j < n; j++) {
			if (map[i][j] == 9) printf("####");
			else if (map[i][j] == 1) printf(" /\\ ");
			else if (map[i][j] == 8) printf("0000");
			else if (map[i][j] == 2) printf("/  \\");
			else printf("    ");
		} printf("\n");
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int map[20][20], x, m, n, i, j;
	for (i = 0; i < levels; i++) {
		x = init_map(map, 1, &m, &n);
		if (x != -1) {
			while (1) {
				print_map(map, m, n);
				system("clear");
			}
		}
	}
}