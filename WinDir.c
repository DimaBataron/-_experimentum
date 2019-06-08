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
int poiskSlovaVf(FILE **fp, char *slovo, int n, int k, char *file);
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
	int fl = 1;
	system("color 0A && chcp 1251"); // установка цвета и кодовой таблицы консоли.
	do
	{
		slovo = zapis_s_con("\n Ввод пути поиска файлов. Прм: \" P:\\A\\z \" ");
		catalog(slovo);
		do
		{
			FindFile(slovo);
			printf("\nИзменить расширения файлов поиска? 1-да,0-нет\n");
			scanf_s("%d", &fl);
		} while (fl == 1);
		printf("\nПовторить 1-да,0-нет");
		scanf_s("%d", &fl);
	} while (fl == 1);
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
	int len, fl=1,Err;
	char *F = "\\FindC.txt", *slovo1=NULL;
	char *slovo2; // расширения файлов в которых будем искать slovoFind
	struct stek *fls; // вершина стэка имен файлов с заданным расширением
	len = strlen(F);
	len += strlen(slovo); 
	slovo1 = (char *)malloc(len - 1);
	slovo1[0] = '\0';
	mystrcpy(slovo1, slovo);
	mystrcpy(slovo1, F); // slovo1 папка где ищем файлы содержащие слово
	slovo1[len-1] = '\0';
	if ((Err=fopen_s(&txt, slovo1, "rt")) != 0) 	// в этом файле каталог всех папок;
	{
		puts("открыть не удалось");
		_getch();
	}
	slovo2 = zapis_s_con("\nВвод расширений файлов в которых ищем. Прм. : \" .c \"");
	fls= Rash(slovo2, txt);
	do
	{
		FindS(fls, slovo);
		printf("\nПоиск завершен.Изменить слово поиска? 1-да,0-нет");
		scanf_s("%d", &fl);
	} while (fl == 1);
}

//Поиск слова с таким расширением в файле.
// slovo2 - что ищем; txt- в каком файле
// возвращает вершину стэка имен файлов с таким расширением
struct stek *Rash(char *slovo2, FILE *txt)
{
	char sl[1000], *result;
	int len,i=0,j=0;
	struct stek *TOP = NULL; // вершина стека
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

//Функция находит слова в текстовом фале, 
//возвращает указатель на массив символов найденного слова;
char *s_scanfDima(FILE *fp)
{
	int sym;
	long int karD, karP;
	while ((sym = fgetc(fp)) != EOF && sym == '\r' && sym == ' ' && sym == '\n')
	{

	}
}

//Процедура запрашивает что ищем, проводит поиск по файлам и выводит
// что найдено.
void FindS(struct stek *TOP,char *slovo1)
{
	char *s_find; // слово поиска
	char *pyt; // путь файла в котором ищем
	int len;
	struct stek *DEL= TOP; // указатель на текущую позицию
	FILE *fp;
	s_find = zapis_s_con("\n Ввод слова поиска в файлах");
	while (TOP != NULL)
	{
		len = strlen(slovo1);
		len += strlen(TOP->slovo);
		pyt = (char *)malloc(len);
		pyt[0] = '\0';
		mystrcpy(pyt, slovo1); // записываем путь 
		mystrcpy(pyt, TOP->slovo); // и наименование файла
		fopen_s(&fp, pyt, "r"); // открываем файл с таким расширением
		if (poiskSlovaVf(fp, s_find, 40, 100,TOP->slovo)==0); // поиск введенного
		// слова в этом файле
		{
			return 0;
		}
		DEL = DEL->NEXT;
	}
}

//Процедура поиска последовательности букв в файле.
//Находит и выводит последовательность букв
// а также n символов до и k символов после.
// Принимает на вход слово поиска и файл где ищем.
int poiskSlovaVf(FILE **fp, char *slovo, int n, int k,char *file)
{
	char sym;
	int i = 0,fl=0;
	long tek; // положение слова в файле.
	int len;
	int psym; //позиция последнего символа
	while ((sym = fgetc(fp)) != EOF)
	{
		if (sym==slovo[i])
		{
			i++; fl = 1;
		}
		else
		{
			if (slovo[i] == '\0' && fl==1) // нашли слово
			{
				printf("\nНайдено в файле %s", file);
				len = strlen(slovo);
				tek = ftell(fp);
				tek = tek - (long)len; // tek положение указателя 
				// относительно начала файла
				if ((tek - n)>0) // можно вывести столько символов до
				{
					fseek(fp, -(long)n, 1);
					while (ftell(fp) < tek)
					{
						putchar(fgetc(fp)); //выводим
					}
				}
				else // нельзя выводим сколько можно
				{
					fseek(fp, 0, 1);
					while (ftell(fp) < tek)
					{
						putchar(fgetc(fp));
					}
				}
				fseek(fp, 0, 3);
				psym =ftell(fp);// получаем позицию последнего символа
				if ((tek + k) < psym) // если можно вывести k
				// символов после
				{
					fseek(fp, (long)tek, 0);
					while (ftell(fp)<(tek+k))
					{
						putchar(fgetc(fp));
					}
				}
				else // нельзя выводим сколько осталось
				{
					fseek(fp, (long)tek, 0);
					while (ftell(fp) < psym)
					{
						putchar(fgetc(fp));
					}
				}
				printf("\n Продолжить? 1-да 0-нет");
				scanf_s("%d", &fl);
				if (fl == 0) return 0;
			}

			else i = 0;
		}
		fl = 0;
	}
	return 1;
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
			slovo1[n-1] = sym; // запись переданного в функцию символа
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
