#include <sys/queue.h>
#include <sys/proc.h>
#include <sys/lottoq.h>

void lottoq_init(struct lottoq *q)
{
	q->T = 0;
	TAILQ_INIT(&(q->head));
}

void lottoq_add(struct lottoq *q, thread *td)
{
	TAILQ_INSERT_TAIL(&(q->head), td, td_lottoq);
}

void lottoq_remove (struct lottoq *q, thread *td)
{
	TAILQ_REMOVE(&(q->head), td, td_lottoq);
}

struct thread *lottoq_choose(struct lottoq *q)
{
	int num = random() % q->T;
	int ticket_tally;
	
	TAILQ_FOREACH(current, &(q->head), td_lottoq){
		ticket_tally += current->td_tickets;
		if(ticket_tally >= num){
			return current;
		}
	}
}
