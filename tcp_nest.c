
/*
 * TCP_NEST.C
 *
 * TCP_NEST -l<localport> -s<sleeptime> -i<buffersize> -o<buffersize> -I<idle_time> -w<wait_for_connection_time> <destmachine> -p<dest_port>
 *
 * Tcp_nest is a server.  It listens for connections and when it 
 * gets one, it creates a connection to the destination machine and
 * then acts as a go-between.  It is useful to get through firewalls
 * and to slow down connections so that you do not overwhelm slow 
 * links.
 *
 * It will exit after an hour with no connections and
 * any given connection idle over 10 minutes is closed.
 *
 * Copyright (c) 1993, Matthew Dillon
 * Copyright (c) 1993, David Muir Sharnoff
 * 
 * Insert BSD-style license agreement here
 *
 */

#define ALARMTO 3600
#define SLEEPTIME 0
#define IBUFSIZE 0
#define OBUFSIZE 0
#define IDLE 600
#define LOCALPORT 0
#define HOST NULL
#define DESTPORT 119

#define FD_SETSIZE 20
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/file.h>
#include <sys/time.h>
#include <sys/wait.h>

#include <netinet/in.h>

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <setjmp.h>
#include <ctype.h>
#include <netdb.h>

typedef unsigned char ubyte;
typedef unsigned short uword;
typedef unsigned long ulong;

struct sockaddr_in Sin;
short DDebug;
short SleepTime = SLEEPTIME;
int   IbufSize = IBUFSIZE;
int   ObufSize = OBUFSIZE;
int   IdleTime = IDLE;
int   DestPort = DESTPORT;
int   WaitTime = ALARMTO;

void copyfds();
void waitchildren();
int AlarmFunc();

main(ac, av)
int ac;
char *av[];
{
    int i;
    int fd;
    short port = LOCALPORT;
    char *host = HOST;
 
    signal(SIGALRM, AlarmFunc);

    for (i = 1; i < ac; ++i) {
	char *ptr = av[i];

	if (*ptr != '-') {
	    host = ptr;
	    continue;
	}
	ptr += 2;
	switch(ptr[-1]) {
	case 'l':
	    port = strtol(ptr, NULL, 0);
	    break;
	case 's':
	    SleepTime = strtol(ptr, NULL, 0);
	    break;
	case 'i':
	    IbufSize = strtol(ptr, NULL, 0);
	    break;
	case 'o':
	    ObufSize = strtol(ptr, NULL, 0);
	    break;
	case 'I':
	    IdleTime = strtol(ptr, NULL, 0);
	    break;
	case 'w':
	    WaitTime = strtol(ptr, NULL, 0);
	    break;
	case 'p':
	    DestPort = strtol(ptr, NULL, 0);
	    break;
	default:
	    printf("bad option: %s\n", ptr - 2);
	    break;
	}
    }
    if (port == 0 || host == NULL || DestPort == 0) {
	printf("localport, port or host missing\n");
	exit(20);
    }
    printf("port %d host %s sleep %d\n", port, host, SleepTime);

    Sin.sin_family = AF_INET;
    Sin.sin_port = htons(port);
    Sin.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((fd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
	perror("socket");
	exit(20);
    }
    if (ObufSize) {
	(void) setsockopt(fd,SOL_SOCKET, SO_SNDBUF, (char *)&ObufSize, sizeof(ObufSize));
	(void) setsockopt(fd,SOL_SOCKET, SO_RCVBUF, (char *)&ObufSize, sizeof(ObufSize));
    }
    if (bind(fd, (struct sockaddr *)&Sin, sizeof(Sin)) < 0) {
	perror("bind");
	exit(20);
    }
    if (listen(fd, 5) < 0) {
	perror("listen");
	exit(20);
    }

    /* 
     * The program is run by rsh and times out after one hour with no 
     * connection.
     */

    {
	struct sockaddr_in sin;
	int alen = sizeof(sin);
	int fd1;
	int fd2;

        if (WaitTime)
	    alarm(WaitTime);
	while ((fd1 = accept(fd, (struct sockaddr *)&sin, &alen)) >= 0) {
	    alarm(0);
	    if (fork() == 0) {
		close(fd);
		if ((fd2 = connectto(host, DestPort)) >= 0) {
		    copyfds(fd1, fd2);
		    close(fd2);
		}
		close(fd1);
		exit(0);
	    } else {
		close(fd1);
	    }
	    waitchildren(WNOHANG);
	    if (WaitTime)
		alarm(WaitTime);
	}
	waitchildren(0);
    }
}

int
AlarmFunc()
{
    fprintf(stderr, "timeout\n");
    waitchildren(0);
    exit(20);
}

void
waitchildren(opts)
int opts;
{
    union wait wdata;

    while (wait3(&wdata, opts, NULL)  > 0)
	;
}

loadhost(hostname, port)
char *hostname;
short port;
{
    bzero((char *)&Sin, sizeof(Sin));
    {
	struct hostent *host = gethostbyname(hostname);

	if (host) {
	    Sin.sin_family = host->h_addrtype;
	    bcopy(host->h_addr, &Sin.sin_addr, host->h_length);
	} else {
	    Sin.sin_family = AF_INET;
	    Sin.sin_addr.s_addr = inet_addr(hostname);
	}
    }
    Sin.sin_port = htons(port);
}

connectto(hostname, port)
char *hostname;
short port;
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (IbufSize) {
	(void) setsockopt(fd,SOL_SOCKET, SO_RCVBUF, (char *)&IbufSize, sizeof(IbufSize));
	(void) setsockopt(fd,SOL_SOCKET, SO_SNDBUF, (char *)&IbufSize, sizeof(IbufSize));
    }

    loadhost(hostname, port);
    if (connect(fd, (struct sockaddr *)&Sin, sizeof(Sin)) < 0) {
	close(fd);
	fd = -1;
    }
    return(fd);
}

