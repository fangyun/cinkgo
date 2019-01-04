#ifndef FIFO_H_
#define FIFO_H_

#ifdef CINKGO_FIFO

void fifo_init(void);
int  fifo_task_queue(void);
void fifo_task_done(int ticket);

#else
#define fifo_init() ((void)0)
#endif /* FIFO */

#endif /* FIFO_H_ */
