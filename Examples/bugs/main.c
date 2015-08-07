#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
	char *c = malloc(6*sizeof(char));

	strcpy(c, "roman");

	printf("name: \"%s\"\n", c);

	free(c);

	return 0;
}

