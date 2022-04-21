/**
*
 *
 * Author: Faris Abufarha
 * SEC:3
 * ID: 1200546
 *
 *
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


#define null NULL
#define ll long long
#define MAX_STRING 4095
#define MAX_LINE MAX_STRING

typedef char *String;


typedef struct Passenger {
    int id;
    int date;
    char studentDepTime[5];
    char studentFromDestination[MAX_STRING];
    char studentToDestination[MAX_STRING];

    struct Passenger *passengerNextPassenger;


} Passenger;

typedef struct Bus {

    int busID;
    //could be either string or int
    int date;
    char depTime[5];
    char fromDestination[MAX_STRING];
    char toDestination[MAX_STRING];
    double price;
    int capacity;

    struct Passenger *busNextPassenger;


} Bus;

void memoryMsg();


int main() {
    printf("WELCOME\n");

    int selection;
    while (true) {


        printf("PLEASE SELECT AN OPTION:\n"
               "1. Load the bus information file\n"
               "2. Load the passenger information file\n"
               "3. Assign passengers and print assignment information of all\n"
               "busses\n"
               "4. Print a specific bus information along with its passengers\n"
               "information (names and IDs)\n"
               "5. Print unmatched passengers\n"
               "6. Add new passenger\n"
               "7. Delete passenger\n"
               "8. Delete bus number\n"
               "9. Exit"
               "\n");

        scanf("%d", &selection);

        switch (selection) {

            case 1:
                //load bus
                break;

            case 2:
                //load pass
                break;

            case 3:
                //assign
                break;

            case 4:
                //print some bus info
                break;

            case 5:
                //print unmatched
                break;

            case 6:
                //add pass

                break;
            case 7:
                //del pass
                break;
            case 8:
                //del bus
                break;
            case 9:
                printf("THANK YOU, COME AGAIN :)\n");
                return 1;
        }


    }
    FILE *pReadBus = null;
    pReadBus = fopen("busses.txt", "r");

    if (pReadBus == null) {
        printf("FILE NOT FOUND\n");
    }

    String buffer;

    int busCnt = 0;
    while (fgets(buffer, MAX_LINE, pReadBus) != null) {

        busCnt++;
    }
    fclose(pReadBus);


    return 0;
}


void memoryMsg() {

    printf("OUT OF MEMORY!\n");
}