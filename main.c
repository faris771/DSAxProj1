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

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


#define null NULL
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
    int numberOfPassengers;
    struct Passenger *busNextPassenger;


} Bus;

int countLines(String filename);

void memoryMsg();

void loadBusInfo(Bus *busArray);

void loadPassInfo(Bus *busArray, int busArraySize);

int busIndex(Bus *busArray, int sizeOfBusArray, Passenger passenger);

void printAllInfo(Bus *busArray, int busArraySize);

void addNewPassenger(Bus *busArray, int busArraySize);

void deletePassenger(Bus *busArray, int busArraySize);

void deleteBus(Bus *busArray, int busArraySize);

void printUnmatched(Bus *busArray, int busArraySize);

void printBus(Bus *busArray, int busArraySize);

void freeAll(Bus *busArray, int busArraySize);

void art();

int main() {

    //initializing the bus array

    int sizeOfBusArray = countLines("busses.txt") + 1; // +1 FOR LATE PEOPLE
    Bus busArray[sizeOfBusArray];
    printf("================================================================\n");
    printf("                 _                              \n"
           "                | |                             \n"
           " __      __ ___ | |  ___  ___   _ __ ___    ___ \n"
           " \\ \\ /\\ / // _ \\| | / __|/ _ \\ | '_ ` _ \\  / _ \\\n"
           "  \\ V  V /|  __/| || (__| (_) || | | | | ||  __/\n"
           "   \\_/\\_/  \\___||_| \\___|\\___/ |_| |_| |_| \\___|\n"
           "                                                \n"
           "                                                \n");
    int selection;

    // MENU

    bool isLoadedBus = false;
    bool isLoadedPass = false;
    char tmpChoice;
    while (true) {


        printf("================================================================\n");
        printf("PLEASE SELECT AN OPTION:\n"
               "1. Load  busses information file\n"
               "2. Load the passengers information file and assign each passenger to his appropriate bus \n"
               "3. print assignment information of all busses\n"
               "4. Print a specific bus information along with its passengers\n"
               "information (names and IDs)\n"
               "5. Print unmatched passengers\n"
               "6. Add new Passenger\n"
               "7. Delete Passenger\n"
               "8. Delete bus number\n"
               "9. Exit"
               "\n");

        scanf("%d", &selection);

        printf("================================================================\n");

        switch (selection) {

            case 1:
                //load bus
                if (isLoadedBus) {
                    printf("busses already loaded\n");
                    break;
                }
                loadBusInfo(busArray);
                isLoadedBus = true;
                break;

            case 2:
                //load pass
                if (!isLoadedBus) {
                    printf("BUSSES INFO NOT LOADED YET\nPRESS '1' TO LOAD IT\n");
                    break;
                }
                if (isLoadedPass) {
                    printf("passengers already loaded\n");
                    break;
                }

            a:;
                loadPassInfo(busArray, sizeOfBusArray);
                isLoadedPass = true;
                break;

            case 3:
                if (!isLoadedBus) {
                    printf("BUSSES INFO NOT LOADED YET\nPRESS '1' TO LOAD IT\n");
                    break;
                }
                //prints all busses info ( not including unmatched passengers )
                printAllInfo(busArray, sizeOfBusArray);
                break;

            case 4:
                if (!isLoadedBus) {
                    printf("BUSSES INFO NOT LOADED YET\nPRESS '1' TO LOAD IT\n");
                    break;
                }
                printBus(busArray, sizeOfBusArray);

                break;

            case 5:
                if (!isLoadedBus) {
                    printf("BUSSES INFO NOT LOADED YET\nPRESS '1' TO LOAD IT\n");
                    break;
                }
                printUnmatched(busArray, sizeOfBusArray);
                break;

            case 6:
                if (!isLoadedBus) {
                    printf("BUSSES INFO NOT LOADED YET\nPRESS '1' TO LOAD IT\n");
                    break;
                }

                addNewPassenger(busArray, sizeOfBusArray);

                break;
            case 7:
                if (!isLoadedBus) {
                    printf("BUSSES INFO NOT LOADED YET\nPRESS '1' TO LOAD IT\n");
                    break;
                }
                deletePassenger(busArray, sizeOfBusArray);
                break;
            case 8:
                if (!isLoadedBus) {
                    printf("BUSSES INFO NOT LOADED YET\nPRESS '1' TO LOAD IT\n");
                    break;
                }
                deleteBus(busArray, sizeOfBusArray);
                break;


            case 9:
                printf("                    THANK YOU, COME AGAIN :)\n");
                art();
                freeAll(busArray, sizeOfBusArray);
                return 0;
            default:
                puts("PLEASE ENTER VALID INPUT");
                break;

        }


    }

}

