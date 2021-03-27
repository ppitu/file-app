#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#include "path.h"


void getpath(char *path)
{
	
}

void paths(const char* path)
{
	struct dirent		*dp;
	char			*fullpath;
	DIR			*dir = opendir(path);
	DIR			*dir2;
	int 			x, ascii;

	while((dp = readdir(dir)))
	{
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
			continue;

		fullpath = pathcat(path, dp->d_name);
		printf("%s\n", fullpath);

		dir2 = opendir(fullpath);

		if(dir2 != NULL && strcmp(fullpath, "/.") != 0 && strcmp(fullpath, "/..") != 0)
		{
			paths(fullpath);
		}
			

		free(fullpath);
	}

	closedir(dir);

}

char *pathcat(const char *str1, char *str2)
{
	char			*res;
	size_t			strlen1 = strlen(str1);
	size_t			strlen2 = strlen(str2);
	int			i, j;
	res = malloc((strlen1+strlen2 +2)*sizeof(*res));
	strcpy(res, str1);
	strcat(res, "/");

	strlen1++;

	for(i = strlen1, j = 0; ((i < (strlen1+strlen2)) && (j < strlen2)); i++, j++)
	{
		res[i] = str2[j];
	}

	res[strlen1 + strlen2] = '\0';
	return res;
}
