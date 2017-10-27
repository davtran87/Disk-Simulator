
/*
 * File: diskSimulator.cpp
 * Author: David Tran
 * Purpose: The purpose of this program is to simulate a disk using the
 * SSTF (Shortest Seek Time First) disk scheduling algorithm. The program
 * is to simulate a disk with 200 cylinders given a queue that is generated
 * with uniformly distributed randomly generated cylinder numbers, also calculating
 * the average seek time and average seek distance for 10000 disk accesses, While
 * increasing the size of the queue per 10000 accesses.
 * Created on March 4, 2017, 8:09 PM
 */

#include <cstdlib>
#include <stdlib.h>
#include <iostream>
#include <math.h>
#include <iomanip>
int const QUEUE_SIZE = 8;
int const NUM_CYLINDERS = 200;
int const NUM_ACCESS = 10000;
using namespace std;

/* Function Declaration */
int SSTF(int dQ[], int head);
double seekTime(int x);
double urn();


int index = 0; // global variable to track position in queue

int main(int argc, char** argv)
{
    int diskQueue[QUEUE_SIZE], shortestDistance, nRev = 7200;
    int currentHead = 13; // current head.
    double totalSeek = 0, totalDistance = 0, avgSeek, avgRD, avgDistance;

      /* Populate queue with first set of random numbers */
    for(int i=0; i<QUEUE_SIZE; i++)
        diskQueue[i] = urn();

    /* Loop to control number of accesses to disk*/
    for (int i=0; i<NUM_ACCESS; i++)
    {
        shortestDistance = SSTF(diskQueue, currentHead); // call to SSTF function
        currentHead = diskQueue[index]; // new head after SSTF.
        diskQueue[index] = urn(); // Replace the current head in queue with new random #
        totalSeek += seekTime(shortestDistance); // call to seekTime() and calculate totalSeek
        totalDistance += shortestDistance; // calculates total distance
    }
    avgDistance = totalDistance/NUM_ACCESS;
    avgSeek = totalSeek/NUM_ACCESS; // calculate avgSeek time.
    avgRD = 30000./nRev; // calculate avg rotational delay.

    /* Prints average seek time, rotational delay time, average access time and
    average seek distance.*/
    cout << "\nMean seek time = " << avgSeek
         << " ms" << endl << "Rotational delay time = " << avgRD
         << " ms\nMean access time = " << avgSeek+avgRD << " ms\n";
    cout << "Mean seek distance = " << avgDistance << " cylinders" << endl;
    return 0;
}

/*
 * This function calculates the shortest seek time first (SSTF) disk scheduling
 * algorithm. It takes an array, and the current position of the head.
 * It then calculates the shortest seek time by subtracting the distance between
 * cylinders in the queue. and returns the shortest distance.
 * @Param: int dQ[] is the queue that holds the list of cylinders.
 *         int head is the position of the current head.
 * @Return: the shortest distance between the head and the cylinders in teh queue.
 */
int SSTF(int dQ[], int head)
{
    int distance, smallest, newHead;
    smallest = -1; // need smallest to start at -1 on first iteration to enter if.
    for(int i=0; i<QUEUE_SIZE; i++) //loop subtracting head and elements in dQ[].
    {
        distance = abs(head - dQ[i]);

        if(distance < smallest || smallest == -1) //finds the shortest distance.
        {
            smallest = distance;
            newHead = dQ[i];
            index = i;
        }
    }
    return smallest;

}

/*
 * This function calculates the seek time given a distance between two cylinders.
 * @Param: int x is the distance between 2 cylinders.
 * @Return: returns the seek time per disk access.
 * @Reference: Dr. Jozo Disk simulator Handout.
 */
double seekTime(int x)
{
    if(x==0) return 0;
    return 1.6+0.39*pow(x-1.0,0.4);
}

/*
 * This function generates Uniformly Distributed Random Numbers from 0 - 199.
 * @return: a number generated between 0-199.
 * @reference:Random Number Generator Slides pg 39
 */
double urn()
{
    return double(rand())/double(RAND_MAX)*(199-0+1)+ 0;
}
