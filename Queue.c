/*
�ۼ���: �̵���
�ۼ���: 2014.05
����: queue API �� test �Լ� 
*/
#define	CHAR_STACK_TEMPLATE		(0)
#define	QUEUE_TEMPLATE			(0)
#include <stdlib.h>
int main

static int *queue;
static int capacity;
static int front; // ���� �� ó��/������ ����� ����� ���� ��ġ. ��, (front + 1) % capacity�� �ִ� item�� ����
static int rear; // ���� �� ����� ������ ��ġ�� ���� ��ġ. ��, (rear+1) % capacity �ڸ��� item�� �߰�

void printQueue();

static int createQueue(int initialCapacity)
{
	queue = (int*)malloc(sizeof(int)*initialCapacity);

	if (!queue)
		return -1;

	capacity = initialCapacity;
	front = 0;
	rear = 0;

	return 0;
}

/*
�Լ���: freeQueue
���: queue�� ���ǰ� �ִ� �޸𸮸� ����
�Ű�����: ����
return��: ����
*/

static void freeQueue()
{
	free(queue);
}

/*
�Լ���: isFull 
���: queue�� �� �� �������� ���� Ȯ��
�Ű�����: ����
return ��: �� �� ������(����� �ϳ� �������) 1, �ƴϸ� 0
*/

static int isFull()
{
	if ((rear + 1) % capacity == front)
		return 1;
	else
		return 0;
}

/*
�Լ���: isEmpty
���: queue�� ��� �ִ� �� Ȯ��
�Ű�����: ����
return��: empty�̸� 1 �ƴϸ� 0
*/

static int isEmpty()
{
	if (front == rear)
		return 1;
	else
		return 0;
}

/*
�Լ���: copyBlock
���: [strBegin, srcEnd)������ ���ҵ��� dst�� ����
�Ű�����:
    srcBegin: ���� �迭�� ���� ��ġ
	stcEnd: ������ �迭�� ������ ���� ��ġ + 1
	dst: ���Ӱ� ������ �迭
*/

void copyBlock(int *srcBegin, int *srcEnd, int *dst)
{
	while (srcBegin < srcEnd){
		*dst = *srcBegin;
		dst++;
		srcBegin++;
	}
}

/*
�Լ���: queueEntension
���: queue�� �뷮�� �ι�� �ø�
�Ű�����: ����
return ��: ����
*/

static void queueExtension()
{
	int *newQueue;
	int startPos;

	newQueue = (int*)malloc(sizeof(int)* 2 * capacity);

	if (!newQueue)
		return;

	startPos = (front + 1) % capacity;

	if (startPos < 2)
		copyBlock(queue+startPos,queue+startPos+capacity-1,newQueue);
	else{
		copyBlock(queue + startPos, queue + capacity, newQueue);
		copyBlock(queue, queue + rear + 1, newQueue + capacity - startPos);
	}

	front = 2 * capacity - 1;
	rear = capacity - 2;
	capacity *= 2;
	
	free(queue);
	queue = newQueue;
}

/*
�Լ���: enQueue 
���: �Ѱ� ���Ҹ� queue �� �ڿ� �߰��� 
�Ű�����: int type�� ��
return ��: ����
*/

static void enQueue(int item)
{
	if (isFull()){
		queueExtension();
		printf("after queueExtension()\n");
		printQueue();
	}

	rear = (rear + 1)&capacity;
	queue[rear] = item;
}

/*
�Լ���: deQueue
���: queue�� �� �տ��� ���� 1���� ������
�Ű�����: ����
return ��: ������ ����
*/

static int deQueue()
{
	if (isEmpty())
		exit(1);

	front = (front + 1) % capacity;
	return queue[front];
}

/* 
�Լ���: printQueue
���: queue�� �ִ� ���ҵ��� ���� front���� rear���� ��ġ�� �Բ� ���
�Ű�����: ����
return ��: ����
*/

void printQueue()
{
	int	pos;

	printf("front: %d, rear: %d\n", front, rear);
	if (isEmpty()) {
		printf("no element in queue!!!\n");
		return;
	}

	pos = (front + 1) % capacity;
	while (pos != rear) {
		printf("[%d, %d]\n", pos, queue[pos]);
		pos = (pos + 1) % capacity;
	}
	printf("[%d, %d]\n", pos, queue[pos]);


}

int main()
{
	int	i;

	createQueue(2); // 20�� ���� queueFull�� �߻����� �ʾƼ� queue Ȯ���� �̷������ ����. 
	// ������ ���������� �̷������ 2�� �ٲپ queueFull�� �����Ͽ� queueExtension()�� ����ǵ��� �Ͽ� �׽�Ʈ��.

	for (i = 0; i < 10; i++) {
		enQueue(i);
		printf("%3d enqueued\n", i);
		printf("---- ���� = %d -----\n", i);
		printQueue();
	}

	printf("----- dequeue ���� -----\n");
	while (!isEmpty()) {
		printf("%3d dequeued\n", deQueue());
		printf("---- ���� = %d -----\n", i);
		printQueue();
	}
	printf("\n");

	free(queue);
}

































