#include <stdio.h>
#include <stdlib.h>
#include "./des_mva.h"

int main(void) {

	enum State state = START_STATE;

	while(1) {
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
