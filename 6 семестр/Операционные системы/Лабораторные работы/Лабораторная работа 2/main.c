//gcc -c main.c
//gcc -o app.exe main.o
#include <stdio.h>
#include <stdlib.h>
#include <errno.h> 
#include <unistd.h> 
#include <limits.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h> 

#define FTW_F 1 // файл, не являющийся каталогом
#define FTW_D 2 // каталог
#define FTW_DNR 3 // каталог, недоступный для чтения
#define FTW_NS 4 // файл, информацию о котором нельзя получить с помощью stat

// Тип функции, которая будет вызываться для каждого встреченного файла
typedef int Handler(const char *,const struct stat *, int);

static Handler counter;
static int dopath(const char *filename, int depth, Handler *);

static long nreg, ndir, nblk, nchr, nfifo, nslink, nsock, nTotal;

int main(int argc, char * argv[])
{
	int ret = -1; 
	if (argc != 2)
	{
		printf("ERROR, wrong arguments.\nUse: ./app <dir>\n");
		exit(-1);
	}

	ret = dopath(argv[1], 0, counter); //выполняет всю работу

	nTotal = nreg + ndir +  nblk + nchr +  nfifo + nslink + nsock;

	if (nTotal == 0)
		nTotal = 1; // во избежание деления на 0
	
	printf("_______________________________\nSummary:\n\n");
	printf("Common files:\t%7ld, %5.2f %%\n", nreg, nreg*100.0/nTotal);
	printf("Catalogs:\t%7ld, %5.2f %%\n", ndir, ndir*100.0/nTotal);
	printf("Block-devices:\t%7ld, %5.2f %%\n", nblk, nblk*100.0/nTotal);
	printf("Char-devices:\t%7ld, %5.2f %%\n", nchr, nchr*100.0/nTotal);
	printf("FIFOs:\t\t%7ld, %5.2f %%\n", nfifo, nfifo*100.0/nTotal);
	printf("Sym-links:\t%7ld, %5.2f %%\n", nslink, nslink*100.0/nTotal);
	printf("Sockets:\t%7ld, %5.2f %%\n\n", nsock, nsock*100.0/nTotal);
	printf("Total:\t%7ld\n", nTotal);

	exit(ret);
}


// Обход дерева каталогов
static int dopath(const char *filename, int depth, Handler *func)
{
	struct stat statbuf;
	struct dirent * dirp;
	DIR *dp;
	int ret = 0;

	if ((ret = lstat(filename, &statbuf)) != 0) // ошибка 
	{
		printf("LSTAT ERROR\n");
	
		switch(ret)
		{
			case EBADF:
				printf("Неверный файловый описатель filedes.\n");
				break;
				
			case ENOENT:
				printf("Компонент полного имени файла file_name не существует или полное имя является пустой строкой.\n");
				break;	
			case ENOTDIR:
				printf("Компонент пути не является каталогом.\n");
				break;					
			case ELOOP:
				printf("При поиске файла встретилось слишком много символьных ссылок.\n");
				break;	
			case EFAULT:
				printf("Некорректный адрес\n");
				break;	
			case EACCES:
				printf("Запрещен доступ.\n");
				break;	

			case ENOMEM:
				printf("Недостаточно памяти в системе.\n");
				break;	
			case ENAMETOOLONG:
				printf("Слишком длинное название файла.\n");
				break;
		}																			
		return ret;
	}   

	for (int i = 0; i < depth; ++i)
		printf("|\t");

	if (S_ISDIR(statbuf.st_mode) == 0) // не каталог 
		return(func(filename, &statbuf, FTW_F)); // отобразить в дереве 

	if ((ret = func(filename, &statbuf, FTW_D)) != 0)
		return(ret);

	if ((dp = opendir(filename)) == NULL) // каталог недоступен
		return(func(filename, &statbuf, FTW_DNR));
    
	chdir(filename); //меняет текущий рабочий каталог процесса. Без этого пришлось бы приписывать в цикле к dirp->d_name сзади filename ?? тк в dirp->d_name только имя файла без пути
	while ((dirp = readdir(dp)) != NULL && ret == 0)
	{
		if (strcmp(dirp->d_name, ".") != 0 &&
			strcmp(dirp->d_name, "..") != 0 ) // пропуск каталогов . и .. попали в текущую родительску директорию
		{
			ret = dopath(dirp->d_name, depth + 1, func);
		}
	}
    
	chdir("..");

	if (closedir(dp) < 0)
		perror("Невозможно закрыть каталог\n");

	return(ret);    
}

static int counter(const char *pathame, const struct stat *statptr, int type)
{
	switch(type)
	{
		case FTW_F: 
			printf( "-- %s\n", pathame);
			switch(statptr->st_mode & S_IFMT)
			{
				case S_IFREG: nreg++; break;
				case S_IFBLK: nblk++; break;
				case S_IFCHR: nchr++; break;
				case S_IFIFO: nfifo++; break;
				case S_IFLNK: nslink++; break;
				case S_IFSOCK: nsock++; break;
			}
			break;
		case FTW_D: 
			printf( "-- %s/\n", pathame);
			ndir++; 
			break;
		default: 
			perror("Неизвестый тип файла.\n"); 
			return(-1);
	}
	return(0);
}
