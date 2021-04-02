#include <stdio.h>

#include "path.h"

int main()
{
	char **paths;
	int x;
	
	get_paths("./", paths, &x);

	printf("%d\n", x);
	printf("---------------------------\n");
	for(int i =0 ; i < x; i++)
	{
		printf("%s\n",	paths[i]);
	}

	printf("+++++++++++++++++++++++++++\n");
		
	printf("=================================\n");
	free_paths(paths, x);
}
