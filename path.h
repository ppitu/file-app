#ifndef PATH_H
#define PATH_H

typedef struct {
	char 		**paths_name;
	int		size;
} paths_t;

void	get_paths(const char *path, paths_t *paths);
void free_paths(paths_t *paths);
void create_directory(const char *path);
char *pathcat(const char* str1, char* str2);
void get_paths_help(const char* path, paths_t *paths);

#endif //PATH_H
