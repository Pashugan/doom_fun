#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "wad.h"

#define WAD_PATH "doomu.wad"

int main()
{
	FILE *fp = fopen(WAD_PATH, "r");
	if (fp == NULL) {
		printf("Failed to open WAD file\n");
		return EXIT_FAILURE;
	}

	WadHeader *header = wad_read_header(fp);

	printf("File type: %s\n", header->wad_type);
	printf("# of dirs: %d\n", header->dir_count);
	printf("Dir offset: %d\n", header->dir_offset);

	WadDirectory *dirs = wad_read_directories(fp, header);
	if (dirs == NULL) {
		printf("Failed to read WAD directories\n");
		return EXIT_FAILURE;
	}

	fclose(fp);

	for (unsigned int i = 0; i < header->dir_count; ++i) {
		printf("Lump '%s' at offset %d of size %d\n", dirs[i].name, dirs[i].offset, dirs[i].size);
	}

	return EXIT_SUCCESS;
}
