#include <stdio.h>

#include "path.h"

int main()
{
	paths_t paths;
	int x;
	
	get_paths(&paths, "./");

	for(int i = 0; i < paths.size; i++)
	{
		printf("%s\n",	paths.paths_name[i]);
	}
		
	free_paths(&paths);
}
