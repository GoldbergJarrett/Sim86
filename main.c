#include <stdio.h>
#include <stdlib.h>

static unsigned char buffer[1<<20];

int main()
{
	FILE *file;
	file = fopen("listing_37","rb");  // r for read, b for binary

	fread(buffer, 1, sizeof(buffer), file); // read 10 bytes to our buffer

	for(int i = 0; i < 10; i++)
	{
		if((buffer[i] >> 2) == 0b100010)
		{
    		printf("mov");	
		}
		else
		{
			printf(" %x", buffer[i]);
		}
	}

	return 0;
}