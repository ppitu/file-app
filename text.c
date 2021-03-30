#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <errno.h>

void test(const char* path)
{
	char *subpath, *fullpath;

	fullpath = strdup(path);

	subpath = dirname(fullpath);

	if(strlen(subpath) > 1)
	{
		test(subpath);
	}

 	if(mkdir(path, 0777) == -1 && errno == EEXIST)
	{
		printf("To jest blad\n");
	} else if(mkdir(path, 0777) == -1)
	{
		perror("Error: ");
	}

	free(fullpath);
}

int main()
{
	char* name = "Test3/Test2/Test123/Test1";

	//printf("%s\n", basename(name));

	test(name);

	//mkdir(basename(name), 0777);

	return 0;
}
