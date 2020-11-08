#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <process.h>
#include "../../des_controller/src/des_mva.h"

int main(void) {
	send_t msg_received;
	response_t response;
	int chid;
	int rcvid;

	if((chid = ChannelCreate(0)) == -1) {
		printf("Error creating channel.");
		return EXIT_FAILURE;
	}

	printf("Display's PID: %d\n", getpid());

	while(1){
//		Call MsgReceive() to receive Display object from controller
		if((rcvid = MsgReceive(chid, &msg_received, sizeof(send_t), NULL)) == -1){
			printf("Error receiving message from controller.");
			return EXIT_FAILURE;
		}

//		Call MsgReply(), sending EOK back to the controller
		if(MsgReply(rcvid, EOK, &response, sizeof(response_t)) == -1){
			printf("Unable to reply to message.");
			return EXIT_FAILURE;
		}

//		IF message == ID_SCAN THEN
		if(msg_received.input == LEFT_SCAN || msg_received.input == RIGHT_SCAN){
			//Print person has been scanned entering (or leaving) the building and display the person's ID
			if(msg_received.input == LEFT_SCAN){
				printf("%s %d", outMessage[LEFT_SCAN], msg_received.person_id);
			} else {
				printf("%s %d", outMessage[RIGHT_SCAN], msg_received.person_id);
			}
		} else if(msg_received.input == WEIGHT_SCAN){ //ELSE IF message = WEIGHED THEN
			//Print person has been weighed and their weight
			printf("Person ID: %d has been weighed: %f.", msg_received.person_id, msg_received.weight);
		} else {
			//		Print message to Neutrino console (i.e. stdout)
			printf("%s", outMessage[msg_received.input]);
		}

		if(msg_received.input == EXIT){ //IF message == EXIT THEN
			break;
		}

	}

	ChannelDestroy(chid);
	return EXIT_SUCCESS;

}
