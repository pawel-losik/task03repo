#include "users.h"
#include <string.h>

struct user_list_ctx {
	size_t size;
	user** users;
};

static int del_user_by_fd(user_list* self,int fd)
{
	size_t i=0;
	for(; i < self->ctx->size; ++i)
	{
		if(self->ctx->users[i] && self->ctx->users[i]->fd==fd)
		{
			free(self->ctx->users[i]);
			self->ctx->users[i]=0;
			return 0;
		}
	}

	return 1;
}


static int add_user(user_list* self, user* u)
{
	size_t i=0;
	for(; i<self->ctx->size; ++i)
	{
		if(self->ctx->users[i]==0)
		{
			self->ctx->users[i]=u;
			return 0;
		}
	}

	return 1;
}

static user* find_user_by_fd(user_list* self, int fd)
{
	size_t i=0;
	for (; i < self->ctx->size; ++i)
	{
		if( self->ctx->users[i] && self->ctx->users[i]->fd==fd)
		{
			return self->ctx->users[i];
		}
	}

	return 0;
}

user_list* alloc_ul(size_t size)
{
	user_list* ul = malloc(sizeof(user_list));
	ul->ctx = malloc(sizeof(ulc));
	ul->ctx->size = size;
	ul->ctx->users = malloc(size * sizeof(user*));
	memset(ul->ctx->users, 0, size * sizeof(user*));

	ul->add_user = add_user;
	ul->del_user_by_fd = del_user_by_fd;
	ul->find_user_by_fd = find_user_by_fd;

	return ul;
}

void free_ul(user_list* ul)
{
	free(ul->ctx->users);
	free(ul->ctx);
	free(ul);
}

