#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	unsigned int input;
	FILE *fout;

	fout = fopen("exploit.bytes", "w");
	while((scanf(" %x", &input)) != EOF) {
		if(input < 0x00 || input > 0xFF) {
			printf("Error: over range(0x00 <= input <= 0xFF)\n");
			fclose(fout);
			exit(1);
		}
		fwrite((char *)&input, sizeof(char), 1, fout);
	}
	fwrite("\n", sizeof(char), 1, fout);
	fclose(fout);

	return 0;
}
