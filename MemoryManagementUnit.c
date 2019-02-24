#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/mman.h> /*For mmap() function*/
#include <string.h> /*For memcpy function*/
#include <fcntl.h> /*For file descriptors*/


#define MEMSIZE 80
#define INT_SIZE 4

//Authors: Madeeha Khan and Biya Kazmi 

signed char *mmapfptr;
int requests[MEMSIZE];
int sortedrequests[MEMSIZE];

/* Function to sort an array using insertion sort*/
void insertionSort(int arr[], int n){
   int i = 1; 
   int key; 
   int j;
   for (i; i < n; i++){
       key = arr[i];
       j = i-1;
       /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
       while (j >= 0 && arr[j] > key){
           arr[j+1] = arr[j];
           j = j-1;
       }
       arr[j+1] = key;
   }
}


void FCFS(int start) {
	printf("FCFS DISK SCHEDULING ALGORITHM:\n\n");
	int hm = 0;
	int i = 0;
	int current = start;
	for (i; i < 20; i++) {
		hm += abs(requests[i] - current);
		current = requests[i];
		if (i < 19) printf("%d, ", requests[i]);
		else printf("%d\n", requests[i]);
	}
	printf("\nFCFS - Total head movements = %d\n\n", hm);

}

void SSTF (int start) {
	printf("SSTF DISK SCHEDULING ALGORITHM:\n\n");
	int hm = 0;	
	int current = start;
	int alreadyUsed[20] = {0};
	int i = 0;
	int closestIndex;
	int closestTo;
	//grab each member of requests
	for (i; i < 20; i++) {
		//look through requests for the closest thing that has NOT been used already
		int j = 0;
		int min = 301;
		for (j; j < 20; j++) {
			//find the closest thing to the current
			//check if the distance is smaller than the current smallest distance and if it has not been used already
			if ((abs(current - requests[j]) < min) && (alreadyUsed[j] == 0)) {
				//if this request is close to the 
				min = abs(current - requests[j]);
				closestTo = requests[j];
				closestIndex = j;
			}			
		}
		hm += abs(current - closestTo);
		current = closestTo;
		alreadyUsed[closestIndex] = 1;

		if (i < 19) printf("%d, ", requests[closestIndex]);
		else printf("%d\n", requests[closestIndex]);
	}
	printf("\nSSTF - Total head movements = %d\n\n", hm);	
}

void rightSCAN(int s){
	int hm = 0;
	int current = s;
	int closestIndex = findClosestIndexRight(sortedrequests, s, current);
	int i = closestIndex;

	//go from the closest index to the end
	for (i; i < 20; i++) {
		hm += abs(sortedrequests[i] - current);
		current = sortedrequests[i]; // new position
		printf("%d, ", current);

	}

	//now go all the way to the end 

	hm += abs(299 - current);
	current = 299;

	//go to closestIndex-1 and then switch direction to count down from there
	i = closestIndex-1;
	for(i; i > -1; i--) {
		hm += abs(sortedrequests[i] - current);
		current = sortedrequests[i];
		if (i > 0) printf("%d, ", current);
		else printf("%d\n", current);
	}
	printf("\nSCAN - Total head movements = %d\n\n", hm);
}
void leftSCAN(int s){
	int hm = 0;
	int current = s;
	int closestIndex = findClosestIndexLeft(sortedrequests, s, current);
	int i = closestIndex;

	//from closest index to the beginning
	for (i; i > -1; i--) {
		hm += abs(sortedrequests[i] - current);
		current = sortedrequests[i];
		printf("%d, ", current);
	}
	//Now go all the way to the end beause youre dumb and you dont know there is no need
	hm += abs(0 - current);
	current = 0;

	//go from closestIndex+1 to the end
	i = closestIndex + 1;
	for (i; i < 20; i++) {
		hm += abs(sortedrequests[i] - current);
		current = sortedrequests[i];
		if (i < 19) printf("%d, ", current);
		else printf("%d\n", current);
	}
	printf("\nSCAN - Total head movements = %d\n\n", hm);
}

void SCAN(int start, char* dir) {
	printf("SCAN DISK SCHEDULING ALGORITHM:\n\n");

	//if the head is moving right
	//want to do bigger numbers than where the head is
	//while sortedrequests[i] is less than sortedrequests[19]
	//go from the closest thing to the head until the end then start from sortedrequests[0] 
	if (strcmp("RIGHT", dir) == 0) {
		rightSCAN(start);
	}

	//if the head is moving left
	//want to do smaller numbers than where the head is
	//while sortedrequests[i] is greater than sortedrequests[0]
	if (strcmp("LEFT", dir) == 0) {
		leftSCAN(start);
	}
	//services on the way back

}

