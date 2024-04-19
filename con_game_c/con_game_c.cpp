#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "conio.h"
#include "locale.h"
#include "string.h"
#include "windows.h"
#include "math.h"

int dai_chislo(int a, int b) { // Функция ввода числа
	int i, k, f = 1;
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

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}