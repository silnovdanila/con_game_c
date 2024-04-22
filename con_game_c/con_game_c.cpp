#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "locale.h"
#include "string.h"
#include "windows.h"
#include "math.h"
#define levels 5
#define map_size 30
FILE* f;

struct Object {
	int x;
	int y;
} boxes[6];

int init_map(int map[map_size][map_size], int level_num, int* m, int* n, int* now_x, int* now_y, int *box, int *end) {
	char fname[20] = "level", flevel[5], ch;
	int i, j;
	*(box) = 0;
	*(end) = 0;
	strcat(fname, _itoa(level_num, flevel, 10));
	strcat(fname, ".txt");
	f = fopen(fname, "r");
	if (f == NULL) return -1;
	i = j = 0;
	while (fscanf(f, "%c", &ch) != EOF) {
		if (ch == '9') map[i][j] = 9;
		else if (ch == 's') { map[i][j] = 0; *(now_x) = j; *(now_y) = i; }
		else if (ch == 'k') { map[i][j] = 0; boxes[*(box)] = Object{ j, i }; *(box) = *(box) + 1; }
		else if (ch == 'o') { map[i][j] = 2; *(end) = *(end) + 1; }
		else if (ch == ' ') map[i][j] = 0;
		else if (ch == '\n') { i++; j = -1;}
		j++;
	}
	*(m) = i + 1;
	*(n) = j;
	fclose(f);
	return 0;
}
int is_box(int y, int x, int box) {
	int f = 0, i;
	for (i = 0; i < box; i++) {
		if (boxes[i].x == x && boxes[i].y == y) f = 1;
	}
	return f;
}

void print_map(int map[map_size][map_size], int m, int n, int x, int y, int box){
	int i, j;
	for (i = 0; i < m; i++) {
		for (j = 0; j < n; j++) {
			if (map[i][j] == 9) printf("####");
			else if (i == y && j == x) printf("0__0");
			else if (is_box(i, j, box)) printf("oooo");
			else if (map[i][j] == 2) printf("\\  /");
			else printf("    ");
		} printf("\n");
		for (j = 0; j < n; j++) {
			if (map[i][j] == 9) printf("####");
			else if (i == y && j == x) printf("(||)");
			else if (is_box(i, j, box)) printf("o  o");
			else if (map[i][j] == 2) printf(" xx ");
			else printf("    ");
		} printf("\n");
		for (j = 0; j < n; j++) {
			if (map[i][j] == 9) printf("####");
			else if (i == y && j == x) printf(" /\\ ");
			else if (is_box(i, j, box)) printf("oooo");
			else if (map[i][j] == 2) printf("/  \\");
			else printf("    ");
		} printf("\n");
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int map[map_size][map_size], x, m, n, i, j, now_x, now_y, box, end, k;
	char c;
	for (i = 0; i < levels; i++) {
		x = init_map(map, i + 1, &m, &n, &now_x, &now_y, &box, &end);
		k = 0;
		if (x != -1) {
			while (1) {
				print_map(map, m, n, now_x, now_y, box);
				c = _getch();
				if (c == 'w') { // w
					if (is_box(now_y - 1, now_x, box)) {
						if (map[now_y - 2][now_x] == 0 && !is_box(now_y - 2, now_x, box)) {
							if (map[now_y - 1][now_x] == 2) k--;
							for (j = 0; j < box; j++) {
								if (boxes[j].x == now_x && boxes[j].y == now_y - 1) {
									boxes[j].y = boxes[j].y - 1;
									now_y--;
								}
							}
						}
						else if (map[now_y - 2][now_x] == 2) {
							k++;
							if (map[now_y - 1][now_x] == 2) k--;
							if (k == end) break;
							for (j = 0; j < box; j++) {
								if (boxes[j].x == now_x && boxes[j].y == now_y - 1) {
									boxes[j].y = boxes[j].y - 1;
									now_y--;
								}
							}
						}
					}
					else if (map[now_y - 1][now_x] == 0 || map[now_y - 1][now_x] == 2) {
						now_y--;
					}
				}
				else if (c == 'a') { // a
					if (is_box(now_y, now_x - 1, box)) {
						if (map[now_y][now_x - 2] == 0 && !is_box(now_y, now_x - 2, box)) {
							if (map[now_y][now_x - 1] == 2) k--;
							for (j = 0; j < box; j++) {
								if (boxes[j].x == now_x - 1 && boxes[j].y == now_y) {
									boxes[j].x = boxes[j].x - 1;
									now_x--;
								}
							}
						}
						else if (map[now_y][now_x - 2] == 2) {
							k++;
							if (map[now_y][now_x - 1] == 2) k--;
							if (k == end) break;
							for (j = 0; j < box; j++) {
								if (boxes[j].x == now_x - 1 && boxes[j].y == now_y) {
									boxes[j].x = boxes[j].x - 1;
									now_x--;
								}
							}
						}
					}
					else if (map[now_y][now_x - 1] == 0 || map[now_y][now_x - 1] == 2) {
						now_x--;
					}
				}
				else if (c == 's') { // s
					if (is_box(now_y + 1, now_x, box)) {
						if (map[now_y + 2][now_x] == 0 && !is_box(now_y + 2, now_x, box)) {
							if (map[now_y + 1][now_x] == 2) k--;
							for (j = 0; j < box; j++) {
								if (boxes[j].x == now_x && boxes[j].y == now_y + 1) {
									boxes[j].y = boxes[j].y + 1;
									now_y++;
								}
							}
						}
						else if (map[now_y + 2][now_x] == 2) {
							k++;
							if (map[now_y + 1][now_x] == 2) k--;
							if (k == end) break;
							for (j = 0; j < box; j++) {
								if (boxes[j].x == now_x && boxes[j].y == now_y + 1) {
									boxes[j].y = boxes[j].y + 1;
									now_y++;
								}
							}
						}
					}
					else if (map[now_y + 1][now_x] == 0 || map[now_y + 1][now_x] == 2) {
						now_y++;
					}
				}
				else if (c == 'd') { // d
					if (is_box(now_y, now_x + 1, box)) {
						if (map[now_y][now_x + 2] == 0 && !is_box(now_y, now_x - 2, box)) {
							if (map[now_y][now_x + 1] == 2) k--;
							for (j = 0; j < box; j++) {
								if (boxes[j].x == now_x + 1 && boxes[j].y == now_y) {
									boxes[j].x = boxes[j].x + 1;
									now_x++;
								}
							}
						}
						else if (map[now_y][now_x + 2] == 2) {
							k++;
							if (map[now_y][now_x + 1] == 2) k--;
							if (k == end) break;
							for (j = 0; j < box; j++) {
								if (boxes[j].x == now_x + 1 && boxes[j].y == now_y) {
									boxes[j].x = boxes[j].x + 1;
									now_x++;
								}
							}
						}
					}
					else if (map[now_y][now_x + 1] == 0 || map[now_y][now_x + 1] == 2) {
						now_x++;
					}
				}
				else if (c == 'r') {
					x = init_map(map, i + 1, &m, &n, &now_x, &now_y, &box, &end);
					k = 0;
					if (x == -1) break;
				}
				system("cls");
			}
		}
		system("cls");		
	}
	printf("Поздравляю! Вы прошли все уровни");
}