void art() {
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡤⠤⠶⠶⠒⠒⠒⠒⠢⠤⢄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠴⠊⢡⣠⣆⡵⠦⠤⠄⠐⠾⠴⣦⣰⣈⡑⠢⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠴⠓⠂⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠓⠺⢶⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠴⠊⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⣤⡶⠋⠀⠀⠀⠀⠀⠀⠉⠳⢤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠎⡀⠀⠂⠀⠀⠀⠀⠀⢀⣤⣶⣿⣿⣿⣿⣿⣭⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠢⣄⠀⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠔⢉⠅⡢⡨⡀⢠⡠⠀⢀⣴⣾⣿⠟⣿⠁⠸⣿⣿⣯⢻⣿⣿⣷⣦⣀⢐⠂⠀⢀⠀⠀⠀⠠⠘⢦⡀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⢠⠊⠀⠃⠪⡠⡪⣜⠆⣨⣾⣿⣿⡿⠁⠀⢻⠀⠀⠹⣿⣿⡄⠙⣿⣿⣿⣿⣷⣴⣈⢆⢄⢔⡹⡢⠑⠀⠳⡄⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⢠⠃⠀⠀⠀⠀⡄⡐⠁⣼⣿⣿⢿⡟⠁⠀⠀⠘⠀⠀⠀⠈⢻⣇⠀⠈⢿⡟⣿⣿⣿⡿⡗⠋⠊⠀⠀⠀⠀⠀⠹⡄⠀⠀⠀\n"
           "⠀⠀⠀⠀⢀⠊⠄⠀⠀⠀⠀⠀⠈⣸⣿⣿⠏⡞⠒⠒⠂⠤⠀⠀⠀⠀⠀⠀⠙⠂⠉⠈⢻⠸⣿⣿⣧⡚⠌⠴⡠⣠⢀⠀⠀⠀⢹⡀⠀⠀\n"
           "⠀⠀⠀⠀⡎⢸⡘⡌⣦⡐⣦⠲⡰⣿⣿⡟⠀⠁⠀⣀⡀⠀⠀⠀⢀⠀⠀⠀⠀⢀⣠⣤⣀⠁⢻⣿⣿⣿⡷⡞⣱⢃⠞⠄⠠⠀⠈⡇⠀⠀\n"
           "⠀⠀⠀⢰⢣⢰⠘⡌⣦⢀⡦⠜⠀⠀⣿⠃⠀⣰⠟⠉⠛⠦⠀⠀⢸⡆⠀⠀⠀⠟⠉⠉⠙⠆⠈⣿⡷⠅⠀⠙⡇⣾⣶⠀⡆⢠⠀⡇⠀⠀\n"
           "⠀⠀⠀⢸⠸⡘⢠⡃⢋⢹⠀⠀⠀⠀⢻⠀⡀⡋⡀⠀⠀⠀⠀⠀⠘⠐⠀⠀⠀⠐⠒⠆⠰⠆⡦⢠⠇⠀⠀⠀⢸⡝⡋⠀⠷⡈⢀⠇⠀⠀\n"
           "⠀⠀⠀⠘⡆⡇⡜⣃⠜⢹⠀⠀⠀⠀⠚⡾⠛⢉⣄⡤⠀⠒⠒⠈⠉⠉⠉⠉⠉⠉⠁⠐⢖⢤⡀⢸⠄⠀⠀⠀⡰⠠⡙⣌⢧⡘⡜⠀⠀⠀\n"
           "⠀⠀⠀⠀⢣⠞⡄⡵⡀⠚⠀⠀⠀⠀⠀⢥⠀⣿⠀⠁⢀⣠⣴⣶⣾⣿⣿⣿⣷⣶⣶⣄⡀⢸⠁⡾⡑⠡⠄⠀⠥⡐⠞⡔⠕⡰⠁⠀⠀⠀\n"
           "⠀⠀⠀⠀⠸⣌⠈⡊⠄⠀⡀⠀⠀⠀⠄⢙⠆⠘⢶⣾⣿⠿⠛⠉⠉⠉⠉⠉⠉⠙⠿⣿⡿⠁⠰⠖⠚⠊⠀⠙⣆⠈⡞⢁⠔⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠈⢦⡈⠀⠀⡱⡆⢀⠥⠠⠨⣚⡄⠀⠻⢤⡔⠒⠀⠀⠉⠉⠉⠉⠐⡢⠍⡔⠂⢭⡠⠀⠀⠀⢠⡙⡠⢭⢅⠀⠀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠈⠓⢵⡊⡩⠮⡌⣄⢭⡛⣸⡦⣄⡀⠈⠓⠒⠒⠐⠒⠒⠂⠁⠠⢐⡀⠀⠀⠀⠀⠀⠀⢜⢪⡇⠚⡄⠧⡀⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢉⠡⠶⠬⠭⢽⠿⢿⠝⣉⡟⠿⣶⢦⣤⣤⣤⣤⣶⣾⣿⣇⠣⠄⠤⠔⠉⠉⠑⠂⡁⠨⣀⠷⠀⢰⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠀⢀⣔⡪⣥⠀⠀⠀⠀⠀⠀⠀⠉⠙⢇⠀⠈⠺⣿⣿⢿⣿⣿⠟⡸⠚⠉⠁⠁⠀⠀⠀⢀⠠⢑⠢⢥⠅⢒⡁⠀⠀⠀⠀\n"
           "⠀⠀⠀⠀⠀⠀⠜⠁⠀⠈⠀⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠉⠲⢄⠈⠉⢹⠻⠯⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠘⡆⠀⠀⠀\n"
           "⠀⠀⠀⢀⠔⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⠀⡀⠀⡠⠕⠒⠉⠀⠀⠀⣠⠞⠔⠀⠀⠀⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠑⠀⠀⠀\n"
           "⠀⠀⠀⢸⠀⠀⡀⡀⣠⣁⣠⣥⣶⣶⣾⣷⣶⣤⣢⣆⡥⣡⠼⠀⠀⣠⡠⠐⠀⠻⠋⣀⠀⡀⣄⣮⢬⡚⢔⢆⣀⣠⠁⢀⡈⢐⢨⠀⠀⠀\n"
           "⠀⠀⠀⢸⢨⣠⣵⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠊⠀⠀⠀⠛⡋⡀⢀⣴⣼⣾⣾⣿⣿⣿⣿⣷⣾⣿⣷⣶⣿⣬⣧⣲⣼⠀⠀⠀\n"
           "⠀⠀⠀⢨⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠿⢿⣿⣿⣿⣿⣿⣷⣴⣱⡄⣆⣦⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣄⠀⠀\n"
           "⠀⠀⢀⣾⣿⣿⣿⣿⠍⠀⢀⠀⠀⠀⠀⠀⠀⠀⠉⠉⠛⠻⣿⠟⠛⠛⠛⢿⠛⠉⠉⠉⠉⠉⠉⠉⠉⠉⠉⠙⡛⠉⣹⣿⣿⣿⣿⣿⣆⠀\n"
           "⠀⠀⣼⣿⡿⠟⠛⠛⢣⠀⢸⠀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⠁⡐⠉⠉⠉⠉⠉⠛⠻⡄\n"
           "⠀⡘⠋⠉⠀⠀⠀⠀⠀⢡⠸⠀⠃⠀⢀⣀⣀⣤⣤⣤⣤⣤⣸⣠⣤⣤⣤⣸⣀⣤⣤⣤⣤⣤⣤⣄⣀⣀⡀⡸⢰⠀⠀⠀⠀⠀⠀⠀⠀⠰\n"
           "⢰⢁⣀⣤⣤⣤⣤⣄⠀⠀⣴⣾⣶⣿⣿⠿⠿⠿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣶⣤⣤⡀⣀⣀⣀⣀⣀\n"
           "⣾⣿⣿⣿⣿⣿⣿⣿⣷⣄⢻⣿⣿⠏⠀⠀⠀⠀⠀⢀⣿⣿⣿⣿⣿⣿⡿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣾⣿⡿⠀⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⡇⠀⠉⠙⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⣿⣯⣿⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿\n"
           "⠿⠛⠉⠉⠉⠀⣈⣭⣿⣿⣿⣿⣧⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⠫⠉⠉⠒⠢⢄⠈⠙⠻\n");


}


