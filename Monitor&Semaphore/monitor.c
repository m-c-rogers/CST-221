//Created by Michael Rogers
//This program demonstrates the ability of Mutex to lock threads.
//Without the MUTEX lock, the program would not count to 10 and then back down.
//Instead, it would count up by 1, then down by 1 over and over.

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int counterNum = 0;

//Count up to 10 then back down to 0.
//Mutex locks thread so the countUp finishes before countDown begins.
void *count(void *arg) {
	int change = *(int *) arg;
	pthread_mutex_lock(&mutex);
	//Critical section
	for(int i = 0; i < 10; i++) {
		counterNum += change;
		printf("Counting: %i\n", counterNum);
		sleep(1);
	}
	pthread_mutex_unlock(&mutex);
}


int main () {
	int countUp = 1;
	int countDown = -1;
	pthread_t aCount;
	pthread_t bCount;

	pthread_create(&aCount, NULL, *count, &countUp);
	pthread_create(&bCount, NULL, *count, &countDown);

	pthread_join(aCount, NULL);
	pthread_join(bCount, NULL);
	return 0;
}
