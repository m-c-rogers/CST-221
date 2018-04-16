//Created by Michael Rogers
/*My solution uses pthreads to signal between the Consumer and Producer informing each thread when to run.
theBuffer variable is used to determine whether Producer
or Consumer should execute their logic.
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int theProduct;
char theBuffer = 'E';
pthread_mutex_t mutex;
pthread_cond_t consumerT;
pthread_cond_t producerT;

void *Producer() {
	int i;
	while(1) {
		//If buffer is full, signal that thread is waiting on a new condition before moving on.
		if(theBuffer == 'F') {
			pthread_cond_wait(&consumerT, &mutex);
		}
		//If buffer is Empty, get new theProduct and print current 				value.
		else if(theBuffer == 'E') {
			i = produce();
			printf("Producing: %i\n", i);
			put(i);
			pthread_cond_signal(&producerT);
		};
	}
}

void *Consumer() {
	int i;
	while(1) {
		//If buffer is empty, signal that thread is waiting on a new condition before moving on.
		if(theBuffer == 'E') {
			pthread_cond_wait(&producerT, &mutex);
		}
		//If buffer is Full, get current value of theProduct and 				print.
		else if(theBuffer == 'F') {
			i = get();
			consume(i);
			pthread_cond_signal(&consumerT);
		}
	}
}

//Get random integer
int produce() {
	theProduct = rand();
	return theProduct;
}

void consume(int i) {
	printf("Consuming: %i\n", i);
}

//Replace theProduct with new value and set buffer to Full (F)
void put(int i) {
	theProduct = i;
	theBuffer = 'F';
	sleep(2);
}

//Set buffer to Empty (E) and return current value of theProduct
int get() {
	theBuffer = 'E';
	return theProduct;
}

int main() {
	//Create threads for producer and consumer
	pthread_t produceThread;
	pthread_t consumeThread;

	//Initalize procuder and consumer threads with Producer and 		Consumer functions
	pthread_create(&produceThread, NULL, *Producer, NULL);
	pthread_create(&consumeThread, NULL, *Consumer, NULL);

	//Join threads so they wait for other to finish
	pthread_join(produceThread, NULL);
	pthread_join(consumeThread, NULL);

	return 0;
}

