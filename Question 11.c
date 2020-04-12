#include <stdio.h>  
#include <pthread.h>
#include<semaphore.h>
 
void * reader(void *) ;  
void *writer (void *) ;  

sem_t wsem,mutex ;  
int count=0 ;  
 
main()  
{
	int a=1;
	int b=1;    

	sem_init(&wsem,0,1) ;  
	sem_init(&mutex,0,1) ;  
  	
	pthread_t read;
	pthread_t write;
	pthread_t read1;
	pthread_t write1;  
  	
	pthread_create(&read, NULL, reader, (void *)a);  
    a++;  
  	
	pthread_create(&write1, NULL, writer, (void *)b);  
    b++;  
	
	pthread_create(&read1, NULL, reader, (void *)a);  
	pthread_create(&write, NULL, writer, (void *)b);  

	pthread_join(read, NULL);
	pthread_join(write1, NULL);
	pthread_join(read1, NULL);
	pthread_join(write, NULL) ;  
  
	printf("Main function terminated");
}
  
void * reader(void *arg)  
{  
	int a = (int)arg;
	
	printf("Reader %d is created \n",a);
	
	sleep(1);  
	sem_wait(&mutex);  
	
	count++;  
	if(count==1)
	{
		sem_wait(&wsem);
	}
	sem_post(&mutex) ;  

	// Critcal Section
	printf("Reader %d is reading \n\n",a);  
	sleep(1) ;  
	printf("Reader %d finished reading \n\n",a);  

	/* critical section completd */  
	sem_wait(&mutex);
	count--;
	if(count==0)  
	{
		sem_post(&wsem) ;
	}
	sem_post(&mutex) ;  
}
  
void * writer(void * arg)  
{  
	int a = (int)arg;  
	
	printf("Writer %d is created \n",a);
	
	sleep(1);  
	sem_wait(&wsem) ;  
	
	printf("Writer %d is writing \n\n",a) ;  
	sleep(1);  
	printf("Writer %d finished writing \n\n",a);  
	
	sem_post(&wsem) ;  
}
