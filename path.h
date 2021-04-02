#ifndef PATH_H
#define PATH_H

void	get_paths(const char *path, char **result_paths, int *number_of_paths);
void free_paths(char **result_paths, int number_of_paths);
void create_directory(const char *path);
char *pathcat(const char* str1, char* str2);
void paths(const char* path, char **result_paths, int *number_of_paths);

#endif //PATH_H
