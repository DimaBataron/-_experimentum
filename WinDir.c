#include<stdio.h> //Модуль стандартного ввода-вывода
#include<conio.h> /*Модуль функций расширения ввода-вывода*/
#include <stdlib.h> /* содержит в себе функции, занимающиеся выделением памяти, 
 контролем процесса выполнения программы, преобразованием типов и другие.  */
#include <string.h> // функции работы со строками

char *slov(char *slovo, int n, char sym);
char *zapis_s_con(char *s);
void catalog(char *slovo);
void mystrcpy(char *slovoD, char *slovoS);
void FindS(struct stek *TOP, char *slovo1);
char *FindFile(char *slovo);
void poiskSlovaVf(FILE *fp, char *slovo, int n, int k);
struct stek *Rash(char *slovo2, FILE *txt);
struct stek *dobavMen9(struct stek *TOP);

struct stek
{
	char *slovo;
	struct stek *NEXT; // следубщая структура
};

void main()
{
	char *slovo=NULL;
	char *FailFind;
	system("color 0A && chcp 1251"); // установка цвета и кодовой таблицы консоли.
	slovo = zapis_s_con("\n Ввод пути поиска файлов. Прм: \" P:\\A\\z \" ");
	catalog(slovo);
	FailFind = FindFile(slovo);
	_getch();
}


/*
Процедура Открывает введенный каталог, и создает текстовый файл с
наименованием файлов содержащихся в нем.
*/
void catalog(char *slovo)
{
	int len;
	char *sd = "cd /d ";
	char *sd2 = " && dir /B > FindC.txt";
	char *slovo1=NULL;
	if (slovo != NULL)
	{
		len = strlen(slovo); // считает с '\0' т.е. Дима=5б
		len+= strlen(sd);
		len+= strlen(sd2);
		slovo1 = (char *)malloc(len - 2);
		slovo1[0] = '\0';
		mystrcpy(slovo1, sd);
		mystrcpy(slovo1, slovo);
		mystrcpy(slovo1, sd2);
		system(slovo1);
	}
	else 
	{
		printf("Ошибка, указатель пути файла NULL");
	}
}


//Процедура запрашивает строку, и проводит поиск
// по расширениям в заданном каталоге, возвращает имя файла с 
// таким расширением в противном случае NULL
char *FindFile(char *slovo)
{
	FILE *txt;
	int len;
	char *F = "\\FindC.txt", *slovo1;
	char *slovo2; // расширения файлов в которых будем искать slovoFind
	len = strlen(F);
	len += strlen(slovo); 
	slovo1 = (char *)malloc(len - 1);
	mystrcpy(slovo1, slovo);
	mystrcpy(slovo1, F); // slovo1 папка где ищем файлы содержащие слово
	slovo1[len-1] = '\0';
	fopen_s(&txt, slovo1, "r"); // в этом файле каталог всех папок;
	slovo2 = zapis_s_con("\nВвод расширений файлов в которых ищем. Прм. : \" .c \"");
	return Rash(slovo2, txt);
}

//Поиск слова с таким расширением в файле.
// slovo2 - что ищем; txt- в каком файле
// возвращает вершину стэка имен файлов с таким расширением
struct stek *Rash(char *slovo2, FILE *txt)
{
	char sl[150], *result;
	int len,i=0,j=0;
	struct stek *TOP = NULL; // вершина стэка
	while ((len = fscanf_s(txt, "%s", sl)) != 0)
	{
		while (sl[i] != '\0')
		{
			if (sl[i] == slovo2[j])
			{
				while (sl[i++] == slovo2[j++]);
				if ((sl[i] == '\0') && (slovo2[j] == '\n'))
				{
					result = (char *)malloc(len + 1);
					mystrcpy(result, sl);
					TOP = dobavMen9(TOP);
					TOP->slovo = result;
				}
			}
			else i++;
			j = 0;
		}
		i = 0; j = 0;
	}
	return TOP;
}

