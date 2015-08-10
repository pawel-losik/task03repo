#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/epoll.h>
#include <arpa/inet.h>

int handle_server_fd(int srv_fd, int epoll_fd);
void handle_client(struct epoll_event* e, int epoll_fd);
void clean_client(int fd, int epoll_fd);
size_t rcv_msg(int fd, char** msg);
//void handle_login(const char* msg,size_t len,int fd,user_list* lista)

int main(int argc, const char *argv[])
{
	int i = 0;

	int srv_fd = -1;
	int epoll_fd = -1;

	struct sockaddr_in srv_addr;
	struct epoll_event e, es[2];

	memset(&srv_addr, 0, sizeof(srv_addr));
	memset(&e, 0, sizeof(e));

	srv_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (srv_fd < 0) {
		printf("Cannot create socket\n");
		return 1;
	}

	srv_addr.sin_family = AF_INET;
	srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	srv_addr.sin_port = htons(5556);
	if (bind(srv_fd, (struct sockaddr*) &srv_addr, sizeof(srv_addr)) < 0) {
		printf("Cannot bind socket\n");
		close(srv_fd);
		return 1;
	}

	if (listen(srv_fd, 1) < 0) {
		printf("Cannot listen\n");
		close(srv_fd);
		return 1;
	}

	epoll_fd = epoll_create(2);
	if (epoll_fd < 0) {
		printf("Cannot create epoll\n");
		close(srv_fd);
		return 1;
	}

	e.events = EPOLLIN;
	e.data.fd = srv_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, srv_fd, &e) < 0) {
		printf("Cannot add server socket to epoll\n");
		close(epoll_fd);
		close(srv_fd);
		return 1;
	}

	for(;;) {
		i = epoll_wait(epoll_fd, es, 2, -1);
		if (i < 0) {
			printf("Cannot wait for events\n");
			close(epoll_fd);
			close(srv_fd);
			return 1;
		}

		for (--i; i > -1; --i) {
			if (es[i].data.fd == srv_fd) {
				if (handle_server_fd(srv_fd, epoll_fd) < 0) {
					return 1;
				}
			} else {
				handle_client(&es[i], epoll_fd);
			}
		}
	}

	return 0;
}

int handle_server_fd(int srv_fd, int epoll_fd)
{
	int cli_fd = -1;
	struct sockaddr_in cli_addr;
	socklen_t cli_addr_len = sizeof(struct sockaddr_in);
	struct epoll_event e;

	memset(&cli_addr, 0, cli_addr_len);
	cli_fd = accept(srv_fd, (struct sockaddr*) &cli_addr, &cli_addr_len);
	if (cli_fd < 0) {
		printf("Cannot accept client\n");
		close(epoll_fd);
		close(srv_fd);
		return -1;
	}

	memset(&e, 0, sizeof(struct epoll_event));
	e.events = EPOLLIN;
	e.data.fd = cli_fd;
	if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, cli_fd, &e) < 0) {
		printf("Cannot accept client\n");
		close(epoll_fd);
		close(srv_fd);
		return -1;
	}

	return 0;
}

void handle_client(struct epoll_event* e, int epoll_fd)
{
	if ( (e->events & EPOLLERR) || (e->events & EPOLLHUP) || (e->events & EPOLLRDHUP) ) {
		clean_client(e->data.fd, epoll_fd);
	}
	else if (e->events & EPOLLIN) {
		char* msg = 0;
		size_t len = rcv_msg(e->data.fd, &msg);
		if (len) {
			switch (msg[0]) {
			case '2':
				//TODO: handle_login(...)
				
				break;
			case '6':
				//TODO: handle_userlist(...)
				break;
			default:
				//TODO: error handling
				//exit(1);

				break;
			}
		}
	}
	else {
		//unknown event
		clean_client(e->data.fd, epoll_fd);
	}
}
void handle_login(const char* msg,size_t len,int fd,user_list* ul)
{
	size_t size = strlen(msg);
	char* temp = malloc(size * sizeof(char));
	strncpy(temp,msg+2,size-2);
	temp[size] = 0;
	user *ptr = malloc(sizeof(user));
	ptr -> fd = fd;
	ptr -> nick = temp;

	if(!(ul->add_user(ul,ptr)))
		{
		char* Ack = "1.0"
		len=strlen(Ack)+1;
		write(fd,&len,sizeof(size_t));
		write(fd,Ack,len);
		}
	else
		{
		char* NAck = "1.1 Blad logowania";
		len = strlen(NAck)+1;
		write(fd,&len,sizeof(size_t));
		write(fd,NAck,len)
		}
}

void clean_client(int fd, int epoll_fd)
{
	//TODO remove from the list
	del_user_by_fd(user_list* ul,int fd)
	{
	
	}

	epoll_ctl(epoll_fd, EPOLL_CTL_DEL, fd, 0);
	close(fd);
}
 
size_t rcv_msg(int fd, char** msg)
{
	size_t res = 0;
	//TODO - Done
	if(read(fd,&res,sizeof(size_t) != sizeof(size_t)
		{
		return 0;	
		}
	(*msg) = malloc((res+1) * sizeof(char));
	(*msg)[res] = 0;
	if(read(fd,(*msg),res)!=res)
		{
		free(*msg);
		*msg=0;
		return 0;
		}		

}

