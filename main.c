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
#include <string.h>


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
    String depTime;
    String fromDestination;
    String toDestination;
    double price;
    int capacity;

    struct Passenger *busNextPassenger;


} Bus;

//node *makeEmpty(node *head);
//
//bool isEmpty(node *l);
//
//bool isLast(node *n, node *head);
//
//node *find(int x, node *head);
//
//node *findPrev(int x, node *l);
//
//void deleteNode(int x, node *head);
//
//void insertAtBeginning(int x, node *head);
//
//void insertAtNode(int x, node *head, node *p);
//
//void printList(node *head);
//
//void deleteList(node *head);
//
//int sizeOfList(node *head);




int countLines(char *filename);

void memoryMsg();

Bus *loadBusInfo();

Passenger *loadPassInfo();


int main() {

    Bus *busArray = null;


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
                busArray = loadBusInfo();
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


    return 0;
}


void memoryMsg() {

    printf("OUT OF MEMORY!\n");
}

Bus *loadBusInfo() {
    //taking them as strings then we will parse some of them into to ints or whatever

    String busID;
    String date;
    String depTime;
    String fromDestination;
    String toDestination;
    String price;
    String capacity;

    Bus *tmpBus = null;


//    Bus tmpBus;

    FILE *pReadBus = null;
    pReadBus = fopen("busses.txt", "r");

    if (pReadBus == null) {
        printf("FILE NOT FOUND\n");
    }


    //    while (fgets(buffer, MAX_LINE, pReadBus)) {
//
//        busCnt++;
//    }

    char buffer[MAX_LINE];
    int sizeOfBusArray = countLines("busses.txt") + 1;
    printf("%d\n", sizeOfBusArray);

    Bus bussArray[sizeOfBusArray]; // +1 for the late students

    int i = 0;
    while (fgets(buffer, MAX_LINE, pReadBus)) {

        printf("%s", buffer);

        busID = strtok(buffer, "#");
        date = strtok(null, "#");
        depTime = strtok(null, "#");
        fromDestination = strtok(null, "#");
        toDestination = strtok(null, "#");
        price = strtok(null, "#");
        capacity = strtok(null, "#");

        tmpBus = malloc(sizeof(Bus));

        tmpBus->busID = atoi(busID);
        tmpBus->date = atoi(date);
        tmpBus->depTime = depTime;
        tmpBus->fromDestination = fromDestination;
        tmpBus->toDestination = toDestination;
        tmpBus->price = atof(price); // parsing double
        tmpBus->capacity = atoi(capacity);
        tmpBus->busNextPassenger = null;

        printf("%s -> %s\n", fromDestination,toDestination);


        bussArray[i] = *tmpBus;


        i++;
    }
    fclose(pReadBus);

    return bussArray;

}


Passenger *loadPassInfo() {
    return NULL;
}

int countLines(char *filename) {
    // count the number of lines in the file called filename
    FILE *fp = fopen(filename, "r");
    int ch = 0;
    int lines = 0;

    if (fp == NULL) {
        return 0;
    }

    lines++;
    while ((ch = fgetc(fp)) != EOF) {
        if (ch == '\n') {
            lines++;
        }
    }
    fclose(fp);
    return lines;
}