/*
 * copyfds() - generic full duplex descriptor copy
 *
 */

void
copyfds(fd1, fd2)
{
    static fd_set RFds, WFds, XFds;
    static unsigned char buf1[512];
    static unsigned char buf2[512];
    int n1 = 0;
    int n2 = 0;
    short fd1_rflag = 1;
    short fd1_wflag = 0;
    short fd2_rflag = 1;
    short fd2_wflag = 0;
    struct timeval tv;

    fcntl(fd1, F_SETFL, FNDELAY);
    fcntl(fd2, F_SETFL, FNDELAY);

    for (;;) {
	if (fd1_rflag)
	    FD_SET(fd1, &RFds);
	else
	    FD_CLR(fd1, &RFds);
	if (fd2_rflag)
	    FD_SET(fd2, &RFds);
	else
	    FD_CLR(fd2, &RFds);

	if (fd1_wflag)
	    FD_SET(fd1, &WFds);
	else
	    FD_CLR(fd1, &WFds);
	if (fd2_wflag)
	    FD_SET(fd2, &WFds);
	else
	    FD_CLR(fd2, &WFds);

	FD_SET(fd1, &XFds);
	FD_SET(fd2, &XFds);

	/*
	 * 10 minute timeout closes connection
	 */

	tv.tv_sec = IdleTime;
	tv.tv_usec = 0;
	if (select(FD_SETSIZE, &RFds, &WFds, &XFds, &tv) == 0)
	    break;

	/*
	 * Exceptional condition on descriptor, exit
	 */

	if (FD_ISSET(fd1, &XFds))
	    break;
	if (FD_ISSET(fd2, &XFds))
	    break;

	/*
	 * Data available for reading from FD1
	 */

	if (FD_ISSET(fd1, &RFds)) {
	    int r;

	    r = read(fd1, buf1, sizeof(buf1) - n1);

	    if (r < 0) {
		perror("read");
		break;
	    }
	    if (r == 0)
		break;
	    n1 += r;
	}

	/*
	 * Data available for reading from FD2
	 */

	if (FD_ISSET(fd2, &RFds)) {
	    int r;

	    r = read(fd2, buf2, sizeof(buf2) - n2);

	    if (r < 0) {
		perror("read");
		break;
	    }
	    if (r == 0)
		break;
	    n2 += r;
	}

	/*
	 * Data ready to write
	 */

	if (FD_ISSET(fd2, &WFds) || (fd2_wflag == 0 && n1)) {
	    int r;

	    r = write(fd2, buf1, n1);
	    if (SleepTime > 0 && n1 > sizeof(buf1) / 2)
		sleep(SleepTime);
	    if (r == n1) {
		fd1_rflag = 1;
		fd2_wflag = 0;
		n1 = 0;
	    } else {
		fd1_rflag = 0;
		fd2_wflag = 1;
		if (r > 0) {
		    bcopy(buf1 + r, buf1, n1 - r);
		    n1 -= r;
		}
	    }
	}

	/*
	 * Data ready to write
	 */

	if (FD_ISSET(fd1, &WFds) || (fd1_wflag == 0 && n2)) {
	    int r;

	    r = write(fd1, buf2, n2);
	    if (SleepTime > 0 && n2 > sizeof(buf2) / 2)
		sleep(SleepTime);
	    if (r == n2) {
		fd2_rflag = 1;
		fd1_wflag = 0;
		n2 = 0;
	    } else {
		fd2_rflag = 0;
		fd1_wflag = 1;
		if (r > 0) {
		    bcopy(buf2 + r, buf2, n2 - r);
		    n2 -= r;
		}
	    }
	}
    }
}

