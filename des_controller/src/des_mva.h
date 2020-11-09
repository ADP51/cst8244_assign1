#ifndef DES_MVA_H_
#define DES_MVA_H_

#define NUM_STATES 13
typedef enum {
	READY_STATE = 0,
	LEFT_SCAN_STATE = 1,
	RIGHT_SCAN_STATE = 2,
	WEIGHT_SCAN_STATE = 3,
	LEFT_OPEN_STATE = 4,
	RIGHT_OPEN_STATE = 5,
	LEFT_CLOSE_STATE = 6,
	RIGHT_CLOSE_STATE = 7,
	LEFT_LOCK_STATE = 8,
	RIGHT_LOCK_STATE = 9,
	LEFT_UNLOCK_STATE = 10,
	RIGHT_UNLOCK_STATE = 11,
	EXIT_STATE = 12
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

#define NUM_OUTPUTS 12
typedef enum {
	READY_MSG = 0,
	LEFT_SCAN_MSG = 1,
	RIGHT_SCAN_MSG = 2,
	LEFT_UNLOCK_MSG = 3,
	LEFT_OPEN_MSG = 4,
	LEFT_CLOSE_MSG = 5,
	LEFT_LOCK_MSG = 6,
	WEIGHT_SCAN_MSG = 7,
	RIGHT_UNLOCK_MSG = 8,
	RIGHT_OPEN_MSG = 9,
	RIGHT_CLOSE_MSG = 10,
	RIGHT_LOCK_MSG = 11,
} Output_t;

const char *outMessage[NUM_OUTPUTS] = {
		"Controller PID: "
		"Person scanned ID. ID: ",
		"Person weighed. Weight: ",
		"Left door Open.",
		"Right door Open.",
		"Left door Closed.",
		"Right door Closed.",
		"Right door locked by Guard. ",
		"Right door unlocked by Guard. ",
		"Left door locked by Guard. ",
		"Left door unlocked by Guard. ",
		"Exiting Door Entry System..."
};

const char *inMessage[NUM_INPUTS] = { "ls", "rs", "glu", "lo", "lc", "gll",
		"ws", "gru", "ro", "rc", "grl", "exit" };

struct response {
	int statusCode; // [OK, UNDEFINED, INVALID_OPERATOR, OVERFLOW]
	char errorMsg[128];
}typedef response_t;

struct send {
	input_t input;
	float weight;
	int person_id;
}typedef send_t;

#endif
