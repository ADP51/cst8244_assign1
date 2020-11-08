#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/netmgr.h>
#include "../../des_controller/src/des_mva.h"

int main(int argc, char *argv[]) {
	send_t msg_send;
	response_t msg_receive;
	pid_t controller_pid;
	int coid;

	char input[10];
	int person_id;
	float weight;

	if (argc != 2) {
		perror("Incorrect number of command line args");
		return EXIT_FAILURE;
	}

	controller_pid = atoi(argv[1]);

	if((coid = ConnectAttach(ND_LOCAL_NODE, controller_pid, 2, _NTO_SIDE_CHANNEL, 0)) == -1){
		printf("ConnectAttach failed.\n");
		return EXIT_FAILURE;
	}
	while(1){
			printf("Enter the event type (ls=left scan, rs=right scan, ws=weight scale, lo=left open, ro=right open, lc=left closed, "
					"rc=right closed, gru=guard right unlock, grl=guard right lock, gll=guard left lock, glu=guard left unlock)\n");
			scanf(" %s", input);

			if(strcmp(input, "ls") == 0 || strcmp(input, "rs") == 0) {
				printf("Enter your ID: \n");
				scanf("%d", &person_id);
				msg_send.person_id = person_id;
			}
			if(strcmp(input, "ws") == 0){
				printf("Enter your weight:\n");
				scanf("%f", &weight);
				msg_send.weight = weight;
				msg_send.input = WEIGHT_SCAN;
			}
			if(strcmp(input, "lo") == 0){
				msg_send.input = LEFT_OPEN;
			}
			if(strcmp(input, "ro") == 0){
				msg_send.input = RIGHT_OPEN;
			}
			if(strcmp(input, "lc") == 0){
				msg_send.input = LEFT_CLOSE;
			}
			if(strcmp(input, "rc") == 0){
				msg_send.input = RIGHT_CLOSE;
			}
			if(strcmp(input, "glu") == 0){
				msg_send.input = GUARD_LEFT_UNLOCK;
			}
			if(strcmp(input, "gll") == 0){
				msg_send.input = GUARD_LEFT_LOCK;
			}
			if(strcmp(input, "gru") == 0){
				msg_send.input = GUARD_RIGHT_UNLOCK;
			}
			if(strcmp(input, "grl") == 0){
				msg_send.input = GUARD_RIGHT_LOCK;
			}
			if(strcmp(input, "exit") == 0){
				printf("Exiting...");
				msg_send.input = EXIT;
				if(MsgSend(coid, &msg_send, sizeof(send_t), 0, 0) == -1){
					printf("Unable to send message.");
					return EXIT_FAILURE;
				}
				return EXIT_SUCCESS;
			}

			if (MsgSend(coid, &msg_send, sizeof(msg_send) + 1, &msg_receive, sizeof(response_t)) == -1) {
				printf("MsgSend had an error.\n");
				return EXIT_FAILURE;
			}
		}
		ConnectDetach(coid);

		return EXIT_SUCCESS;
	}


