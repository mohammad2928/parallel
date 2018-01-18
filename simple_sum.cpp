//import module
#include <iostream>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include "mpi.h"

using namespace std;
//main function
int main(int argc, char *argv[])
{//initialise mpi
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
			InputArr[i] = rand() % 1000;

		for (int i = 0; i<numprocs * 1000; i++)
			cout << InputArr[i] << "\t";
		cout << endl;
		//send data to anyprocess by process that id is 0
		for (int i = 1; i < numprocs; i++)
			MPI_Send(&InputArr[i * 1000], 1000, MPI_INT, i, 0, MPI_COMM_WORLD);//send data for any process 
	}
	else
	{

		InputArr = new int[1000];
		MPI_Recv(&InputArr[0], 1000, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);//recive that and put them on inputarr
	}
	
	//any process sum all of number that recieved
	for (int i = 0; i < 1000; i++)
		MySum += InputArr[i];

	cout << myid << "\t MySUM = " << MySum << endl;


	if (myid == 0)
	{
		for (int i = 1; i < numprocs; i++)
		{
			int HisSum;
			//process that id is 0 sum all mysum that recive from any process
			MPI_Recv(&HisSum, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
			MySum += HisSum;
		}
		cout << endl << "Sum = " << MySum << endl;
	}
	else
	{
		//other process without 0 send mysum to process  0
		MPI_Send(&MySum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}

//finalize program 
	MPI_Finalize();
}
