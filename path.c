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
#include "data_transfer.h"


void 
create_directory	(const char 	*path)
{
	char 			*subpath; 
	char			*fullpath;
	int 			err;

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

void
get_paths	(const char	*path,
		paths_t		*paths)
{
	paths->size = 0;

	get_paths_help(path, paths);
}

void
free_paths	(paths_t	*paths)
{
	int 			i;

	for(i = 0; i < paths->size; ++i)
	{
		printf("{-}%d\n", i);
		free(paths->paths_name[i]);
	}
	printf("Test\n");
	free(paths->paths_name);
}

void 
get_paths_help	(const char	*path,
		paths_t		*paths)
{
	struct dirent		*dp;
	char			*fullpath;
	DIR			*dir;
	DIR			*dir2;
	int 			x, ascii;

	dir = opendir(path);

	while((dp = readdir(dir)))
	{
		if(strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0 || strcmp(dp->d_name, ".git") == 0)
			continue;

		++paths->size;

		fullpath = pathcat(path, dp->d_name);

		if(paths->size == 1)
		{
			paths->paths_name = (char **)malloc(1 * sizeof(char *));
		} else
		{
			paths->paths_name = (char **)realloc(paths->paths_name, paths->size * sizeof(char *));
		}
		paths->paths_name[paths->size - 1] = (char *)malloc(strlen(fullpath) * sizeof(char));

		strcat(paths->paths_name[paths->size - 1], fullpath);

		printf("%ld || %ld\n", strlen(fullpath), strlen(paths->paths_name[paths->size - 1]));
		
		printf("%s\n", fullpath);
		printf("%s\n", paths->paths_name[paths->size - 1]);

		dir2 = opendir(fullpath);
	
		if(dir2 != NULL && strcmp(fullpath, "/.") != 0 && strcmp(fullpath, "/..") != 0)
		{
			get_paths_help(fullpath, paths);
		}
		

		closedir(dir2);
		free(fullpath);
	}

	closedir(dir);

}

char *
pathcat		(const char 	*str1, 
		char 		*str2)
{
	char			*res;
	size_t			strlen1 = strlen(str1);
	size_t			strlen2 = strlen(str2);
	int			i, j;

	if(str1[strlen1 + 1] == '/')
	{
		res = malloc((strlen1+strlen2 +1)*sizeof(*res));

	} else
	{
		res = malloc((strlen1+strlen2 +2)*sizeof(*res));

	}
	
	strcpy(res, str1);

	if(res[strlen1 -1] != '/')
	{
		strcat(res, "/");

		strlen1++;
	}

	for(i = strlen1, j = 0; ((i < (strlen1+strlen2)) && (j < strlen2)); i++, j++)
	{
		res[i] = str2[j];
	}

	res[strlen1 + strlen2] = '\0';
	return res;
}
