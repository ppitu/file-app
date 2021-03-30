#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>

#include "path.h"


void create_directory(const char* path)
{
	char *subpath, *fullpath;
	int err;

	fullpath = strdup(path);

	subpath = dirname(fullpath);

	if(strlen(subpath) > 1)
	{
		create_directory(subpath);
	}

	err = mkdir(path, 0777);

 	if(err == -1 && errno == EEXIST)
	{
		//Nothing happen dir exists	
	} else if(err == -1)
	{
		perror("Error: ");
	}

	free(fullpath);
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
