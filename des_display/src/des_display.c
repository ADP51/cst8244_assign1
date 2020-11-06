#include <stdio.h>
#include <stdlib.h>
#include "../../des_controller/src/des_mva.h"

int main(void) {
	send_t = msg_received;
	resposne_t = response;
	int chid = ChannelCreate(0);

	if(chid < 0) {
		return EXIT_FAILURE;
	}

	printf("Display's PID: %d\n", getpid());

	while(1){
//		Call MsgReceive() to receive Display object from controller
		rcvid = MsgReceive(chid, &msg_received, size_of(send_t), NULL);

//		Call MsgReply(), sending EOK back to the controller
		MsgReply(rcvid, state, &response, size_of(response_t));

//		IF message == ID_SCAN THEN
		if(msg_received.state == LEFT_SCAN || msg_received.state == RIGHT_SCAN){
			//Print person has been scanned entering (or leaving) the building and display the person's ID
			if(msg_received.state == LEFT_SCAN){
				printf("%s %d", outMessage[LEFT_SCAN], msg_received.person_id);
			} else {
				printf("%s %d", outMessage[RIGHT_SCAN], msg_received.person_id);
			}
		} else if(msg_received.state == WEIGHT_SCAN){ //ELSE IF message = WEIGHED THEN
			//Print person has been weighed and their weight
			printf("Person ID: %d has been weighed: %f.", msg_received.person_id, msg_received.weight);
		} else {
			//		Print message to Neutrino console (i.e. stdout)
			printf("%s", outMessage[msg_received.state]);
		}

		if(msg_received.state == EXIT){ //IF message == EXIT THEN
			break;
		}

	}

	ChannelDestroy(chid);
	return EXIT_SUCCESS;

}
