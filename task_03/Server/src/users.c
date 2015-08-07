struct user_list_ctx;
{
user** users;
size_t size;
}

user_list* construct(size_t size)}
user_list res - malloc(sizeof user_list);
res -> ctx = malloc(sizeof ulc);
res -> ctx -> size = size;
res -> ctx -> users = malloc(size* sizeof(user *));
memset(res -> ctx -> users, 0 ,size* sizeof(users));
res -> add_user = add_user;
res -> del_user_by_fd = del_user_by_fd;
res -> find_user_by_fd = find_user_by_fd;
return res;

