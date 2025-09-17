#include "./movieList.h"

void MovieListCreate(MovieList ** movieList)
{
    (*movieList) = malloc(sizeof(MovieList) );
    if ( (*movieList) == NULL )
    {
        perror("malloc");
    }
    (*movieList)->length = 0;
    (*movieList)->head = NULL;
}

void MovieListDestroy(MovieList * movieList)
{
    Movie * movie = NULL;
    while( movieList->length )
    {
        movie = movieList->head;
        movieList->head = movieList->head->next;
        movieList->length--;
        free(movie->name);
        free(movie);
    }
    free(movieList);
}

void MovieListInsert(MovieList * movieList, char *  name, int price, int capacity)
{
    Movie * movie = malloc(sizeof(Movie));
    if ( movie == NULL )
    {
        perror("malloc");
    }
    movie->name = malloc(sizeof(char) * strlen(name) + 1);
    if ( movie->name == NULL )
    {
        perror("malloc");
    }
    strcpy(movie->name,name);
    movie->price = price;
    movie->capacity = capacity;
    movie->next = movieList->head;
    movieList->head = movie;
    movieList->length++;
}

void MovieListDelete( MovieList * movieList, char * name )
{
    int found = 0;
    if ( movieList->length == 0 )
    {
        printf("Sorry, list is empty\n");
    }
    else
    {
        Movie * movie = movieList->head;
        Movie * prevMovie = movieList->head;
        for (int i = 0; i < movieList->length; i++)
        {
            if ( strcmp(movie->name, name) == 0 )
            {
                if ( i == 0 ) {
                    movieList->head = movie->next;
                }
                else {
                    prevMovie->next = movie->next;
                }
                free(movie);
                movieList->length--;
                found = 1;
                break;
            }
            movie = movie->next;
            if ( i == 0 ) continue;
            prevMovie = prevMovie->next;

        }
    }
    if (!found ) {
        printf("Sorry, movie not found.\n");
    }
}

void MovieListPrint( MovieList * movieList, FILE * stream )
{
    if ( movieList->length == 0 )
    {
        fprintf(stdout,"Sorry, no movies available at this time.\n");
    }
    else
    {
        Movie * movie = movieList->head;
        for ( int i = 0; i < movieList->length; i++ )
        {
            fprintf(stream,"%s-%d %d \n", movie->name,movie->price,movie->capacity);
            movie = movie->next;
        }
    }
}

int MovieListBook( MovieList * movieList, char * name, int tickets )
{
    if ( movieList->length == 0 )
    {
        printf("Sorry, list is empty\n");
        return 0;
    }
    Movie * movie = movieList->head;
    for ( int i = 0; i < movieList->length; i++ )
    {
        if ( strcmp(movie->name, name) == 0 )
        {
            if ( movie->capacity < tickets ) {
                return -1;
            }
            movie->capacity -= tickets;
            return tickets * movie->price;
        }
        movie = movie->next;
    }
    return 0;
}
