#ifndef PATH_H
#define PATH_H

typedef struct {
	char 		**paths_name;
	int		size;
} paths_t;

void 
init_paths 		(paths_t	*paths);

void	
get_paths		(paths_t	*paths,
			const char 	*path);

void 
free_paths		(paths_t 	*paths);

void 		
create_directory	(const char 	*path);

#endif //PATH_H
