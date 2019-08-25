#include <conio.h>
#include <stdio.h>
/*
	1) db 0, 0, 0, 0, 0
	2) db 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
	3) db 'aaaaa'
	4) db 'abcde'
	Дан массив из 5 байт. Рассматривая его как массив из восьми
	5-битных байтов, посчитать количество байт с четным числом единиц.

*/
void main() {
	char mas1[] = { 0,0,0,0,0 };
	
	int buf=0, kik=0, kol=0;
	
	for (int i = 0, sdvig = 0; i < 4; i++, sdvig += 8) {
		buf |= mas1[i] << sdvig;
	}
	
	for (int i = 0, k=2; i < 6; i++) {
		int z = 0;
		kik = 0; // количество едениц
		while (z < 5) {
			if ((buf & k) >0) kik++;
			k *= 2;
			z++;
		}
		if ((kik % 2) == 0) kol++; // кол количесвто байт с четными единичными разрядами
	}
	buf = (buf & -1073741824) >> 30;
	buf |= mas1[4] << 2;
	
	for (int i = 0, k = 2; i < 2; i++) {
		int z = 0;
		kik = 0;
		while (z < 5) {
			if ((buf & k) > 0) kik++;
			k *= 2;
			z++;
		}
		if ((kik % 2) == 0) kol++;
	}
		//printf_s("%d", kol);;
}