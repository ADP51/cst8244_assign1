#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/neutrino.h>
#include "./des_mva.h"

int main(void) {

	enum State state = READY_STATE;
	send_t msg_send;
	response_t msg_receive;
	int coid;
	int rcvid;

	coid = ConnectAttach(ND_LOCAL_NODE, controller_pid, 1, _NTO_SIDE_CHANNEL, 0);
	int chid = ChannelCreate(0);

	while(1) {

		rcvid = MsgReceive(chid, &msg_received, size_of(send_t), NULL);
		switch(state) {
		case READY_STATE:
			 break;
		case LEFT_SCAN_STATE:
			break;
		case RIGHT_SCAN_STATE:
			break;
		case ENTER_LEFT_UNLOCK_STATE:
			break;
		case ENTER_RIGHT_UNLOCK_STATE:
			break;
		case ENTER_LEFT_OPEN_STATE:
			break;
		case ENTER_RIGHT_OPEN_STATE:
			break;
		case ENTER_WEIGHTSCAN_STATE:
			break;
		case ENTER_LEFTCLOSE_STATE:
			break;
		case ENTER_LEFTLOCK_STATE:
			break;
		case ENTER_RIGHT_UNLOCK_STATE:
			break;
		case ENTER_RIGHT_OPEN_STATE:
			break;
		case ENTER_RIGHT_CLOSE_STATE:
			break;
		case LEAVE_RIGHT_UNLOCK_STATE:
			break;
		case LEAVE_RIGHT_OPEN_STATE:
			break;
		case LEAVE_WEIGHTSCAN_STATE:
			break;
		case LEAVE_RIGHT_CLOSE_STATE:
			break;
		case LEAVE_RIGHTLOCK_STATE:
			break;
		case LEAVE_LEFT_UNLOCK_STATE:
			break;
		case LEAVE_LEFT_OPEN_STATE:
			break;
		case LEAVE_LEFT_CLOSE_STATE:
			break;
		}
	}
}
