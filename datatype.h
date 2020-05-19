#include <stdint.h>

typedef struct Vertex {
	int16_t x_pos;
	int16_t y_pos;
} Vertex;

typedef struct Linedef {
	uint16_t start_vertex;
	uint16_t end_vertex;
	uint16_t flags;
	uint16_t line_type;
	uint16_t sector_tag;
	uint16_t rightside_def;
	uint16_t leftside_def;
} Linedef;

typedef struct Map {
	char name[5];
	Vertex *vertexes;
	uint16_t vertexes_cnt;
	Linedef *linedefs;
	uint16_t linedefs_cnt;
} Map;
