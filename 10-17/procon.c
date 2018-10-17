/*************************************************************************
    > File Name: procon.c
    > Author: ma6174
    > Mail: ma6174@163.com 
    > Created Time: Wed 17 Oct 2018 04:43:20 PM CST
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<error.h>

#define PRO_CNT 1//生产者个数
#define CON_CNT 2//消费者个数
pthread_cond_t cond;//条件变量
pthread_mutex_t mutex;//互斥量
int num=0;
void *pro(void *arg)
{
	int id=*(int *)arg;
	free(arg);
	while(1)
	{
		pthread_mutex_lock(&mutex);
		printf("%d号生产线程开始生产第%d个产品\n",id,num+1);
		num++;
		sleep(rand()%3);
		printf("%d号生产线程生产第%d个产品结束\n",id,num);
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mutex);
        sleep(rand()%3);
	}
}

void *con(void *arg)
{
	int id=*(int *)arg;
	free(arg);
	while(1)
	{
		pthread_mutex_lock(&mutex);
		while(num<=0)
		{
			printf("%d号消费线程开始等待消费产品\n",id);
			pthread_cond_wait(&cond,&mutex);
			printf("%d消费线程等待结束\n",id);
		}
		printf("%d消费线程开始消费%d消费产品\n",id,num);
		num--;
		sleep(rand()%3);
		printf("%d消费线程消费%d产品结束\n",id,num+1);
		pthread_mutex_unlock(&mutex);
		sleep(rand()%3);
	}
}
int main()
{
	pthread_t tids[PRO_CNT+CON_CNT];
	srand(getpid());
	pthread_cond_init(&cond,NULL);
	pthread_mutex_init(&mutex,NULL);

	for(int i=0;i<PRO_CNT;i++)
	{
		int *p=(int *)malloc(sizeof(int));
		*p=i;
		pthread_create(&tids[i],NULL,pro,p);
	}

	for(int i=0;i<CON_CNT;i++)
	{
		int *p=(int *)malloc(sizeof(int));
		*p=i;
		pthread_create(&tids[i+PRO_CNT],NULL,con,p);
	}
	
	for(int i=0;i<PRO_CNT+CON_CNT;i++)
	{
		pthread_join(tids[i],NULL);
	}
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
	return 0;
}
