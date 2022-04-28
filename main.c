/**
*
 *
 * Author: Faris Abufarha
 * SEC:3
 * ID: 1200546
 *
 *
*/
//#include<bits/stdc++.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define null NULL
#define ll long long
#define MAX_STRING 100
#define MAX_LINE 4095

typedef char String[MAX_STRING];



typedef struct Passenger {
    int passID;
    long passDate;
    String passengerDepTime;
    String passengerFromDestination;
    String passengerToDestination;

    struct Passenger *passengerNextPassenger;


} Passenger;

typedef struct Bus {

    int busID;
    //could be either string or int
    long date;
    String depTime;
    String fromDestination;
    String toDestination;
    double price;
    int maxCapacity;
    int currentCapacity;

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


int countLines(char *filename);         //CHECK THIS IF U GET AN ERROR

void memoryMsg();

void loadBusInfo(Bus *busArray);

void loadPassInfo(Bus *busArray, int busArraySize);

int busIndex(Bus *busArray, int sizeOfBusArray, Passenger passenger);

void printAllInfo(Bus * busArray, int busArraySize);

//plan b make the array global


int main() {

    //initializing the bus array

    int sizeOfBusArray = countLines("busses.txt") + 1;
    Bus busArray[sizeOfBusArray];

    printf("WELCOME\n");
    int selection;

    // MENU

    while (true) {


        //I MADE POINT 2 AND 3 IN ONE OPTION, LOAD AND ASSIGN, 3 FOR PRINTING ONLY              $((ASK!!!))
        printf("PLEASE SELECT AN OPTION:\n"
               "1. Load the bus information file\n"
               "2. Load the passenger information file and assign each passenger to his appropriate bus \n"
               "3. print assignment information of all busses\n"
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
                loadBusInfo(busArray);

//               for (int i = 0; i < 4; ++i) {                  PASS
//                    printf("id  %d\n", busArray[i].busID);
//                    printf("\nfrom dest bus : %s to : %s \n", busArray[i].fromDestination,
//                           busArray[i].toDestination);//test
//
//                }

                break;

            case 2:
                //load pass
                loadPassInfo(busArray, sizeOfBusArray);
                break;

            case 3:
                //print
                printAllInfo(busArray, sizeOfBusArray);
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

void loadBusInfo(Bus *busArray) {
    //taking them as strings then we will parse some of them into to ints or whatever

    //char* = String

    String busID          ;
    String date           ;
    String depTime        ;
    String fromDestination;
    String toDestination  ;
    String price          ;
    String maxCapacity    ;

//    Bus *tmpBus = null; // creates bus nodes

//    Bus tmpBus;

    FILE *pReadBus = null;
    pReadBus = fopen("busses.txt", "r");

    if (pReadBus == null) {
        printf("FILE NOT FOUND\n");
    }

    char buffer[MAX_LINE];
//    int sizeOfBusArray = countLines("busses.txt") + 1;// +1 for the late students


    int i = 0;
    while (fgets(buffer, MAX_LINE, pReadBus)) {

        printf("%s", buffer);

        strcpy(busID, strtok(buffer, "#"));
        strcpy(date, strtok(null, "#"));
        strcpy(depTime, strtok(null, "#"));
        strcpy(fromDestination, strtok(null, "#"));
        strcpy(toDestination, strtok(null, "#"));
        strcpy(price, strtok(null, "#"));
        strcpy(maxCapacity, strtok(null, "#"));


        printf("223: %s to : %s\n", fromDestination, toDestination);



//        tmpBus = malloc(sizeof(Bus));
//        if (tmpBus == null) {
//            memoryMsg();
//        }

//        tmpBus->busID                       = atoi(busID);
//        tmpBus->date                    = atoi(date);
//        tmpBus->depTime                    = depTime;
//        tmpBus->fromDestination             = fromDestination;
//        tmpBus->toDestination           = toDestination;
//        tmpBus->price                    = atof(price); // parsing double
//        tmpBus->maxCapacity                     = atoi(capacity);
//        tmpBus->currentCapacity             = 0;
//        tmpBus->busNextPassenger            = null;


        busArray[i].busID = atoi(busID);
        busArray[i].date = atol(date);

        strcpy(busArray[i].depTime, depTime);
        strcpy(busArray[i].fromDestination, fromDestination);
        strcpy(busArray[i].toDestination, toDestination);

        busArray[i].price = atof(price); // parsing double
        busArray[i].maxCapacity = atoi(maxCapacity);
        busArray[i].currentCapacity = 0;
        busArray[i].busNextPassenger = null;

//        printf("255: %d%s\n",busArray[i].busID, busArray[i].fromDestination);PASS


//        printf("237: %d\n",tmpBus->busID);    //THIS WORKS PASS
//        printf("237: %s\n",tmpBus->fromDestination);


        printf("TESTING ARRAY ID %d DEST from : %s TESTING TO: %s \n", busArray[i].busID, busArray[i].fromDestination,
               busArray[i].toDestination);

        i++;
    }
    fclose(pReadBus);
    //free busArray ??


}


void loadPassInfo(Bus *busArray, int busArraySize) {

    String passID                  ;     //initially int
    String passDate                ;  //int
    String passengerDepTime                ;
    String passengerFromDestination            ;
    String passengerToDestination          ;

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

        strcpy(passID ,strtok(buffer, "#"));
        strcpy(passDate , strtok(null, "#"));
        strcpy(passengerDepTime , strtok(null, "#"));
        strcpy(passengerFromDestination , strtok(null, "#"));
        strcpy(passengerToDestination , strtok(null, "#"));

        tmpPassenger = malloc(sizeof(Passenger));

        if (tmpPassenger == null) {

            memoryMsg();
            exit(1);
        }

        // assigning

        tmpPassenger->passID = atoi(passID); // converting string into int
        tmpPassenger->passDate = atol(passDate);
        strcpy(tmpPassenger->passengerDepTime , passengerDepTime);
        strcpy(tmpPassenger->passengerFromDestination , passengerFromDestination);
        strcpy(tmpPassenger->passengerToDestination , passengerToDestination);
        tmpPassenger->passengerNextPassenger = null;

//        printf("TESTING BUSARRAY IN LOADPASS: %s\n", busArray[2].fromDestination); PASS

        //  for checking the proper bus for each passenger
        indx = busIndex(busArray, busArraySize, *tmpPassenger);
        //CHECK POINT

        busArray[indx].currentCapacity++;  // incrementing the bus current number of passengers

        tmpPassenger->passengerNextPassenger = busArray[indx].busNextPassenger;
        busArray[indx].busNextPassenger = tmpPassenger;



        printf("indx: %d\n", indx);


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

int busIndex(Bus *busArray, int busArraySize, Passenger passenger) {

//    printf("%d:::%s\n", busArray[1].busID, busArray[1].fromDestination); PASS
//    printf("$$passenger %s\n",passenger.passengerToDestination);PASS

    for ( int i = 0; i < busArraySize - 1; i++) { // -1 to not search in the -late passengers section-)

//        printf("!!!bus indx fun TEST: ID: %d from dest : %s\n", busArray[i].busID, (busArray[i].fromDestination));PASS

//        if (strcmp( busArray[i].fromDestination, passenger.passengerFromDestination) == 0) { PASS
//            return i;
//        }
        String tmpBusTime;
        strcpy(tmpBusTime, busArray[i].depTime);
        tmpBusTime[2] = '0';
        String tmpPassTime;
        strcpy(tmpPassTime, passenger.passengerDepTime);
        tmpPassTime[2] = '0';   // converting : to '0' for comparison reasons

//        printf("%d\n", atoi(tmpBusTime));     PASS
//        printf("%d\n",busArray[i].maxCapacity); PASS

        String flushed;
        strcpy(flushed, passenger.passengerToDestination);
        for (int j = 0; j < sizeof(flushed); ++j) {
            if (flushed[j] =='\n'){
                flushed[j] = '\0';
                break;
            }
        }
        //inorder to remove '\n' from the string

        if (busArray[i].date == passenger.passDate
            && atoi(tmpBusTime) >= atoi(tmpPassTime)
            && strcasecmp(busArray[i].fromDestination, passenger.passengerFromDestination) == 0
            && strcasecmp(busArray[i].toDestination, flushed) == 0
            && busArray[i].currentCapacity < busArray[i].maxCapacity
            ) {

            return i;
        }

        // in case none of busses is suitable

    }
    return (busArraySize - 1);//last index
}


void printAllInfo(Bus * busArray, int busArraySize) {

    //visiting all busses

    // last block is for the late ppl so '-1'

    for (int i = 0; i < busArraySize - 1 ; ++i) {


        printf("passengers info in BUS %d date: %ld departure time: %s from %s to %s ticket price %f capacity %d\n",
               busArray[i].busID
               ,busArray[i].date
               ,busArray[i].depTime
               ,busArray[i].fromDestination
               ,busArray[i].toDestination
               ,busArray[i].price
               ,busArray[i].maxCapacity
               );

        if (busArray[i].busNextPassenger == null ) {

            printf("EMPTY BUS \n");
            continue;
        }

        for (Passenger *iter = busArray[i].busNextPassenger; iter != NULL; iter = iter -> passengerNextPassenger ) {
            printf("Passenger: ID: %d date: %ld  time: %s from: %s to: %s\n"
                   ,iter ->passID
                   ,iter ->passDate
                   ,iter ->passengerDepTime
                   ,iter ->passengerFromDestination
                   ,iter ->passengerToDestination
                   );

        }

    }



    printf("PASSENGERS WITH NO BUSSES: \n");
    for (Passenger *iter = busArray[busArraySize - 1].busNextPassenger; iter != NULL; iter = iter -> passengerNextPassenger ) {
        printf("Passenger: ID: %d date: %ld date:%s time: %s from: %s to: %s\n"
                ,iter ->passID
                ,iter ->passDate
                ,iter ->passengerDepTime
                ,iter ->passengerFromDestination
                ,iter ->passengerToDestination
        );

    }

    //    if (isEmpty(head)) {
//        //printf("empty bus\n");
//        return;
//    }
//    for (node *iter = head->next; iter != NULL; iter = iter->next) {
//        printf("%d ", iter->num);
//
//    }
//    printf("\n");
}

//info of bus without the passengerts



//
//bool isEmpty(Passenger *pass) {
//    if (pass->passengerNextPassenger == null) {
//
//        return true;
//
//    }
//    else {
//        return false;
//    }







//LINKED LIST FUNCTIONS

//
//
//int sizeOfList(node *head) {
//
//    int cnt = 0;
//    for (node *iter = head->next; iter != NULL; iter = iter->next) {
//        cnt++;
//    }
//
//
//    return cnt;
//
//}
//
//void deleteList(node *head) {
//    node *tmp = null;
//    for (node *iter = head->next; iter != NULL;) {
//
//        tmp = iter;
//        iter = iter->next;
//        tmp->next = null;
//        free(tmp);
//
//    }
//
//    head->next = null;
//

//    node *tmp = null;
//    node *iter = head->next;
//
//    head->next = null;
//
//    for (; iter != NULL; iter = iter->next) {
//
//        tmp = iter->next;
//        free(iter);
//
//        iter = tmp;
//
//
//    }

    // u can free head here



//


//
//void insertAtBeginning(int x, node *head) {
//    node *tmp = malloc(sizeof(node));
//    tmp->num = x;
//    tmp->next = head->next;
//
//    head->next = tmp;
//
//    free(tmp);
//
//}

//void deleteNode(int x, node *head) {
//
////    for (node *i = head;i!= null && i;  < ; ++) {
////
////    }
//    node *tmp = null;
//
//    node *prev = findPrev(x, head);
//    if (!isLast(prev, head)) {
//        tmp = prev->next;
//        prev->next = tmp->next;
//        free(tmp);
//
//
//    }
//
//
//}

//
