#include <stdio.h>

#include "data_transfer.h"

int main()
{
	char *name = "Hello Peter";

	char buffer[6];

	get_substring(0, 5, name, buffer);

	printf("%s\n", buffer);
}
