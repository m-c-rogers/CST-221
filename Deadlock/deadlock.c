//Created by Michael Rogers
//This program demonstrates deadlock avoidance by forcing a process to wait for a resource to become available if it is blocked on an attempt to use said resource. The sleep() method is used so that eventually the process will gain access to the resource during a period in which it is not being used.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int resource = 0;
FILE *output;
int x = 0;

//Checks if resource is not in use (set to an even number). If not in use, access is granted. If resource is in use (set to an odd number), process will wait and attempt to gain access again after a specified period of time.
void *useResource(void *arg) {
	output = fopen("output.txt", "w");
	while(x < 11) {
	if(resource % 2 == 0) {
		resource++;
		pthread_mutex_lock(&mutex);
		printf("%s tries to access resource.\n", arg);
		fprintf(output, "%s tries to access resource.\n", arg);
		printf("%s gained access.\n", arg);
		fprintf(output, "%s gained access.\n", arg);
		pthread_mutex_unlock(&mutex);
		sleep(3);
		x++;
	}
	else if(resource % 2 != 0) {
		resource++;
		printf("%s tries to access resource.\n", arg);
		fprintf(output, "%s tries to access resource.\n", arg);
		printf("Resource is not available.\n");
		fprintf(output, "Resource is not available.\n");
		printf("%s goes to sleep and will try again.\n", arg);
		fprintf(output, "%s goes to sleep and will try again.\n", arg);
		sleep(4);
		x++;
	};
	}
	fclose(output);
}


int main() {
	//Create two threads
	pthread_t threadOne;
	pthread_t threadTwo;

	char *threadOneMessage = "Thread One";
	char *threadTwoMessage = "Thread Two";

	pthread_create(&threadOne, NULL, *useResource, (void *) threadOneMessage);
	pthread_create(&threadTwo, NULL, *useResource, (void *) threadTwoMessage);

	pthread_join(threadOne, NULL);
	pthread_join(threadTwo, NULL);

	return 0;
}
