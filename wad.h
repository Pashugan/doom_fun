#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "datatype.h"

#define sizeof_field(TYPE, MEMBER) sizeof((((TYPE *)0)->MEMBER))

typedef struct WadHeader {
	char wad_type[5];
	uint32_t dir_cnt;
	uint32_t dir_offset;
} WadHeader;

typedef struct WadDirectory {
	char name[9];
	uint32_t offset;
	uint32_t size;
} WadDirectory;

enum mapidx {
	THINGS = 1,
	LINEDEFS,
	SIDEDEFS,
	VERTEXES,
	SEGS,
	SSECTORS,
	NODES,
	SECTORS,
	REJECT,
	BLOCKMAP,
};

WadHeader* wad_read_header(FILE* fp);

WadDirectory* wad_read_directories(FILE* fp, const WadHeader* header);

Map* wad_read_map(const char* map_name, FILE* fp, const WadHeader* header, const WadDirectory* dirs);
