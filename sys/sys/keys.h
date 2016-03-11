#ifndef SYS_H_KEYS
#define SYS_H_KEYS
/*
  Static array that holds values for users along with their corresponding keys
*/

struct user_keys {
	uid_t user;
	unsigned int user_count;
	unsigned int k0;
	unsigned int k1;
};

typedef struct user_keys user;

#endif
