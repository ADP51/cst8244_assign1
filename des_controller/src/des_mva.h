#ifndef DES_MVA_H_
#define DES_MVA_H_

#define NUM_STATES 20
typedef enum {
	READY_STATE = 0,
	WEIGHT_SCAN_STATE = 1,
	LEFT_SCAN_STATE = 2,
	RIGHT_SCAN_STATE = 3,
	ENTER_LEFT_UNLOCK_STATE = 4,
	ENTER_RIGHT_UNLOCK_STATE = 5,
	ENTER_LEFT_OPEN_STATE = 6,
	ENTER_RIGHT_OPEN_STATE = 7,
	ENTER_WEIGHTSCAN_STATE = 8,
	ENTER_LEFTCLOSE_STATE = 9,
	ENTER_LEFTLOCK_STATE = 10,
	ENTER_RIGHT_CLOSE_STATE = 11,
	LEAVE_RIGHT_UNLOCK_STATE = 12,
	LEAVE_RIGHT_OPEN_STATE = 13,
	LEAVE_WEIGHTSCAN_STATE = 14,
	LEAVE_RIGHT_CLOSE_STATE = 15,
	LEAVE_RIGHTLOCK_STATE = 16,
	LEAVE_LEFT_UNLOCK_STATE = 17,
	LEAVE_LEFT_OPEN_STATE = 18,
	LEAVE_LEFT_CLOSE_STATE = 19,
} State;

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
	EXIT = 11
} input_t;

#define NUM_OUTPUTS 13
typedef enum {
	READY_MSG = 1,
	LS_MSG = 2,
	RS_MSG = 3,
	LEFTDOOR_UNLOCK_MSG = 4,
	LEFTDOOR_OPEN_MSG = 5,
	LEFTDOOR_CLOSED_MSG = 6,
	LEFTDOOR_LOCKED_MSG = 7,
	WEIGHTSCAN_MSG = 8,
	RIGHTDOOR_UNLOCK_MSG = 9,
	RIGHTDOOR_OPEN_MSG = 10,
	RIGHTDOOR_CLOSED_MSG = 11,
	RIGHTDOOR_LOCKED_MSG = 12,
} Output_t;

const char *outMessage[NUM_OUTPUTS] = { "Controller PID:", "Ready for Entry\n",
		"Person ID entered:", "Person ID Leaving:", "Left door unlocked\n", "Left door opened\n",
		"Left door closed\n", "Left door locked\n", "Weight scan\n",
		"Right door unlocked\n", "Right door opened\n", "Right door closed\n",
		"Right door locked\n" };

const char *inMessage[NUM_INPUTS] = { "ls", "rs", "glu", "lo", "lc", "gll",
		"ws", "gru", "ro", "rc", "grl", "exit" };

struct response {
	int statusCode; // [OK, UNDEFINED, INVALID_OPERATOR, OVERFLOW]
	char errorMsg[128];
}typedef response_t;

struct send {
	input_t input;
	int weight;
	int person_id;
}typedef send_t;

#endif