void rightCSCAN(int s){
	int hm = 0;
	int current = s;
	int closestIndex = findClosestIndexRight(sortedrequests, s, current);
	int i = closestIndex;

	//go from the closest index to the end
	for (i; i < 20; i++) {
		hm += abs(sortedrequests[i] - current);
		current = sortedrequests[i]; // new position
		printf("%d, ", current);

	}

	//now go all the way to the end 

	hm += abs(299 - current);

	hm += 299;
	current = 0;

	//go to closestIndex-1 and then switch direction to count down from there
	i = closestIndex;
	int j = 0;
	for(j; j < i; j++) {
		hm += abs(sortedrequests[j] - current);
		current = sortedrequests[j];
		if ((j+1) != i) printf("%d, ", current);
		else printf("%d\n", current);
	}
	printf("\nC-SCAN - Total head movements = %d\n\n", hm);
}
void leftCSCAN(int s){
	int hm = 0;
	int current = s;
	int closestIndex = findClosestIndexLeft(sortedrequests, s, current);
	int i = closestIndex;

	//from closest index to the beginning
	for (i; i > -1; i--) {
		hm += abs(sortedrequests[i] - current);
		current = sortedrequests[i];
		printf("%d, ", current);
	}
	//Now go all the way to the end beause youre dumb and you dont know there is no need
	hm += abs(0 - current);
	current = 299;
	hm += 299;

	//go from closestIndex+1 to the end
	int j = 19;
	i = closestIndex;
	for (j; j > i; j--) {
		hm += abs(sortedrequests[j] - current);
		current = sortedrequests[j];
		if ((j-1) != i) printf("%d, ", current);
		else printf("%d\n", current);
	}
	printf("\nC-SCAN - Total head movements = %d\n\n", hm);
}

void CSCAN(int start, char* dir) {
	printf("C-SCAN DISK SCHEDULING ALGORITHM:\n\n");

	//if the head is moving right
	//want to do bigger numbers than where the head is
	//while sortedrequests[i] is less than sortedrequests[19]
	//go from the closest thing to the head until the end then start from sortedrequests[0] 
	if (strcmp("RIGHT", dir) == 0) {
		rightCSCAN(start);
	}

	//if the head is moving left
	//want to do smaller numbers than where the head is
	//while sortedrequests[i] is greater than sortedrequests[0]
	if (strcmp("LEFT", dir) == 0) {
		leftCSCAN(start);
	}
	//services on the way back

}

int findClosestIndexLeft(int arr[], int s, int current) {
	int i = 0;
	int closestIndex;

	//want to find the number just smaller than start
	for (i; i < 20; i++) {
		if (arr[i] <= s) {
			current = arr[i];
			closestIndex = i;	
		}
	}
	return closestIndex;
}

int findClosestIndexRight(int arr[], int s, int current) {
	int i = 0;
	int closestIndex;
	
	//find number just bigger than start
	for (i; i < 20; i++) {
		if (arr[i] >= s) {
			current = arr[i];
			closestIndex = i;
			break;
		}
	}
	return closestIndex;
}

void rightLOOK(int s){
	int hm = 0;
	int current = s;
	int closestIndex = findClosestIndexRight(sortedrequests, s, current);
	int i = closestIndex;

	//go from the closest index to the end
	for (i; i < 20; i++) {
		hm += abs(sortedrequests[i] - current);
		current = sortedrequests[i];
		printf("%d, ", current);
	}

	//go to closestIndex-1 and then switch direction to count down from there
	i = closestIndex-1;
	for(i; i > -1; i--) {
		hm += abs(sortedrequests[i] - current);
		current = sortedrequests[i];
		if (i > 0) printf("%d, ", current);
		else printf("%d\n", current);
	}
	printf("\nLOOK - Total head movements = %d\n\n", hm);
}

void leftLOOK(int s){
	int hm = 0;
	int current = s;
	int closestIndex = findClosestIndexLeft(sortedrequests, s, current);
	int i = closestIndex;

	//from closest index to the beginning
	for (i; i > -1; i--) {
		hm += abs(sortedrequests[i] - current);
		current = sortedrequests[i];
		printf("%d, ", current);
	}

	//go from closestIndex+1 to the end
	i = closestIndex + 1;
	for (i; i < 20; i++) {
		hm += abs(sortedrequests[i] - current);
		current = sortedrequests[i];
		if (i < 19) printf("%d, ", current);
		else printf("%d\n", current);
	}
	printf("\nLOOK - Total head movements = %d\n\n", hm);
}

