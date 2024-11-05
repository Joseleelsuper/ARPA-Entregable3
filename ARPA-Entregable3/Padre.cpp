#include <mpi.h>  
#include <iostream>  
 
constexpr int NUM_HIJOS = 4;  
constexpr int TAG = 0;  
constexpr int RANK_MASTER = 0;  
constexpr char NOMBRE_HIJOS[] = "ARPA-Entregable3-Hijos.exe";  
 
using namespace std;  
 
int main(int argc, char* argv[]) {  
   int rank, size;  
   MPI_Init(&argc, &argv);  
   MPI_Comm_rank(MPI_COMM_WORLD, &rank);  
   MPI_Comm_size(MPI_COMM_WORLD, &size);  

   double start_time = MPI_Wtime();

   if (rank == RANK_MASTER) { 
       printf("\n<<PADRE>> Soy el padre y crearé hijos.\n");

       MPI_Comm intercom;  
       MPI_Comm_spawn(
           const_cast<char*>(NOMBRE_HIJOS), 
           MPI_ARGV_NULL, 
           NUM_HIJOS, 
           MPI_INFO_NULL, 
           TAG, 
           MPI_COMM_WORLD, 
           &intercom, 
           MPI_ERRCODES_IGNORE);  

       // Enviar mensaje de saludo a los hijos  
       char mensaje[] = "<<PADRE>> Hola desde el padre";  
       for (int i = 0; i < NUM_HIJOS; i++) {  
           MPI_Send(mensaje, sizeof(mensaje), MPI_CHAR, i, TAG, intercom);
       }
	   MPI_Send(&start_time, 1, MPI_DOUBLE, 0, TAG+1, intercom);
   }
 
   MPI_Finalize();  
   return 0;  
}