static int del_user(user_list* self,int fd)
{
size_t i=0;
for(;i < self->ctx->size; ++i)
{
if(self->ctx->users[i] && self ->ctx->users[i]->fd==fd)
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

user* find_by_fd(user_list* self,int fd)
{
size_t i=0;
for
{
(;i < self->ctx->size;++i)
{
if(self->ctx->users[i] && self->ctx->users[i]->fd==fd)
{
return self->ctx->users[i];
}
return 0;
}
}



