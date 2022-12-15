#include<stdio.h>
#include<mpi.h>

 // Function to be integrated over
double f(double x)
{
     return (1 / (1 + (x * x)));
}

double trapezoidal(double a_p, double b_p, double h)
{
   // For each interval, i is the lower, and j is the upper bound
   double i, j;
   double y_i, y_j, area, sum_p = 0.0;

   for(i = a_p; i < b_p; i += h)
   {
       j = i + h;

       y_i = f(i);
       y_j = f(j);

       // Area of trapezium defined by this interval
       area = 0.5 * h * (y_i + y_j);

       // Calculate partial sum (sub-integral)
       sum_p += area;
   }

   return sum_p;
}

int main(int argc, char **argv)
{
   double a, b, n, a_p, b_p, n_p, sum, sum_p, h;

   int process_rank, num_processes;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

   // Only master process receives input from user
   if(process_rank == 0)
   {
       printf("Enter a, b and n\n");
       scanf("%lf", &a);
       scanf("%lf", &b);
       scanf("%lf", &n);

       // Number of intervals assigned to each process
       n_p = n / num_processes;

       // Length of each interval
       h = (b - a) / n;
   }

   // Master process broadcasts user input to slave processes
   MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   MPI_Bcast(&n_p, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   MPI_Bcast(&h, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

   // a = 0, b = 20, n = 10, h = 2, num_processes = 2, n_p = 5

   a_p = a + process_rank * h * n_p;
   b_p = a_p + h * n_p;

   sum_p = trapezoidal(a_p, b_p, h);

   // Combine partial sums
   MPI_Reduce(&sum_p, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
   MPI_Allreduce(&sum_p, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

   printf("The area under the curve is %lf (Process %d)\n", sum, process_rank);

   MPI_Finalize();
}
#include<stdio.h>
#include<mpi.h>

 // Function to be integrated over
double f(double x)
{
     return (1 / (1 + (x * x)));
}

double trapezoidal(double a_p, double b_p, double h)
{
   // For each interval, i is the lower, and j is the upper bound
   double i, j;
   double y_i, y_j, area, sum_p = 0.0;

   for(i = a_p; i < b_p; i += h)
   {
       j = i + h;

       y_i = f(i);
       y_j = f(j);

       // Area of trapezium defined by this interval
       area = 0.5 * h * (y_i + y_j);

       // Calculate partial sum (sub-integral)
       sum_p += area;
   }

   return sum_p;
}

int main(int argc, char **argv)
{
   double a, b, n, a_p, b_p, n_p, sum, sum_p, h;

   int process_rank, num_processes;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

   // Only master process receives input from user
   if(process_rank == 0)
   {
       printf("Enter a, b and n\n");
       scanf("%lf", &a);
       scanf("%lf", &b);
       scanf("%lf", &n);

       // Number of intervals assigned to each process
       n_p = n / num_processes;

       // Length of each interval
       h = (b - a) / n;
   }

   // Master process broadcasts user input to slave processes
   MPI_Bcast(&a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   MPI_Bcast(&b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   MPI_Bcast(&n_p, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
   MPI_Bcast(&h, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

   // a = 0, b = 20, n = 10, h = 2, num_processes = 2, n_p = 5

   a_p = a + process_rank * h * n_p;
   b_p = a_p + h * n_p;

   sum_p = trapezoidal(a_p, b_p, h);

   // Combine partial sums
   MPI_Reduce(&sum_p, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
   MPI_Allreduce(&sum_p, &sum, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

   printf("The area under the curve is %lf (Process %d)\n", sum, process_rank);

   MPI_Finalize();
}

#include<stdio.h>
#include<mpi.h>

int main(int argc, char **argv)
{
   int process_rank, num_processes;
   int i, n, n_p;
   int a[100], b[100], sum[100], a_p[100], b_p[100], sum_p[100];

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

   if(process_rank == 0)
   {
       printf("Enter the length of the vectors\n");
       scanf("%d", &n);

       printf("Enter the elements of vector 1\n");
       for(i = 0; i < n; i++)
       {
           scanf("%d", &a[i]);
       }

       printf("Enter the elements of vector 2\n");
       for(i = 0; i < n; i++)
       {
           scanf("%d", &b[i]);
       }

       n_p = n / num_processes;
   }

   MPI_Bcast(&n_p, 1, MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);

   MPI_Scatter(a, n_p, MPI_INT, a_p, n_p, MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Scatter(b, n_p, MPI_INT, b_p, n_p, MPI_INT, 0, MPI_COMM_WORLD);

   for(i = 0; i < n_p; i++)
   {
       sum_p[i] = a_p[i] + b_p[i];
   }

   MPI_Gather(sum_p, n_p, MPI_INT, sum, n_p, MPI_INT, 0, MPI_COMM_WORLD);

   if(process_rank == 0)
   {
       printf("Resultant vector :-\n");

       for(i = 0; i < n; i++)
       {
           printf("%d ", sum[i]);
       }

       printf("\n");
   }

   MPI_Finalize();
   return 0;
}

#include<stdio.h>
#include<mpi.h>

void get_input(double *a, double *b, int *n, int process_rank, int num_processes, int b_flag)
{
   MPI_Status status;
   double a_val = 0.0, b_val = 0.0;
   int n_val = 0;

   if(process_rank == 0)
   {
       printf("Enter a, b and n\n");
       scanf("%lf", &a_val);
       scanf("%lf", &b_val);
       scanf("%d", &n_val);

       a = &a_val;
       b = &b_val;
       n = &n_val;
   }

   if(b_flag == 0)
   {
       if(process_rank == 0)
       {
           for(int i = 1; i < num_processes; i++)
           {
               MPI_Send(a, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
               MPI_Send(b, 1, MPI_DOUBLE, i, 1, MPI_COMM_WORLD);
               MPI_Send(n, 1, MPI_INT, i, 2, MPI_COMM_WORLD);
           }
       }
       else
       {
           MPI_Recv(a, 1, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
           MPI_Recv(b, 1, MPI_DOUBLE, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
           MPI_Recv(n, 1, MPI_INT, 0, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

           printf("a = %lf (Process - %d)\n", *a, process_rank);
           printf("b = %lf (Process - %d)\n", *b, process_rank);
           printf("n = %d (Process - %d)\n", *n, process_rank);
       }
      
   }

   else
   {
       MPI_Bcast(a, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
       MPI_Bcast(b, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);
       MPI_Bcast(n, 1, MPI_INT, 0, MPI_COMM_WORLD);

       if(process_rank != 0)
       {
           printf("a = %lf (Process - %d)\n", *a, process_rank);
           printf("b = %lf (Process - %d)\n", *b, process_rank);
           printf("n = %d (Process - %d)\n", *n, process_rank);
       }
   }
  
}

int main(int argc, char **argv)
{
   double a, b;
   int n, b_flag;

   int process_rank, num_processes;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

   if(process_rank == 0)
   {
       printf("Enter 1 to broadcast the values, 0 to not\n");
       scanf("%d", &b_flag);
   }

   // Broadcasting b_flag alone
   MPI_Bcast(&b_flag, 1, MPI_INT, 0, MPI_COMM_WORLD);

   get_input(&a, &b, &n, process_rank, num_processes, b_flag);

   MPI_Finalize();
}

#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>
#include<string.h>

int main(int argc, char **argv)
{
   char send_greeting[50], recv_greeting[50];
   int process_rank, num_processes, method;

   MPI_Init(&argc, &argv);
   MPI_Comm_rank(MPI_COMM_WORLD, &process_rank);
   MPI_Comm_size(MPI_COMM_WORLD, &num_processes);

   sprintf(send_greeting, "Greetings from process %d", process_rank);

   if(process_rank == 0)
   {
       printf("Select method 1 (all receive) or 2 (only root receives)\n");
       scanf("%d", &method);
   }

   MPI_Bcast(&method, 1, MPI_INT, 0, MPI_COMM_WORLD);

   if(method == 1)
   {
       for(int i = 0; i < num_processes; i++)
       {
           if(i != process_rank)
           {
               MPI_Bsend(send_greeting, strlen(send_greeting), MPI_CHAR, i, 0, MPI_COMM_WORLD);
           }
       }

       for(int i = 0; i < num_processes - 1; i++)
       {
           MPI_Recv(recv_greeting, 50, MPI_CHAR, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

           printf("%s, process %d!\n", recv_greeting, process_rank);
       }
   }
   else
   {
       if(process_rank != 0)
       {
           MPI_Send(send_greeting, strlen(send_greeting), MPI_CHAR, 0, 0, MPI_COMM_WORLD);
       }
       else
       {
           for(int i = 1; i < num_processes; i++)
           {
               MPI_Recv(recv_greeting, 50, MPI_CHAR, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

               printf("%s, root!\n", recv_greeting);
           }
       }
   }
  
   MPI_Finalize();
}
