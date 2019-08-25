#include<stdio.h> //Модуль стандартного ввода-вывода
#include<conio.h> /*Модуль функций расширения ввода-вывода*/
#include <stdlib.h> /* заголовочный файл стандартной библиотеки языка Си,
 который содержит в себе функции, занимающиеся выделением памяти, 
 контролем процесса выполнения программы, преобразованием типов и другие. 
 Заголовок вполне совместим с C++ и известен в нём как cstdlib.
 Название «stdlib» расшифровывается как «standard library» (стандартная библиотека). */
#include <stdint.h>

void main()
{
	struct address {
		char* name; // имя "Jim Dandy" 
		long  number; // номер дома 61  
		char* street; // улица "South Street" 
		char* town; // город "New Providence"  
		char* state[2]; // штат 'N' 'J' 
		int   zip; // индекс 7974 
	};
	struct address jd = { "Jim Dandy",  61, "South Street",  "New Providence", {'N','J'}, 7974 };;
}
