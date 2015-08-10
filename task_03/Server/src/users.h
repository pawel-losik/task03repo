#include <stdlib.h>

typedef struct user
{
	int fd;
	char nick[50];
} user;

typedef struct user_list_ctx ulc;

typedef struct user_list
{
	ulc* ctx;
	int(*add_user)(struct user_list* self,user* c);
	int(*del_user_by_fd)(struct user_list* self, int fd);
	user* (*find_user_by_fd)(struct user_list* self, int fd);
} user_list;

user_list* alloc_ul(size_t size);
void free_ul(user_list* ul);