void memoryMsg() {

    printf("OUT OF MEMORY!\n");
}

void loadBusInfo(Bus *busArray) {
    //taking them as strings then we will parse some of them into to ints or whatever

    String busID;
    String date;
    String depTime;
    String fromDestination;
    String toDestination;
    String price;
    String maxCapacity;

    FILE *pReadBus = null;
    pReadBus = fopen("busses.txt", "r");

    if (pReadBus == null) {
        printf("FILE NOT FOUND\n");
        exit(1);

    }

    char buffer[MAX_LINE];

    int i = 0;
    while (fgets(buffer, MAX_LINE, pReadBus)) {  // for busses in the file ( NOT INCLUDING UNMATCHED LIST)

        //printf("%s", buffer);

        strcpy(busID, strtok(buffer, "#"));
        strcpy(date, strtok(null, "#"));
        strcpy(depTime, strtok(null, "#"));
        strcpy(fromDestination, strtok(null, "#"));
        strcpy(toDestination, strtok(null, "#"));
        strcpy(price, strtok(null, "#"));
        strcpy(maxCapacity, strtok(null, "#"));

        // PARSING

        busArray[i].busID = atoi(busID);
        busArray[i].date = atol(date);

        strcpy(busArray[i].depTime, depTime);
        strcpy(busArray[i].fromDestination, fromDestination);
        strcpy(busArray[i].toDestination, toDestination);

        busArray[i].price = atof(price); // parsing double
        busArray[i].maxCapacity = atoi(maxCapacity);
        busArray[i].numberOfPassengers = 0;
        busArray[i].busNextPassenger = null;


        i++;
    }

    //to make the LATE PEOPLE list (UNMATCHED)
    busArray[i].busNextPassenger = null;

    printf("LOADED SUCCESSFULLY\n");
    fclose(pReadBus);
    //free busArray ??


}


