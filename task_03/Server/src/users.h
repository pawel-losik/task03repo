typedef struct user{
int fd;
char nick[50];}user;

typedef user_list_ctx ulc;
typdef struct user_list
{
ulc* ctx;
int(*add_user)(struct user_list_self,user* c);
int(*del_user_by_fd)(struct user_list_self, int fd);
user* (*find_user_by_fd)(struct user_list_self, int fd);
} user_list;

