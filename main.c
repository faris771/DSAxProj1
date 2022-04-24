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
    int passID;
    int passDate;
    String passengerDepTime;
    String passengerFromDestination;
    String passengerToDestination;

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
    int maxCapacity;
    int currentCapacity ;

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

int busIndex(Bus * busArray,int sizeOfBusArray, Passenger passenger);

//plan b make the array global

Passenger *loadPassInfo(Bus * busArray, int busArraySize);


int main() {

    Bus *busArray = null;

    int sizeOfBusArray = countLines("busses.txt") + 1;

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
                printf("ID IS : %s \n", busArray[3].toDestination);//test

                break;

            case 2:
                //load pass
                loadPassInfo(busArray, sizeOfBusArray);
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
                return 0;
            default:
                puts("PLEASE ENTER VALID INPUT");
                break;

        }


    }

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

    char buffer[MAX_LINE];
    int sizeOfBusArray = countLines("busses.txt") + 1;// +1 for the late students
    printf("%d\n", sizeOfBusArray);

    Bus *bussArray = malloc(sizeof(Bus) * sizeOfBusArray);

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
        if (tmpBus == null) {
            memoryMsg();
        }

        tmpBus->busID = atoi(busID);
        tmpBus->date = atoi(date);
        tmpBus->depTime = depTime;
        tmpBus->fromDestination = fromDestination;
        tmpBus->toDestination = toDestination;
        tmpBus->price = atof(price); // parsing double
        tmpBus->maxCapacity = atoi(capacity);
        tmpBus->currentCapacity = 0;
        tmpBus->busNextPassenger = null;

        bussArray[i] = *tmpBus;

//        free(tmpBus);

        i++;
    }
    fclose(pReadBus);
    //free busArray ??

    return bussArray;

}


Passenger *loadPassInfo(Bus * busArray, int busArraySize) {

    String passID;     //initially int
    String passDate;   //int
    String passengerDepTime;
    String passengerFromDestination;
    String passengerToDestination;

    Passenger *tmpPassenger = null;

    FILE *pReadPass = null;
    pReadPass = fopen("passengers.txt", "r");

    if (pReadPass == null) {

        printf("FILE NOT FOUND\n");
        exit(1);

    }

    char buffer[MAX_LINE];
//    int sizeOfBusArray = countLines("passengers.txt") + 1;
//    Bus *bussArray = malloc(sizeof(Bus) * sizeOfBusArray); // +1 for the late students

    int indx;
    while (fgets(buffer, MAX_LINE, pReadPass)) {

        passID = strtok(buffer, "#");
        passDate = strtok(null, "#");
        passengerDepTime = strtok(null, "#");
        passengerFromDestination = strtok(null, "#");
        passengerToDestination = strtok(null, "#");

        tmpPassenger = malloc(sizeof(Passenger));

        if (tmpPassenger == null) {

            memoryMsg();
            exit(1);
        }

        tmpPassenger->passID = atoi(passID); // converting string into int
        tmpPassenger->passDate = atoi(passDate);
        tmpPassenger->passengerDepTime = passengerDepTime;
        tmpPassenger->passengerFromDestination = passengerFromDestination;
        tmpPassenger->passengerToDestination = passengerToDestination;
        tmpPassenger->passengerNextPassenger = null;

        printf("TESTING BUSARRAY IN LOADPASS: %s\n",busArray[1].fromDestination);
        indx = busIndex(busArray, busArraySize,*tmpPassenger);

        //dbg: it reads

        printf("indx: %d\n",indx);


    }

    fclose(pReadPass);


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

//returns what the bus index should the passenger be in

int busIndex(Bus *busArray,int busArraySize,  Passenger passenger) {

    printf("ID: %d from dest : %s\n",busArray[0].busID, (busArray[0].fromDestination));
//    for (int i = 0; i < busArraySize - 1; ++i) { // -1 to not search in the -late passengers section)

        //        if (strcmp( busArray[i].fromDestination, passenger.passengerFromDestination) == 0) {
//            return i;
//        }


//        if (busArray[i].date >= passenger.passDate
//        && atoi(busArray[i].depTime) >= atoi(passenger.passengerDepTime)
//        && strcmp( busArray[i].fromDestination , passenger.passengerFromDestination) == 0
//        && strcmp(busArray[i].toDestination , passenger.passengerToDestination) == 0
//        && busArray[i].currentCapacity < busArray[i].maxCapacity) {
//
//            return i;
//        }


    // in case none of busses is suitable
    return (busArraySize - 1);


}