void loadPassInfo(Bus *busArray, int busArraySize) {

    String passID;     //initially int
    String passDate;  //int
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

        strcpy(passID, strtok(buffer, "#"));
        strcpy(passDate, strtok(null, "#"));
        strcpy(passengerDepTime, strtok(null, "#"));
        strcpy(passengerFromDestination, strtok(null, "#"));
        strcpy(passengerToDestination, strtok(null, "#"));

        tmpPassenger = malloc(sizeof(Passenger));

        if (tmpPassenger == null) {

            memoryMsg();
            exit(1);
        }

        // assigning

        tmpPassenger->passID = atoi(passID); // converting string into int
        tmpPassenger->passDate = atol(passDate);
        strcpy(tmpPassenger->passengerDepTime, passengerDepTime);
        strcpy(tmpPassenger->passengerFromDestination, passengerFromDestination);
        strcpy(tmpPassenger->passengerToDestination, passengerToDestination);
        tmpPassenger->passengerNextPassenger = null;

//        printf("TESTING BUSARRAY IN LOADPASS: %s\n", busArray[2].fromDestination); PASS

        //  for checking the proper bus for each tmpPassenger
        indx = busIndex(busArray, busArraySize, *tmpPassenger);

        busArray[indx].numberOfPassengers++;  // incrementing the bus current number of passengers
        tmpPassenger->passengerNextPassenger = busArray[indx].busNextPassenger; //
        busArray[indx].busNextPassenger = tmpPassenger;


//        printf("indx: %d\n", indx); PASS

//  DO NOT FREE HERE
    }
    busArray[busArraySize - 1].busID = -1;

    printf("PASSENGERS LOADED AND ASSIGNED SUCCESSFULLY\n");

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

//returns what the bus index should the tmpPassenger be in

