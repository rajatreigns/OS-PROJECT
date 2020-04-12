#include <stdio.h>
#define Queue_Size 50
typedef struct Pro {
	int pro_no;
	int AT;
	int BT;
} process;
process * QUEUE[Queue_Size];
int f = 0; 
r = -1;
 exe = 0;
  CT = 0;
  tq = 6;
int last_f = 0, last_r = -1;
void swaping(process * a, process * b) {
	process temp = * a;
	* a = * b;
	* b = temp;
}
void sort(process p[], int n) {
	int i, j;
	short swap;	
	for (i = 0; i < n; ++i) {
		swap = 0;
		for (j = 0; j < n-i-1; ++j)
		{
			if (p[j].AT > p[j+1].AT)
			{
				swaping(&p[j], &p[j+1]);
				swap = 1;
			}
		}
		if (swap == 0)
			break;
	}
}
void enqueue(process p[], int n) {
	int i, j, can_insert;
	for (i = 0; i < n; ++i)
	{
		can_insert = 1;
		
		if (p[i].AT <= CT && p[i].BT > 0)
		{
			if (f == 0) {
				QUEUE[++r] = &p[i];
			}
			else
			{
				for (j = last_f; j <= last_r; ++j) {
					if (QUEUE[j]->pro_no == p[i].pro_no)
						can_insert = 0;
				}
				if (can_insert == 1)
					QUEUE[++r] = &p[i];
			}
		}
	}
	for (i = last_f; i <= last_r; ++i)
	{
		if (QUEUE[i]->BT > 0)
			QUEUE[++r] = QUEUE[i];
	}
}
void execute() {
	int i;
	
	if (f-1 == r) {
		printf("CPU is going to be idle for 1 sec\n");
		CT += 1;
	}
	else {
		last_f = f;
		last_r = r;		
		for (i = f; i <= r; ++i, ++f)
		{
			if (QUEUE[i]->BT > tq)
			{
				QUEUE[i]->BT -= tq;
				CT += tq;
				printf("process %d is running till %d seconds.\n", QUEUE[i]->pro_no, CT);
			}
			else if (QUEUE[i]->BT > 0)
			{
				CT += QUEUE[i]->BT;
				QUEUE[i]->BT = 0;
				printf("process %d is running till %d seconds.\n", QUEUE[i]->pro_no, CT);
				++exe;
			}
		}
	}
}
int main() {
	int n, i;
	short x = 0;	
	do {
		if (x == 1)
			fprintf(stderr, "\nNumber of processes should be greater than 1.\n");
		printf("Enter the number of processes: ");
		scanf("%d", &n);
		x = 1;
	} while (n < 1);
	x = 0;
	process p[n];
	for (i = 0; i < n; ++i) {
		printf("\n");
		printf("enter arrival time %d: ", i+1);
		scanf("%d", &p[i].AT);
		printf("enter burst time %d: ", i+1);
		scanf("%d", &p[i].BT);
		p[i].pro_no = i+1;
	}
	sort(&p[0], n); // Sort the processes according to the arrival time of each process.	
	while (1) {
		enqueue(p, n);
		printf("\nIn queue: ");
		for (i = 0; i <= r; ++i) {
			printf("%d ", QUEUE[i]->pro_no);
		}
		printf("\nF : %d, R : %d.\n\n", f, r);
		execute();
		// If all the processes have been processed, break from the loop.
		if (exe == n)
			break;
	}
	return 0;
}

