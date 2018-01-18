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
			InputArr[i] = rand()%1000;

		for (int i = 0; i<numprocs * 1000; i++)
			cout << InputArr[i] << "\t";
		cout << endl;

	}

//array to save data that recive from scatter 
int* receve_data=new int[1000];

//send data for any process with scatter 
MPI_Scatter(InputArr,1000, MPI_INT,receve_data,1000,MPI_INT, 0,  MPI_COMM_WORLD);//1000=count of data that send and 0 is the admin id


//sum all number that recive by any process 
	for (int i = 0; i < 1000; i++)
		MySum += receve_data[i];

	cout << myid << "\t MySUM = " << MySum << endl;

//varible that save sum all number
int AllSum;

//gather all musum that send via process and sum all of them 
MPI_Reduce(&MySum,&AllSum,1,MPI_INT,MPI_SUM,0,MPI_COMM_WORLD);//1=count of data that recive from any process , mpi_sum=operatore to sum all numer that recive and
								//save all of them on Allsum varible 
//process that id is 0 print allsum
if (myid==0){
	cout<<"sum=      "<<AllSum<<"   and id = "<<myid<<endl;
}

//finalize process 
	MPI_Finalize();
}
