#ifndef DES_MVA_H_
#define DES_MVA_H_

#define NUM_STATES 13
typedef enum {
    START_STATE =               	0,
    WEIGHT_SCAN_STATE =   		1,
    LEFT_SCAN_STATE = 			2,
    RIGHT_SCAN_STATE = 			3,
    LEFT_UNLOCK_STATE =   		4,
    LEFT_OPEN_STATE =     		5,
    LEFT_CLOSE_STATE =    		6,
    LEFT_LOCK_STATE =      		7,
    RIGHT_UNLOCK_STATE =  		8,
    RIGHT_OPEN_STATE =    		9,
    RIGHT_CLOSE_STATE =   		10,
    RIGHT_LOCK_STATE =    		11,
    EXIT = 				12
} State;

#define NUM_INPUTS 11
typedef enum {
    LEFT_SCAN = 			0,
    RIGHT_SCAN = 			1,
    GUARD_LEFT_UNLOCK = 		2,
    LEFT_OPEN = 			3,
    LEFT_CLOSE = 			4,
    GUARD_LEFT_LOCK = 			5,
    WEIGHT_SCAN = 			6,
    GUARD_RIGHT_UNLOCK = 		7,
    RIGHT_OPEN = 			8,
    RIGHT_CLOSE = 			9,
    GUARD_RIGHT_LOCK = 			10
} Input;

#define NUM_OUTPUTS 13
typedef enum {
    START_MSG =				0,
	READY_MSG = 			1,
	LS_MSG =			2,
	RS_MSG =			3,
	LEFTDOOR_UNLOCK_MSG =		4,
	LEFTDOOR_OPEN_MSG =		5,
	LEFTDOOR_CLOSED_MSG =		6,
	LEFTDOOR_LOCKED_MSG = 		7,
	WEIGHTSCAN_MSG =		8,
	RIGHTDOOR_UNLOCK_MSG = 		9,
	RIGHTDOOR_OPEN_MSG =		10,
	RIGHTDOOR_CLOSED_MSG =		11,
	RIGHTDOOR_LOCKED_MSG = 		12,
} Output;

const char *outMessage[NUM_OUTPUTS] = {
		"Controller PID: ",
		"Ready for Entry",
		"Enter Person ID:",
		"Person ID entered: ",
		"Left door unlocked",
		"Left door opened",
		"Left door closed",
		"Left door locked",
		"Weight scan",
		"Right door unlocked",
		"Right door opened",
		"Right door closed",
		"Right door locked"
};

const char *inMessage[NUM_INPUTS] = {
		"ls",
		"rs",
		"glu",
		"lo",
		"lc",
		"gll",
		"ws",
		"gru",
		"ro",
		"rc",
		"grl"
};


struct response
{
	double answer;
	int statusCode; // [OK, UNDEFINED, INVALID_OPERATOR, OVERFLOW]
	char errorMsg[128];
} typedef response_t;

struct send
{
	char state;
	int weight;
	int person_id;
} typedef send_t;

#endif