void LOOK(int start, char* dir) {
	printf("LOOK DISK SCHEDULING ALGORITHM:\n\n");

	//if the head is moving right
	//want to do bigger numbers than where the head is
	//while sortedrequests[i] is less than sortedrequests[19]
	//go from the closest thing to the head until the end then start from sortedrequests[0] 
	if (strcmp("RIGHT", dir) == 0) {
		rightLOOK(start);
	}

	//if the head is moving left
	//want to do smaller numbers than where the head is
	//while sortedrequests[i] is greater than sortedrequests[0]
	if (strcmp("LEFT", dir) == 0) {
		leftLOOK(start);
	}
	//services on the way back
}

void rightCLOOK(int s) {
	int hm = 0;
	int current = s;
	int closestIndex = findClosestIndexRight(sortedrequests, s, current);
	int i = closestIndex;

	//want to increment from here until sortedrequests[19]
	for (i; i < 20; i++) {
		hm += abs(current - sortedrequests[i]);
		current = sortedrequests[i];
		printf("%d, ", current);
	}

	//go from current to sorted[0]
	i = 0;

	//go from sorted[0] to right sorted[closestIndex-1]
	for (i; i < closestIndex; i++) {
		hm += abs(current - sortedrequests[i]);
		current = sortedrequests[i];
		if (i < closestIndex-1) printf("%d, ", current);
		else printf("%d\n", current);
	}
	printf("\nC-LOOK - Total head movements = %d\n", hm);
}

void leftCLOOK(int s) {
	int hm = 0;
	int current = s;
	int closestIndex = findClosestIndexLeft(sortedrequests, s, current);
	int i = closestIndex;

	//want to decrement from here until sortedrequests[0]
	for (i; i > -1; i--) {
		hm += abs(current - sortedrequests[i]);
		current = sortedrequests[i];
		printf("%d, ", current);
	}

	//go from current to sorted[19]
	i = 19;

	//go backwards from sorted[19] to right sorted[closestIndex+1]
	for (i; i > closestIndex; i--) {
		hm += abs(current - sortedrequests[i]);
		current = sortedrequests[i];
		if (i > closestIndex+1) printf("%d, ", current);
		else printf("%d\n", current);
	}
	printf("\nC-LOOK - Total head movements = %d\n", hm);
}

void CLOOK(int start, char* dir) {
	printf("C-LOOK DISK SCHEDULING ALGORITHM:\n\n");

	//if the head is moving right
	//want to do bigger numbers than where the head is
	//while sortedrequests[i] is less than sortedrequests[19]
	//go from the closest thing to the head until the end then start from sortedrequests[0] 
	if (strcmp("RIGHT", dir) == 0) rightCLOOK(start);

	//if the head is moving left
	//want to do smaller numbers than where the head is
	//while sortedrequests[i] is greater than sortedrequests[0]
	if (strcmp("LEFT", dir) == 0) leftCLOOK(start);
}


int main(int argc, char *argv[])
{

	int i = 0;
	int mmapfile_fd = open("request.bin", O_RDONLY);
	mmapfptr= mmap(0, MEMSIZE, PROT_READ, MAP_PRIVATE, mmapfile_fd, 0); 
	for(i; i < 20; i++){
		//create the requests array
		memcpy(requests+ i, mmapfptr + 4*i, INT_SIZE);
		//copy requests into another array to be sorted later
		memcpy(sortedrequests+ i, mmapfptr + 4*i, INT_SIZE);
	}

	//sort the requests in sortedarray once
	insertionSort(sortedrequests, 20);

	int start = atoi(argv[1]);

	printf("Total requests = 20\nInitial Head Position: %d\nDirection of Head: %s\n\n", start, argv[2]);
	//first two don't need the direction
	FCFS(start);
	SSTF(start);
	//rest of the algorithms need to know what direction to go in
	SCAN(start, argv[2]);
	CSCAN(start, argv[2]);
	LOOK(start, argv[2]);
	CLOOK(start, argv[2]);

	if (argc !=3) {
		printf("need to provide starting position and direction");
		return -1;
	}

	return 0;
}