int busIndex(Bus *busArray, int busArraySize, Passenger passenger) {

//    printf("%d:::%s\n", busArray[1].busID, busArray[1].fromDestination); PASS
//    printf("$$tmpPassenger %s\n",tmpPassenger.passengerToDestination);PASS

    for (int i = 0; i < busArraySize - 1; i++) { // -1 to not search in the -late passengers section-)

//        printf("!!!bus indx fun TEST: ID: %d from dest : %s\n", busArray[j].busID, (busArray[j].fromDestination));PASS

//        if (strcmp( busArray[j].fromDestination, tmpPassenger.passengerFromDestination) == 0) { PASS
//            return j;
//        }
        String tmpBusTime;
        strcpy(tmpBusTime, busArray[i].depTime);
        tmpBusTime[2] = '0';
        String tmpPassTime;
        strcpy(tmpPassTime, passenger.passengerDepTime);
        tmpPassTime[2] = '0';   // converting : to '0' for comparison reasons

//        printf("%d\n", atoi(tmpBusTime));     PASS
//        printf("%d\n",busArray[j].maxCapacity); PASS

        String flushed;
        strcpy(flushed, passenger.passengerToDestination);
        for (int j = 0; j < sizeof(flushed); ++j) {
            if (flushed[j] == '\n') {
                flushed[j] = '\0';
                break;
            }
        }
        //inorder to remove '\n' from the string

        if (busArray[i].date == passenger.passDate
            && atoi(tmpBusTime) >= atoi(tmpPassTime)
            && strcasecmp(busArray[i].fromDestination, passenger.passengerFromDestination) == 0
            && strcasecmp(busArray[i].toDestination, flushed) == 0
            && busArray[i].numberOfPassengers < busArray[i].maxCapacity
                ) {

            return i;
        }

        // in case none of busses is suitable

    }
    return (busArraySize - 1);//last index
}


void printAllInfo(Bus *busArray, int busArraySize) {

    //visiting all busses

    // last block is for the unmatched psngrs so '-1'

    for (int i = 0; i < busArraySize - 1; ++i) {

        if (busArray[i].busID == -1) {
//            printf("PASSED\n");
            continue;
        }

        printf("BUS %d date: %ld departure time: %s from %s to %s ticket price %.2f capacity %d\n",
               busArray[i].busID, busArray[i].date, busArray[i].depTime, busArray[i].fromDestination,
               busArray[i].toDestination, busArray[i].price, busArray[i].maxCapacity
        );

        if (busArray[i].busNextPassenger == null) {

            printf("EMPTY BUS \n");
            continue;
        }

        // each tmpPassenger in each bus
        for (Passenger *iter = busArray[i].busNextPassenger; iter != NULL; iter = iter->passengerNextPassenger) {
            printf("Passenger: ID: %d date: %ld  time: %s from: %s to: %s\n", iter->passID, iter->passDate,
                   iter->passengerDepTime, iter->passengerFromDestination, iter->passengerToDestination
            );

        }

    }


}

//still, spaced string not fixed
void addNewPassenger(Bus *busArray, int busArraySize) {

    printf("INPUT NEW PASSENGER'S:"
           "ID, DATE, TIME RESPECTIVELY  "
           "\n");


    int passID;
    long passDate;
    String passengerDepTime;
    String passengerFromDestination;
    String passengerToDestination;
    //pointer

    Passenger *tmpPassenger = null;
    tmpPassenger = malloc(sizeof(Passenger));
    if (tmpPassenger == null) {

        memoryMsg();
        exit(1);
    }

//    scanf("%d%ld%s%s%s", &passID, &passDate, passengerDepTime, passengerFromDestination, passengerToDestination);
    scanf("%d%ld%s", &passID, &passDate, passengerDepTime);   //
    fgetc(stdin);//GETS RID OF NEWLINE
    //
    Passenger *tmpPass = null;
    Passenger *nextPass = null;
    int indx1 = 0;

    for (indx1 = 0; indx1 < busArraySize; ++indx1) {
        tmpPass = busArray[indx1].busNextPassenger;

        for (Passenger *iter = tmpPass; iter != NULL;) {

            nextPass = iter;
            iter = iter->passengerNextPassenger;
            if (nextPass->passID == passID) {
                printf("ID TAKEN\n");
                return;
            }

        }

    }

    //

    printf("INPUT FROM  DESTINATION,\n");
    fgets(passengerFromDestination, MAX_STRING, stdin);

    for (int i = 0; i < sizeof(passengerFromDestination); ++i) {
        if (passengerFromDestination[i] == '\n') {
            passengerFromDestination[i] = '\0';
            break;
        }
    }
//    passengerFromDestination[strlen(passengerFromDestination) - 1] = '\0';// getting rid of \n

    printf("INPUT TO DESTINATION \n");
    fgets(passengerToDestination, MAX_STRING, stdin);
    for (int i = 0; i < sizeof(passengerToDestination); ++i) {
        if (passengerToDestination[i] == '\n') {
            passengerToDestination[i] = '\0';
            break;
        }
    }
    printf("%s", passengerToDestination);


//    passengerToDestination[strlen(passengerToDestination) - 1] = '\0';// getting rid of \n


    tmpPassenger->passID = (passID); // converting string into int
    tmpPassenger->passDate = (passDate);
    strcpy(tmpPassenger->passengerDepTime, passengerDepTime);
    strcpy(tmpPassenger->passengerFromDestination, passengerFromDestination);
    strcpy(tmpPassenger->passengerToDestination, passengerToDestination);
    tmpPassenger->passengerNextPassenger = null;


    int indx = busIndex(busArray, busArraySize, *tmpPassenger);

    busArray[indx].numberOfPassengers++;  // incrementing the bus current number of passengers
    tmpPassenger->passengerNextPassenger = busArray[indx].busNextPassenger; //
    busArray[indx].busNextPassenger = tmpPassenger;

}

