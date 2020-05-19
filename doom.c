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

	WadDirectory *dirs = wad_read_directories(fp, header);
	if (dirs == NULL) {
		printf("Failed to read WAD directories\n");
		return EXIT_FAILURE;
	}

	Map *map = wad_read_map("E1M1", fp, header, dirs);
	for (int i = 0; i < map->vertexes_cnt; ++i) {
		printf("(%d,%d)\n", map->vertexes[i].x_pos, map->vertexes[i].y_pos);
	}

	fclose(fp);

	return EXIT_SUCCESS;
}
