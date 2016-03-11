#include <sys/sysproto.h>
#include <sys/proc.h>

#include <sys/types.h>
#include <sys/systm.h>

#include <sys/proc.h>
#include <sys/ucred.h>
#include <sys/keys.h>

//struct declarations
#ifndef _SYS_SYSPROTO_H_
struct setkey_args {
   unsigned int k0;
   unsigned int k1;
};
#endif

#define KEYSTORE_LENGTH 20

struct user_keys {
	uid_t user;
	unsigned int k0;
	unsigned int k1;
	int valid;
};

struct key_store {
	struct user_keys keylist[KEYSTORE_LENGTH];
	int len;
};

static struct key_store keys;

int sys_setkey(struct thread *td, struct setkey_args *args) {
	//check uid via ucred
	uid_t userID;
	int i, start;
	struct user_keys *key, *first_invalid = NULL;
	userID = (td->td_ucred->cr_uid);
	if (args->k0 || args->k1)
		if (keys.len == KEYSTORE_LENGTH)
			return 1;

	for (i = 0; i < KEYSTORE_LENGTH; i++)
	{
		key = &(keys.keylist[i]);
		if (!key->valid && !first_invalid)
			first_invalid = key;
		if (key->user == userID)
			first_invalid = key;
	}
	
	//fill out user_keys with relevant data
	start = first_invalid->valid;
	first_invalid->user = userID;
	first_invalid->k0 = args->k0;
	first_invalid->k1 = args->k1;
	first_invalid->valid = args->k0 || args->k1;
	keys.len += first_invalid->valid - start;

	for (i = 0; i < KEYSTORE_LENGTH; i++)
	{
		key = &(keys.keylist[i]);
		printf ("uid: %d ; k0: %d ; k1: %d ; valid: %d\n", key->user, key->k0, key->k1, key->valid);
	}
   
	printf("uid: %d\n", userID);
	return 0;
}

int get_keys_by_uid (uid_t uid, int *k0, int *k1)
{
	int i;
	for (i = 0; i < KEYSTORE_LENGTH; i++)
	{
		if (keys.keylist[i].valid && keys.keylist[i].user == uid)
		{
			*k0 = keys.keylist[i].k0;
			*k1 = keys.keylist[i].k1;
			return 1;
		}
	}
	return 0;
}








