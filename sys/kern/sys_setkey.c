#include <sys/sysproto.h>
#include <sys/proc.h>

#include <sys/types.h>
#include <sys/systm.h>

#include <sys/proc.h>
#include <sys/ucred.h>
#include "keys.h"

//struct declarations
#ifndef _SYS_SYSPROTO_H_
struct setkey_args {
   unsigned int k0;
   unsigned int k1;
}
#endif

//Already declared in the header file, so not needed??
/*struct user_keys {
	uid_t user;
	unsigned int k0;
	unsigned int k1;
}*/



int sys_setkey(struct thread *td, struct setkey_args *args) {
   
	//check uid via ucred
	uid_t userID;
	userID = (td->td_ucred->cr_uid);
   
	//malloc space for 20 users (need minimum of 16)
	struct user_keys key_table[20];
	
	//fill out user_keys with relevant data
	key_table->user = userID;
	key_table->k0 = args->k0;
	key_table->k1 = args->k1;
   
	printf("Hello World\n");
	return 0;
}