//Процедура запрашивает что ищем, проводит поиск по файлам и выводит
// что найдено.
void FindS(struct stek *TOP,char *slovo1)
{
	char *s_find; // слово поиска
	char *pyt; // путь файла в котором ищем
	int len;
	FILE *fp;
	s_find = zapis_s_con("\n Ввод слова поиска в файлах");
	while (TOP != NULL)
	{
		len = strlen(slovo1);
		len += strlen(TOP->slovo);
		pyt = (char *)malloc(len);
		mystrcpy(pyt, slovo1);
		mystrcpy(pyt, TOP->slovo);
		fopen_s(&fp, pyt, "r");
	}
}

//Процедура поиска последовательности букв в файле.
//Находит и выводит последовательность букв
// а также n символов до и k символов после.
// Принимает на вход слово поиска и файл где ищем.
void poiskSlovaVf(FILE *fp, char *slovo, int n, int k)
{
	char sym;
	int i = 0,fl=0;
	long tek; // положение слова в файле.
	int len;
	while ((sym = fgetc(fp)) != EOF)
	{
		if (sym==slovo[i])
		{
			i++; fl = 1;
		}
		else
		{
			if (slovo[i] == '\0') // нашли слово
			{
				len = strlen(slovo);
				tek = ftell(fp);
				tek = tek - (long)len; // tek положение указателя 
				// относительно начала файла

			}
			else i = 0;
		}
	}
}

// Функция добавляет структуру на вершину стэка
// возвращает указатель на вершину стэка
struct stek *dobavMen9(struct stek *TOP)
{
	struct stek *BEG;
	if (TOP != NULL)
	{
		BEG = (struct stek *)malloc(sizeof(struct stek));
		BEG->NEXT = TOP;
	}
	else
	{
		BEG = (struct stek *)malloc(sizeof(struct stek));
		BEG->NEXT = NULL;
	}
	return BEG;
}

// Копирует слова, функции strcpy_s и strcat_s мне ненравится, 
// а особенно вот эта _s в конце!!. 
// в MS считают меня дауном походу.
void mystrcpy(char *slovoD , char *slovoS)
{
	int i = 0, z=0;
	if (slovoD[0] != '\0') 
		while ((slovoD[i] != '\0') && (slovoD[i]!='\n')) i++;
	while (slovoS[z] != '\0') slovoD[i++] = slovoS[z++];
	slovoD[i] = '\0';
}


// Функция проводит считывание с консоли символов
// выделяет память для полученного количества символов
// ВОЗВРАЩАЕТ УКАЗАТЕЛЬ НА СТРОКУ ВВЕДЕННУЮ В КОНСОЛИ.
char *zapis_s_con(char *s)
{
	char sym, *slovo=NULL;
	//printf("\n Ввод пути поиска файлов. Прм: \" P:\\A\\z \" ");
	puts(s);
	printf("\n Enter ввод. Ctrl+z для останова ввода\n");
	int i = 0;
	while ((sym = getchar()) != EOF) //считывает всю строку введенную с клавы.
	{
		i++;
		slovo = slov(slovo, i, sym);
	}
	return slovo;
}


//Функция принимает на вход, указатель на массив символов
// и номер введенной буквы. Возвращает указатель на новое слово.
// Выделяет память для нового количества букв,
// записывает старое слово + добавляет новую букву
// Ставит в конец признак окончания слова. '\0'
// Очищает память от старого слова.
char *slov(char *slovo, int n,char sym)
{
	char *slovo1=NULL;
	if (n == 1)
	{
		slovo = (char*)malloc(sizeof(char)*2);
		*slovo = sym;
		*(slovo + 1) = '\0';
		return slovo;
	}
	else
	{
		if (slovo[n-1] != '\n')
		{
			slovo1 = (char *)malloc(sizeof(char)*n + 1); // выделяем память для нового слова
			int j = 0;
			while (*(slovo + j) != '\0')  // копируем предыдущую строку
			{
				*(slovo1 + j) = *(slovo + j);
				j++;
			}
			slovo1[n - 1] = sym; // запись переданного в функцию символа
			slovo1[n] = '\0'; // запись признака окончания слова
			free(slovo);
			return slovo1;
		}
		else
		{
			slovo[n - 1] = '\0';
			return slovo;
		}
	}
}
