/******************
 * Filename: des_inputs.c
 * Date: November 9, 2020
 * Course: CST8244 Real-Time Programming
 * Author: Andrew Palmer, Karim Tahan
 * Functions: int main(int argc, char *argv[])
 *
 * Prompts the user for a command and sends the input to des_controller.
 *****************/

#include <stdio.h>
#include <stdlib.h>
#include <process.h>
#include <string.h>
#include <errno.h>
#include <sys/neutrino.h>
#include <sys/iofunc.h>
#include <sys/dispatch.h>
#include <sys/netmgr.h>
#include "../../des_controller/src/des_mva.h"

send_t msg_send;
response_t msg_receive;
pid_t controller_pid;
int coid;

int main(int argc, char *argv[]) {

	char input[10];
	int person_id;
	float weight;

	if (argc != 2) {
		perror("Incorrect number of command line args");
		return EXIT_FAILURE;
	}

	controller_pid = atoi(argv[1]);

    if ((coid = name_open(ATTACH_POINT_CONTROLLER, 0)) == -1) {
    	perror("name_open failed.");
        return EXIT_FAILURE;
    }

		printf(
				"Enter the event type (ls=left scan, rs=right scan, ws=weight scale, lo=left open, ro=right open, lc=left closed, "
						"rc=right closed, gru=guard right unlock, grl=guard right lock, gll=guard left lock, glu=guard left unlock)\n");

	while (1) {

		scanf(" %s", input);

		if (strcmp(input, "ls") == 0 || strcmp(input, "rs") == 0) {
			printf("Enter your ID: \n");
			scanf("%d", &person_id);
			msg_send.person_id = person_id;
			if (strcmp(input, "ls") == 0) {
				msg_send.input = LEFT_SCAN;
			} else {
				msg_send.input = RIGHT_SCAN;
			}
		}
		if (strcmp(input, "ws") == 0) {
			printf("Enter your weight:\n");
			scanf("%f", &weight);
			msg_send.weight = weight;
			msg_send.input = WEIGHT_SCAN;
		}
		if (strcmp(input, "lo") == 0) {
			msg_send.input = LEFT_OPEN;
		}
		if (strcmp(input, "ro") == 0) {
			msg_send.input = RIGHT_OPEN;
		}
		if (strcmp(input, "lc") == 0) {
			msg_send.input = LEFT_CLOSE;
		}
		if (strcmp(input, "rc") == 0) {
			msg_send.input = RIGHT_CLOSE;
		}
		if (strcmp(input, "glu") == 0) {
			msg_send.input = GUARD_LEFT_UNLOCK;
		}
		if (strcmp(input, "gll") == 0) {
			msg_send.input = GUARD_LEFT_LOCK;
		}
		if (strcmp(input, "gru") == 0) {
			msg_send.input = GUARD_RIGHT_UNLOCK;
		}
		if (strcmp(input, "grl") == 0) {
			msg_send.input = GUARD_RIGHT_LOCK;
		}
		if (strcmp(input, "exit") == 0) {
			msg_send.input = EX_INPUT;
			if (MsgSend(coid, &msg_send, sizeof(send_t), 0, 0) == -1) {
				printf("\nUnable to send message.\n");
				name_close(coid);
				return EXIT_FAILURE;
			}

			name_close(coid);
			return EXIT_SUCCESS;
		}

		if (MsgSend(coid, &msg_send, sizeof(msg_send) + 1, &msg_receive,
				sizeof(response_t)) == -1) {
			printf("MsgSend had an error.\n");
			return EXIT_FAILURE;
		}
	}

	name_close(coid);
	return EXIT_SUCCESS;
}

