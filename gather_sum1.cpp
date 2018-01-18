//import module
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"

using namespace std;
//main function
int main(int argc, char *argv[])
{	//initialise mpi 
	int *InputArr = NULL;
	int myid, numprocs;
	MPI_Status status;
	int MySum = 0;


	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	// Generate data and Print it too see (unsorted)
	if (myid == 0)
	{
		InputArr = new int[numprocs * 1000];

		srand(time(NULL));
		for (int i = 0; i<numprocs * 1000; i++)
			InputArr[i] = rand()%1000;

		for (int i = 0; i<numprocs * 1000; i++)
			cout << InputArr[i] << "\t";
		cout << endl;

	}

//array to save data that recive from scatter 
int* receve_data=new int[1000];

//send data for any process with scatter c
MPI_Scatter(InputArr,1000, MPI_INT,receve_data,1000,MPI_INT, 0,  MPI_COMM_WORLD);//1000=count of data that send and 0 is the admin id 


//sum all number that recive by any process 
	for (int i = 0; i < 1000; i++)
		MySum += receve_data[i];

	cout << myid << "\t MySUM = " << MySum << endl;

//array that to save any MYsum that recive from 
int AllSum[numprocs];

//gather all mysum taht make by any process and save on Allsum arry 
MPI_Gather(&MySum,1,MPI_INT,AllSum,1,MPI_INT,0,MPI_COMM_WORLD);// 1=count of data that want to save

//process that id is 0 sum all number on Allsum 
	if (myid == 0)
	{
		int HisSum=0;
		for (int i = 0; i < numprocs; i++)
		{


			HisSum+=AllSum[i];
		}
		cout << endl << "Sum = " << HisSum << endl;
	}

//finalize program
	MPI_Finalize();
}
