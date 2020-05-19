#include <string.h>
#include "wad.h"

WadHeader* wad_read_header(FILE* fp)
{
	WadHeader *h;

	h = (WadHeader *)malloc(sizeof(WadHeader));

	fread(h->wad_type, sizeof(char), sizeof_field(WadHeader, wad_type) - 1, fp);
	h->wad_type[sizeof_field(WadHeader, wad_type) - 1] = '\0';
	fread(&h->dir_cnt, sizeof(h->dir_cnt), 1, fp);
	fread(&h->dir_offset, sizeof(h->dir_offset), 1, fp);

	return h;
}

WadDirectory* wad_read_directories(FILE* fp, const WadHeader* header)
{
	int res = fseek(fp, (long)header->dir_offset, SEEK_SET);
	if (res == -1) {
		return NULL;
	}

	WadDirectory *dirs = (WadDirectory *)malloc(header->dir_cnt * sizeof(WadDirectory));

	for (unsigned int i = 0; i < header->dir_cnt; ++i) {
		fread(&dirs[i].offset, sizeof(dirs->offset), 1, fp);
		fread(&dirs[i].size, sizeof(dirs->size), 1, fp);
		fread(dirs[i].name, sizeof(char), sizeof_field(WadDirectory, name) - 1, fp);
		dirs[i].name[sizeof_field(WadDirectory, name) - 1] = '\0';
	}

	return dirs;
}

Map* wad_read_map(const char* map_name, FILE* fp, const WadHeader* header, const WadDirectory* dirs)
{
	Map *map;
	map = (Map *)malloc(sizeof(Map));
	strncpy(map->name, map_name, sizeof_field(Map, name) - 1);
	map->name[sizeof_field(Map, name) - 1] = '\0';

	// Find the map in the directories
	const WadDirectory *map_dir = NULL;
	for (unsigned int i = 0; i < header->dir_cnt; ++i) {
		if (strcmp(dirs[i].name, map_name) == 0) {
			map_dir = dirs + i;
			break;
		}
	}
	if (map_dir == NULL) {
		return NULL;
	}

	// Read the vertexes
	const WadDirectory *vertex_dir = map_dir + VERTEXES;

	int res = fseek(fp, (long)vertex_dir->offset, SEEK_SET);
	if (res == -1) {
		return NULL;
	}

	map->vertexes_cnt = vertex_dir->size / sizeof(Vertex);
	map->vertexes = (Vertex *)malloc(sizeof(Vertex) * map->vertexes_cnt);

	for (unsigned int i = 0; i < map->vertexes_cnt; ++i) {
		fread(&map->vertexes[i].x_pos, sizeof(map->vertexes->x_pos), 1, fp);
		fread(&map->vertexes[i].y_pos, sizeof(map->vertexes->y_pos), 1, fp);
	}

	// Read the linedefs
	const WadDirectory *linedef_dir = map_dir + LINEDEFS;

	res = fseek(fp, (long)linedef_dir->offset, SEEK_SET);
	if (res == -1) {
		return NULL;
	}

	map->linedefs_cnt = linedef_dir->size / sizeof(Linedef);
	map->linedefs = (Linedef *)malloc(sizeof(Linedef) * map->linedefs_cnt);

	for (unsigned int i = 0; i < map->linedefs_cnt; ++i) {
		fread(&map->linedefs[i].start_vertex, sizeof(map->linedefs->start_vertex), 1, fp);
		fread(&map->linedefs[i].end_vertex, sizeof(map->linedefs->end_vertex), 1, fp);
		fread(&map->linedefs[i].flags, sizeof(map->linedefs->flags), 1, fp);
		fread(&map->linedefs[i].line_type, sizeof(map->linedefs->line_type), 1, fp);
		fread(&map->linedefs[i].sector_tag, sizeof(map->linedefs->sector_tag), 1, fp);
		fread(&map->linedefs[i].rightside_def, sizeof(map->linedefs->rightside_def), 1, fp);
		fread(&map->linedefs[i].leftside_def, sizeof(map->linedefs->leftside_def), 1, fp);
	}

	return map;
}
