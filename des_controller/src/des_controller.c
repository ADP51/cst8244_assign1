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

		rcvid = MsgReceive(chid, &msg_received, sizeof(send_t), NULL);

		if(msg_received.input == EXIT) {
			ChannelDestroy(chid);
			return EXIT_SUCCESS;
		}

		switch(state) {
		case READY_STATE:
			if(msg_received.input == LEFT_SCAN) {
				state = LEFT_SCAN_STATE;
			} else if (msg_received.input == RIGHT_SCAN) {
				state = RIGHT_SCAN_STATE;
			}
			 break;
		case LEFT_SCAN_STATE:
			if(msg_received.input == GUARD_LEFT_UNLOCK) {
				state = ENTER_LEFT_UNLOCK_STATE;
			}
			break;
		case RIGHT_SCAN_STATE:
			if(msg_received.input == GUARD_RIGHT_UNLOCK) {
				state = LEAVE_RIGHT_UNLOCK_STATE;
			}
			break;
		case ENTER_LEFT_UNLOCK_STATE:
			if(msg_received.input == LEFT_OPEN) {
				state = ENTER_LEFT_OPEN_STATE;
			}
			break;
		case ENTER_LEFT_OPEN_STATE:
			if(msg_received.input == WEIGHT_SCAN) {
				state = ENTER_WEIGHTSCAN_STATE;
			}
			break;
		case ENTER_WEIGHTSCAN_STATE:
			if(msg_received.input == LEFT_CLOSE) {
				state = ENTER_LEFT_CLOSE_STATE;
			}
			break;
		case ENTER_LEFT_CLOSE_STATE:
			if(msg_received.input == GUARD_LEFT_LOCK) {
				state = ENTER_LEFTLOCK_STATE;
			}
			break;
		case ENTER_LEFTLOCK_STATE:
			if(msg_received.input == GUARD_RIGHT_UNLOCK) {
				state = ENTER_RIGHT_UNLOCK_STATE;
			}
			break;
		case ENTER_RIGHT_UNLOCK_STATE:
			if(msg_received.input == RIGHT_OPEN) {
				state = ENTER_RIGHT_OPEN_STATE;
			}
			break;
		case ENTER_RIGHT_OPEN_STATE:
			if(msg_received.input == RIGHT_CLOSE) {
				state = ENTER_RIGHT_CLOSE_STATE;
			}
			break;
		case ENTER_RIGHT_CLOSE_STATE:
			if(msg_received.input == GUARD_RIGHT_LOCK) {
				state = READY_STATE;
			}
			break;
		case LEAVE_RIGHT_UNLOCK_STATE:
			if(msg_received.input == RIGHT_OPEN) {
				state = LEAVE_RIGHT_OPEN_STATE;
			}
			break;
		case LEAVE_RIGHT_OPEN_STATE:
			if(msg_received.input == WEIGHT_SCAN) {
				state = LEAVE_WEIGHTSCAN_STATE;
			}
			break;
		case LEAVE_WEIGHTSCAN_STATE:
			if(msg_received.input == RIGHT_CLOSE) {
				state = LEAVE_RIGHT_CLOSE_STATE;
			}
			break;
		case LEAVE_RIGHT_CLOSE_STATE:
			if(msg_received.input == GUARD_RIGHT_LOCK) {
				state = LEAVE_RIGHTLOCK_STATE;
			}
			break;
		case LEAVE_RIGHTLOCK_STATE:
			if(msg_received.input == GUARD_LEFT_UNLOCK) {
				state = LEAVE_LEFT_UNLOCK_STATE;
			}
			break;
		case LEAVE_LEFT_UNLOCK_STATE:
			if(msg_received.input == LEFT_OPEN) {
				state = LEAVE_LEFT_OPEN_STATE;
			}
			break;
		case LEAVE_LEFT_OPEN_STATE:
			if(msg_received.input == LEFT_CLOSE) {
				state = LEAVE_LEFT_CLOSE_STATE;
			}
			break;
		case LEAVE_LEFT_CLOSE_STATE:
			if(msg_received.input == GUARD_LEFT_LOCK) {
				state = READY_STATE;
			}
			break;
		}

		MsgSend(coid, &msg_received, sizeof(send_t), &response, sizeof(response_t));
	}

}
