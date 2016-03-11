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

//Already declared in the header file, so not needed??
/*struct user_keys {
	uid_t user;
	unsigned int k0;
	unsigned int k1;
}*/

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
	int i;
	struct user_keys *key;
	userID = (td->td_ucred->cr_uid);

	for (i = 0; i < KEYSTORE_LENGTH; i++)
	{
		key = &(keys.keylist[i]);
		if (!key->valid)
			break;
	}
	
	//fill out user_keys with relevant data
	key->user = userID;
	key->k0 = args->k0;
	key->k1 = args->k1;
	key->valid = 1;

	for (i = 0; i < KEYSTORE_LENGTH; i++)
	{
		key = &(keys.keylist[i]);
		printf ("uid: %d ; k0: %d ; k1: %d\n", key->user, key->k0, key->k1);
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








