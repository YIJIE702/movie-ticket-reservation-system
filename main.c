#include "movieList.h"
#include "ticketList.h"
#define BUFFERSIZE 600
#define DELIM " \n\t"

// Function that saves movie list inside a file
void storeMovies( MovieList * movieList )
{
    FILE * file = fopen("movieList.txt","w");
    MovieListPrint(movieList,file);
    fclose(file);
}

// Function that loads a movie list from a file
void loadMovies( MovieList * movieList  )
{
    FILE * file = fopen("movieList.txt","r");
    if ( file == NULL )
    {
        perror("fopen r");
    }
    char buffer[BUFFERSIZE];
    memset(buffer,0,BUFFERSIZE);
    char * name;
    int price;
    int capacity;
    while( fgets(buffer,BUFFERSIZE,file) != NULL )
    {
        // Ignore all empty lines, spaces and tabs
        if ( *buffer == '\n' || *buffer == ' ' || *buffer == '\t') continue;

        name = strtok(buffer,"-");
        price = atoi( strtok(NULL,DELIM) );
        capacity = atoi( strtok(NULL,DELIM) );
        MovieListInsert(movieList,name,price,capacity);
        memset(buffer,0,BUFFERSIZE);
    }
    fclose(file);
}

int main( int argc, char * argv[] )
{
    enum modes{USER, ADMIN, MODERATOR};
    int mode = USER;
    if ( argc > 1 )
    {
        if ( strcmp(argv[1],"-a") == 0) {
            mode = ADMIN;
        }
        else if ( strcmp(argv[1], "-m") == 0 ) {
            mode = MODERATOR;
        }
    }
    MovieList * movieList;
    MovieListCreate(&movieList);

    // Make sure that file exists
    FILE * file = fopen("movieList.txt","a");
    if ( file == NULL ) {
        perror("fopen a");
    }
    fclose(file);
    loadMovies(movieList);

    char name[BUFFERSIZE], username[BUFFERSIZE];
    char buffer[BUFFERSIZE];
    int price = 0 , capacity = 0;
    int loop = 1;
    TicketList * ticketList;

    switch(mode) {
        // Main switch depended on program mode
        case USER:
            TicketListCreate(&ticketList);
            printf("What is your username?\n");
            fgets(username,BUFFERSIZE,stdin);
            strtok(username,"\n");
            TicketListInput(ticketList,username);
            while(loop)
            {
                printf("\nAll movie will start at 10am!\n");
                printf("There is no any promotion for this season!!!\n");
                printf("--------------------------------\n");
                printf("1. View Movies Schedule\n");
                printf("2. Book ticket(s)\n");
                printf("3. Cancel Booking(s)\n");
                printf("4. View ticket list\n");
                printf("5. Exit\n");
                printf("--------------------------------\n");

                int answer = 0;
                fgets(buffer,BUFFERSIZE,stdin);
                answer = atoi(buffer);

                switch ( answer ) {
                    case 1: // view movie list
                        MovieListPrint(movieList,stdout);
                        break;

                    case 2: // book movie
                        printf("Please enter the movie name you would like to book:\n");
                        fgets(name,BUFFERSIZE,stdin);
                        strtok(name,"\n");
                        printf("How many tickets would you like to book?\n");

                        int notValid = 1;
                        while ( notValid ) {
                            scanf(" %d", &capacity);
                            getchar();
                            notValid=0;
                            if ( capacity <= 0 ) {
                                printf("invalid input, try again.\n");
                                notValid=1;
                            }
                        }
                        printf("Trying to book %s...\n", name);
                        int ret = MovieListBook(movieList,name,capacity);
                        if ( ret == -1 ) {
                            printf("Not enough seats available!\n");
                        } else if ( ret == 0 ) {
                            printf("Sorry, no such movie!\n");
                        }else {
                            printf("The price is : $%d\n", ret );
                            printf("Are you going to to pay online(0) or at cinema(1)?\n");
                            fgets(buffer,BUFFERSIZE,stdin);
                            int pending = atoi(buffer);
                            TicketListInsert(ticketList,name,capacity,pending);
                        }
                        break;

                    case 3: // cancel booking movie
                        printf("Please enter the movie name you would like to cancel booking:\n");
                        fgets(name,BUFFERSIZE,stdin);
                        strtok(name,"\n");
                        printf("Trying to cancel booking %s...\n", name);

                        if ( ret == 0 ) {
                            printf("Sorry, list is empty\n");
                            printf("Sorry, movie not found.\n");
                        }else {
                            printf("The price refunded is : $%d\n", ret);
                            TicketListDelete(ticketList,name);
                        }
                        break;

                    case 4: // print ticket ticket
                        TicketListPrint(ticketList);
                        break;

                    case 5:// exit application
                        printf("Exiting application...\n");
                        TicketListOutput(ticketList,username);
                        TicketListDestroy(ticketList);
                        loop = 0;
                        break;

                    default:
                        printf("Unknown command\n");
                }
            }
            break; // end of admin
            break;

        case MODERATOR:
            while(loop) {
                printf("--------------------------------\n");
                printf("1. View Movies\n");
                printf("2  View user tickets\n");
                printf("3. Delete user ticket\n");
                printf("4. Exit\n");
                printf("--------------------------------\n");
                int answer = 0;
                fgets(buffer,BUFFERSIZE,stdin);
                answer = atoi(buffer);

                switch ( answer ) {
                    case 1: // view movie list
                        MovieListPrint(movieList,stdout);
                        break;
                    case 2: // user tickets
                        TicketListCreate(&ticketList);
                        printf("What is the username?\n");
                        fgets(username,BUFFERSIZE,stdin);
                        strtok(username,"\n");
                        TicketListInput(ticketList,username);
                        TicketListPrint(ticketList);
                        TicketListDestroy(ticketList);
                        break;
                    case 3: // delete ticket
                        TicketListCreate(&ticketList);
                        printf("What is the username?\n");
                        fgets(username,BUFFERSIZE,stdin);
                        strtok(username,"\n");
                        TicketListInput(ticketList,username);

                        printf("What is the movie name?\n");
                        memset(name,0,BUFFERSIZE);
                        fgets(name,BUFFERSIZE,stdin);
                        strtok(name,"\n");

                        TicketListDelete(ticketList,name);
                        printf("Deletion complete!\n");
                        TicketListOutput(ticketList,username);
                        TicketListDestroy(ticketList);
                        break;
                    case 4:
                        printf("Exiting application...\n");
                        loop = 0;
                        break;
                    default:
                        printf("Unknown command\n");
                }
            }
            break;

        case ADMIN:
            while(loop) {
                printf("--------------------------------\n");
                printf("1. Create new movie\n");
                printf("2. Delete an existing movie\n");
                printf("3. View movies\n");
                printf("4. Exit\n");
                printf("--------------------------------\n");

                int answer = 0;
                fgets(buffer,BUFFERSIZE,stdin);
                answer = atoi(buffer);
                switch ( answer ) {
                    case 1: // new movie
                        printf("Please enter movie name\n");
                        memset(name,0,BUFFERSIZE);
                        fgets(name,BUFFERSIZE,stdin);
                        strtok(name,"\n");
                        printf("What is the ticket price?\n");
                        scanf(" %d", &price);
                        printf("What is the capacity of the movie theater?\n");
                        scanf(" %d",&capacity);
                        MovieListInsert(movieList,name,price,capacity);
                        break;
                    case 2: // delete movie
                        printf("Please enter the movie name you would like to delete\n");
                        fgets(name,BUFFERSIZE,stdin);
                        strtok(name,"\n");
                        printf("Trying to delete %s...\n", name);
                        MovieListDelete(movieList,name);
                        break;
                    case 3: // view movie
                        MovieListPrint(movieList,stdout);
                        break;
                    case 4:
                        printf("Exiting application...\n");
                        loop = 0;
                        break;
                    default:
                        printf("Unknown command\n");
                }
            }
            break; // end of admin
    }
    storeMovies(movieList);
    MovieListDestroy(movieList);
}