void deletePassenger(Bus *busArray, int busArraySize) {

    printf("PLEASE INPUT PASSENGER ID YOU WANT TO DELETE \n");

    int passID;
    scanf("%d", &passID);

    bool isLast;
    for (int i = 0; i < busArraySize; ++i) {


        // each tmpPassenger in each bus
        for (Passenger *iter = busArray[i].busNextPassenger; iter != null; iter = iter->passengerNextPassenger) {

            isLast = iter->passengerNextPassenger == null;
            // in case the first pass was the one


            if (iter->passID == passID) {

                Passenger *tmpPass = null;
                tmpPass = iter;
                busArray[i].busNextPassenger = tmpPass->passengerNextPassenger;
                free(tmpPass);
                printf("PASSENGER DELETED SUCCESSFULLY\n");
                busArray[i].numberOfPassengers--;
                return;

            }


            if (iter->passengerNextPassenger != null && iter->passengerNextPassenger->passID == passID) {
                //like findPrevious
                Passenger *tmpPass = null;
                tmpPass = iter->passengerNextPassenger;
                iter->passengerNextPassenger = tmpPass->passengerNextPassenger;
                free(tmpPass);
                printf("PASSENGER DELETED SUCCESSFULLY\n");
                busArray[i].numberOfPassengers--;
                return;
            }

        }

    }

    printf("PASSENGER DOESN'T EXIST ! \n");


}

void deleteBus(Bus *busArray, int busArraySize) {

    int bdx;    // bus indx


    printf("INPUT BUS ID YOU WANT TO DELETE \n");

    int ID;
    scanf("%d", &ID);

    bool flag = false;

    int indx;// indx of bus u want to delete

    for (int i = 0; i < busArraySize - 1; ++i) {
        if (busArray[i].busID == ID) {

            flag = true;
            indx = i;
            break;

        }

    }
    if (!flag) {

        printf("BUS DOESN'T EXIST \n");
        return;
    }

    Passenger *tmpPass = null;
    Passenger *nextPass = null;
    tmpPass = busArray[indx].busNextPassenger;

    //shifting
    for (int i = indx; i < busArraySize - 1; ++i) {
        busArray[i] = busArray[i + 1];
    }


    for (Passenger *iter = tmpPass; iter != NULL;) {

        nextPass = iter;
        iter = iter->passengerNextPassenger;
        nextPass->passengerNextPassenger = null; // assign this

        for (int i = 0; i < busArraySize - 1; ++i) {

            String tmpBusTime;
            strcpy(tmpBusTime, busArray[i].depTime);
            tmpBusTime[2] = '0';
            String tmpPassTime;
            strcpy(tmpPassTime, nextPass->passengerDepTime);
            tmpPassTime[2] = '0';   // converting : to '0' for comparison reasons


            String flushed;
            strcpy(flushed, nextPass->passengerToDestination);
//                    flushed[strlen(flushed) -1] = '\0'; ALREADY FLUSHED
            for (int z = 0; z < sizeof(flushed); ++z) {
                if (flushed[z] == '\n') {
                    flushed[z] = '\0';
                    break;
                }
            }
            //inorder to remove '\n' from the string


            if (busArray[i].date == nextPass->passDate
                && atoi(tmpBusTime) >= atoi(tmpPassTime)
                && strcasecmp(busArray[i].fromDestination, nextPass->passengerFromDestination) == 0
                && strcasecmp(busArray[i].toDestination, flushed) == 0
                && busArray[i].numberOfPassengers < busArray[i].maxCapacity
                && i != indx) {

                bdx = i;
                goto f1;

            }


        }

        bdx = busArraySize - 1; // in case no bus is suitable

        f1:;

        nextPass->passengerNextPassenger = busArray[bdx].busNextPassenger;
        busArray[bdx].busNextPassenger = nextPass;


    }
    printf("DELETED \n");


}


