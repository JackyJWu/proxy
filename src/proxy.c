/*
 ============================================================================
 Name        : proxy.c
 Author      : Jacky Wu
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>

/* Libraries for socket programming */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* Library for parsing strings */
#include <string.h>
#include <strings.h>

/* h_addr?! */
#include <netdb.h>

/* Clean exit! */
#include <signal.h>

int lstn_sock;

int main(void) {

	/* Initializing the Address */
	int lstn_port = 8001;
	struct sockaddr_in addr_proxy;
	addr_proxy.sin_family = AF_INET;
	addr_proxy.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_proxy.sin_port = htons(lstn_port);
	printf("Address Initialization: done.\n");

	//Creating the Listener Socket for proxy

	lstn_sock = socket(AF_INET, SOCK_STREAM,0);
	if (lstn_sock<0){
		printf("Error in socket() call.\n");
		exit(-1);
	}else{
		printf("Listening Socket creation: done.\n");
	}

	/* Binding the socket to address and port */
	int bind_status;
	bind_status = bind(lstn_sock, (struct sockaddr *) &addr_proxy,
			sizeof(struct sockaddr_in));
	if (bind_status < 0) {
		printf("Error in bind() call.\n");
		exit(-1);
	} else {
		printf("Binding: done.\n");
	}

	/* Listening on binded port number */
	int lstn_status;
	lstn_status = listen(lstn_sock, 10);
	if (lstn_status < 0) {
		printf("Error in listen() call.\n");
		exit(-1);
	}

	int data_sock;
	data_sock = accept(lstn_sock, NULL, NULL);
	if (data_sock < 0) {
		printf("Error in accept() call");
		exit(-1);
	} else {
		printf("Accepting connection request: done.\n");
	}

	return 0;
}
