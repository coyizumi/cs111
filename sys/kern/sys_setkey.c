#include <sys/sysproto.h>
#include <sys/proc.h>

#include <sys/types.h>
#include <sys/systm.h>

#ifndef _SYS_SYSPROTO_H_

struct setkey_args {
   unsigned int k0;
   unsigned int k1;
}

#endif

int sys_setkey(struct thread *td, struct setkey_args *args) {
   printf("Hello World\n");
   return 0;
}
