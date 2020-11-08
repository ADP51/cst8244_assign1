#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <sys/netmgr.h>
#include <sys/neutrino.h>
#include "./des_mva.h"

int main(int argc, char **argv) {

	State state = READY_STATE;
	send_t msg_received;
	response_t response;
	pid_t display_pid;
	int coid;
	int chid;
	int rcvid;

	if (argc != 2) {
		perror("Incorrect number of command line args");
		return EXIT_FAILURE;
	}

	display_pid = atoi(argv[1]);

	coid = ConnectAttach(ND_LOCAL_NODE, display_pid, 1, _NTO_SIDE_CHANNEL, 0);

	if((chid = ChannelCreate(0)) == -1) {
		printf("Error creating channel.");
		return EXIT_FAILURE;
	}

	printf("Controller PID: %d", pthread_self());

	while(1) {

		if((rcvid = MsgReceive(chid, &msg_received, sizeof(send_t), NULL)) == -1){
			printf("Could not receive message from inputs.");
			return EXIT_FAILURE;
		}

		switch(state) {
		case READY_STATE:
			 state = RIGHT_LOCK_STATE;
			 break;
		case LEFT_SCAN_STATE:
			if(msg_received.input == GUARD_LEFT_UNLOCK) {
				state = LEFT_UNLOCK_STATE;
			}
			break;
		case RIGHT_SCAN_STATE:
			if(msg_received.input == GUARD_RIGHT_UNLOCK) {
				state = RIGHT_UNLOCK_STATE;
			}
			break;
		case LEFT_UNLOCK_STATE:
			if(msg_received.input == LEFT_OPEN) {
				state = LEFT_OPEN_STATE;
			}
			break;
		case LEFT_OPEN_STATE:
			if(msg_received.input == WEIGHT_SCAN) {
				state = WEIGHT_SCAN_STATE;
			}
			break;
		case WEIGHT_SCAN_STATE:
			if(msg_received.input == LEFT_CLOSE) {
				state = LEFT_CLOSE_STATE;
			}
			break;
		case LEFT_CLOSE_STATE:
			if(msg_received.input == GUARD_LEFT_LOCK) {
				state = LEFT_LOCK_STATE;
			}
			break;
		case LEFT_LOCK_STATE:
			if(msg_received.input == GUARD_RIGHT_UNLOCK) {
				state = RIGHT_UNLOCK_STATE;
			}
			break;
		case RIGHT_UNLOCK_STATE:
			if(msg_received.input == RIGHT_OPEN) {
				state = RIGHT_OPEN_STATE;
			}
			break;
		case RIGHT_OPEN_STATE:
			if(msg_received.input == RIGHT_CLOSE) {
				state = RIGHT_CLOSE_STATE;
			}
			break;
		case RIGHT_CLOSE_STATE:
			if(msg_received.input == GUARD_RIGHT_LOCK) {
				state = RIGHT_LOCK_STATE;
			}
			break;
		case RIGHT_LOCK_STATE:
			if(msg_received.input == GUARD_RIGHT_LOCK){
				state = READY_STATE;
			}
			break;
		case EXIT_STATE:
			if(msg_received.input == EXIT){
				state = EXIT_STATE;
			}
			break;
		}

		MsgSend(coid, &msg_received, sizeof(send_t), &response, sizeof(response_t));

		if(state != EXIT_STATE){
			MsgReply(rcvid, EOK, &response, sizeof(response_t));
		} else {
			ConnectDetach(coid);
			ChannelDestroy(chid);
			break;
		}
	}

	ConnectDetach(coid);
	ChannelDestroy(chid);
	return EXIT_SUCCESS;
}
