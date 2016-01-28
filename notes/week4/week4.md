# Week 4 (Jan 25 - 29)

## Lecture 2 (Jan 27)

Livelock Example:
* Two people in elevator, both saying after you, then attempting to go

IPC - Interproccess Communication

If processes aren't allowed to communicate, there can never be race condition

Communication: Affecting an observable change
	* If i manipulate data you can read, we're communicating

Bakery: Take a turn but declare your intent to take a turn. Take a number

Implementation of Barriers with Semaphores:
	Barrier b; /* contains two semaphores */
	b.bsem.value = 0; /* for barrier */
	b.mutex.value = 1; /* for mutex */
	b.waiting = 0;
	b.maxproc = n; /* n processes needed at barrier */

	HitBarrier Barrier *b)
	{
		SemDown (&b->mutex); // Lock because we're changing stuff
		// if everyone is done
		if(++b->waiing >= b->maxproc) {
			// Let everyonoe be free!
			while(--b->waiting >0) {
				SemUp (&b->bsem);
			}
			SemUp (&b->mutex); // unlock
		}
		else
		{
			SemUp (&b->mutex);
			SemDown (&b->bse); // unlock
		}
	}

Classical Sync Problems

Bounded Buffers

Readers and Writers

Dining philosophers

Goal : Use semaphores

### Bounded Buffers

	// Shared
	const int n;
	// Num slots empty, num slots full, mutex
	Semaphore empty(n), full(0), mutex(1);
	Item buffer[n];

	// Producer
	int in = 0;
	Item pitem;
	while (1)
	{
		// produce an item into pitem
		empty.down();
		mutex.down();
		buffer[in] = pitem;
		in = (in+1) % n;
		mutex.up();
		full.up();
	}

	// Consumer
	int out = 0;
	Item citem;
	while (1)
	{
		full.down();
		mutex.down();
		citem = buffer[out];
		out = (out+1) % n;
		mutex.up();
		empty.up();
	}