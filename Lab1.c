#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{

    char *nombre1;

    int chunks, hebras;
    int flagI = 1;
    int flagO = 1;
    int flagC = 1;

    int option;
    while ((option = getopt(argc, argv, "i:N:H")) != -1)
    {
        switch (option)
        {
        case 'i':
            nombre1 = optarg;
            printf("%s \n", nombre1);
            flagI = 0;
            break;
        case 'N':
            chunks = atoi(optarg);
            flagO = 0;
            printf("%d \n", chunks);
            break;
        case 'H':
            hebras = atoi(optarg);
            flagC = 0;
            printf("%d \n", hebras);
            break;
        }
    }
    if (flagI == 1 || flagO == 1 || flagC == 1)
    {
        printf("flag incorrectas\n");
    }
    else
    {
        printf("nombre : %s, tamano: %d, hebras %d", nombre1, chunks, hebras);
    }

    return 0;
}