void printUnmatched(Bus *busArray, int busArraySize) {
    FILE *tmpFile = fopen("tmpFile.txt", "w");


    printf("PASSENGERS WITH NO BUSSES: \n");
//    fprintf(tmpFile,"PASSENGERS WITH NO BUSSES: \n");


    for (Passenger *iter = busArray[busArraySize - 1].busNextPassenger;
         iter != NULL; iter = iter->passengerNextPassenger) {
        printf("Passenger: ID: %d date: %ld time: %s from: %s to: %s\n", iter->passID, iter->passDate,
               iter->passengerDepTime, iter->passengerFromDestination, iter->passengerToDestination
        );
        fprintf(tmpFile,"Passenger: ID: %d date: %ld time: %s from: %s to: %s", iter->passID, iter->passDate,
                iter->passengerDepTime, iter->passengerFromDestination, iter->passengerToDestination
        );


    }

    fclose(tmpFile);

}

void printBus(Bus *busArray, int busArraySize) {
    printf("INPUT BUS ID YOU'RE LOOKING FOR\n");
    int id;
    scanf("%d", &id);


    for (int i = 0; i < busArraySize - 1; ++i) {

        if (busArray[i].busID == id) {

            printf("BUS %d date: %ld departure time: %s from %s to %s ticket price %.2f capacity %d\n",
                   busArray[i].busID, busArray[i].date, busArray[i].depTime, busArray[i].fromDestination,
                   busArray[i].toDestination, busArray[i].price, busArray[i].maxCapacity
            );

            if (busArray[i].busNextPassenger == null) {

                printf("EMPTY BUS \n");
                return;

            }

            // each tmpPassenger in each bus
            for (Passenger *iter = busArray[i].busNextPassenger; iter != NULL; iter = iter->passengerNextPassenger) {
                printf("Passenger: ID: %d   time: %s \n", iter->passID,
                       iter->passengerDepTime
                );

            }
            return;

        }


    }
    printf("BUS DOESN'T EXIST\n");

}

void freeAll(Bus *busArray, int busArraySize) {

    Passenger *tmpPass = null;
    Passenger *nextPass = null;

    for (int indx = 0; indx < busArraySize; ++indx) {
        tmpPass = busArray[indx].busNextPassenger;

        for (Passenger *iter = tmpPass; iter != NULL;) {

            nextPass = iter;
            iter = iter->passengerNextPassenger;
            free(nextPass);


        }


    }


}




/*
 *
 *              THANK YOU
 * ⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⠋⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠈⢻⣿⣿⡄⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣸⣿⡏⠀⠀⠀⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⢰⣿⣿⣯⠁⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣷⡄⠀
⠀⠀⣀⣤⣴⣶⣶⣿⡟⠀⠀⠀⢸⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣷⠀
⠀⢰⣿⡟⠋⠉⣹⣿⡇⠀⠀⠀⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿⠀
⠀⢸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀
⠀⣸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇⠀⠀
⠀⣿⣿⠁⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣧⠀⠀
⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀
⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀
⠀⢿⣿⡆⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀
⠀⠸⣿⣧⡀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠃⠀⠀
⠀⠀⠛⢿⣿⣿⣿⣿⣇⠀⠀⠀⠀⠀⣰⣿⣿⣷⣶⣶⣶⣶⠶⠀⢠⣿⣿⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⣽⣿⡏⠁⠀⠀⢸⣿⡇⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⢹⣿⡆⠀⠀⠀⣸⣿⠇⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁⠀⠈⠻⣿⣿⣿⣿⡿⠏⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠈⠛⠻⠿⠿⠿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
 *
 *
 *
 *
 *
 */