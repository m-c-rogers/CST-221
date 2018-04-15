//Created by Michael Rogers
/*My solution uses pthread_mutex to lock the consumer
and producer threads so they do not run concurrently.
theBuffer variable is used to determine whether Producer
or Consumer should execute their logic.
*/

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

int theProduct;
char theBuffer = 'E';
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *Producer() {
	int i;
	while(1) {
		pthread_mutex_lock(&mutex);
		//If buffer is Empty, get new theProduct and print current 				value.
		if(theBuffer == 'E') {
			i = produce();
			put(i);
			printf("Producing: %i\n", i);
		}
		pthread_mutex_unlock(&mutex);
	}
}

void *Consumer() {
	int i;
	while(1) {
		pthread_mutex_lock(&mutex);
		//If buffer is Full, get current value of theProduct and 				print
		if(theBuffer == 'F') {
			i = get();
			consume(i);
		}
		pthread_mutex_unlock(&mutex);
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
	sleep(2);
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

