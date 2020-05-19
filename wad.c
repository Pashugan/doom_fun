#include "wad.h"

WadHeader* wad_read_header(FILE* fp)
{
	WadHeader *h;

	h = (WadHeader *)malloc(sizeof(WadHeader));

	fread(h->wad_type, sizeof(char), 4, fp);
	h->wad_type[4] = '\0';

	fread(&h->dir_count, sizeof(h->dir_count), 1, fp);

	fread(&h->dir_offset, sizeof(h->dir_offset), 1, fp);

	return h;
}

WadDirectory* wad_read_directories(FILE* fp, const WadHeader* header)
{
	int res = fseek(fp, (long)header->dir_offset, SEEK_SET);
	if (res == -1) {
		return NULL;
	}

	WadDirectory *dirs = (WadDirectory *)malloc(header->dir_count * sizeof(WadDirectory));

	for (unsigned int i = 0; i < header->dir_count; i++) {
		fread(&dirs[i].offset, sizeof(dirs->offset), 1, fp);
		fread(&dirs[i].size, sizeof(dirs->size), 1, fp);
		fread(dirs[i].name, sizeof(char), 8, fp);
		dirs[i].name[8] = '\0';
	}

	return dirs;
}
