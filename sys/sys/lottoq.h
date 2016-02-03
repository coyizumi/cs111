#include <sys/queue.h>
#include <sys/proc.h>

TAILQ_HEAD (lotto, thread);

struct lottoq {
	struct lotto head;
	int T;
	// Rand Numbers here maybe
};

void lottoq_init(struct lottoq *q);
void lottoq_add(struct lottoq *q, thread *td);
void lottoq_remove(struct lottoq *q, thread *td);
struct thread *lottoq_choose(struct lottoq *q);