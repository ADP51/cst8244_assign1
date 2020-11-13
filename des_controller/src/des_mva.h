/******************
 * Filename: des_mva.h
 * Date: November 9, 2020
 * Course: CST8244 Real-Time Programming
 * Author: Andrew Palmer, Karim Tahan
 *
 * Contains lists of transitions, states, in and out messages, the response and send structs.
 *****************/


#ifndef DES_MVA_H_
#define DES_MVA_H_

#define NAME_ATTACH_DISPLAY "des_display"
#define NAME_ATTACH_CONTROLLER "des_controller"

// State transitions
#define NUM_STATES 20
typedef enum {
	READY_STATE = 0,
	LEFT_SCAN_STATE = 1,
	RIGHT_SCAN_STATE = 2,
	ENTER_LEFT_UNLOCK_STATE = 3,
	ENTER_RIGHT_UNLOCK_STATE = 4,
	ENTER_LEFT_OPEN_STATE = 5,
	ENTER_RIGHT_OPEN_STATE = 6,
	ENTER_WEIGHTSCAN_STATE = 7,
	ENTER_LEFT_CLOSE_STATE = 8,
	ENTER_LEFTLOCK_STATE = 9,
	ENTER_RIGHT_CLOSE_STATE = 10,
	LEAVE_RIGHT_UNLOCK_STATE = 11,
	LEAVE_RIGHT_OPEN_STATE = 12,
	LEAVE_WEIGHTSCAN_STATE = 13,
	LEAVE_RIGHT_CLOSE_STATE = 14,
	LEAVE_RIGHTLOCK_STATE = 15,
	LEAVE_LEFT_UNLOCK_STATE = 16,
	LEAVE_LEFT_OPEN_STATE = 17,
	LEAVE_LEFT_CLOSE_STATE = 18,
	EXIT_STATE = 19
} State;

// Possible states
#define NUM_INPUTS 12
typedef enum {
	LEFT_SCAN = 0,
	RIGHT_SCAN = 1,
	GUARD_LEFT_UNLOCK = 2,
	LEFT_OPEN = 3,
	LEFT_CLOSE = 4,
	GUARD_LEFT_LOCK = 5,
	WEIGHT_SCAN = 6,
	GUARD_RIGHT_UNLOCK = 7,
	RIGHT_OPEN = 8,
	RIGHT_CLOSE = 9,
	GUARD_RIGHT_LOCK = 10,
	EX_INPUT = 11
} input_t;

// State message indexes
#define NUM_OUTPUTS 12
typedef enum {
	READY_MSG = 0,
	SCAN_MSG = 1,
	WEIGHT_SCAN_MSG= 2,
	LEFT_OPEN_MSG = 3,
	RIGHT_OPEN_MSG = 4,
	LEFT_CLOSE_MSG = 5,
	RIGHT_CLOSE_MSG = 6,
	LEFT_UNLOCK_MSG = 7,
	RIGHT_UNLOCK_MSG = 8,
	RIGHT_LOCK_MSG = 9,
	LEFT_LOCK_MSG = 10,
	EXIT_MSG = 11
} Output_t;

// Messages to be output to des_display
const char *outMessage[NUM_OUTPUTS] = {
		"Controller PID: ",
		"Person scanned ID. ID: ",
		"Person weighed. Weight: ",
		"Left door Open.",
		"Right door Open.",
		"Left door Closed.",
		"Right door Closed.",
		"Left door unlocked by Guard. ",
		"Right door unlocked by Guard. ",
		"Right door locked by Guard. ",
		"Left door locked by Guard. ",
		"Exiting Door Entry System..."
};

struct response {
	int statusCode;
	char errorMsg[128];
}typedef response_t;

struct send {
	input_t input;
	float weight;
	int person_id;
}typedef send_t;

#endif
