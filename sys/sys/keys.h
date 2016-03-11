#ifndef SYS_H_KEYS
#define SYS_H_KEYS
#include <sys/types.h>
/*
  Static array that holds values for users along with their corresponding keys
*/

int get_keys_by_uid (uid_t uid, int *k0, int *k1);


#endif
