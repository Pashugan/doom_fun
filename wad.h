#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
	char wad_type[5];
	uint32_t dir_count;
	uint32_t dir_offset;
} WadHeader;

typedef struct {
	char name[9];
	uint32_t offset;
	uint32_t size;
} WadDirectory;

WadHeader* wad_read_header(FILE* fp);

WadDirectory* wad_read_directories(FILE* fp, const WadHeader* header);
