//Created by Michael Rogers
//This program demonstrates the ability of Semaphores to lock threads.
//Without the Semaphore, the program would not count to 10 and then back down.
//Instead, it would count up by 1, then down by 1 over and over.

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>

sem_t mutex;
int counterNum = 0;

//Count up to 10 then back down to 0.
//Semaphore locks thread so the countUp finishes before countDown begins.
void *count(void *arg) {
	int change = *(int *) arg;
	sem_wait(&mutex);
	//Critical section
	for(int i = 0; i < 10; i++) {
		counterNum += change;
		printf("Counting: %i\n", counterNum);
		sleep(1);
	}
	sem_post(&mutex);
}

int main () {
	int countUp = 1;
	int countDown = -1;
	pthread_t aCount;
	pthread_t bCount;
	
	//Create semaphore
	sem_init(&mutex, 0, 1);

	pthread_create(&aCount, NULL, *count, &countUp);
	pthread_create(&bCount, NULL, *count, &countDown);

	pthread_join(aCount, NULL);
	pthread_join(bCount, NULL);

	//Release semaphore
	sem_destroy(&mutex);
	return 0;
}
