/*
* cwade12c
* pgmutil - a utility to draw shapes based on an input of values
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "pgmUtility.h"

void usage(void)
{
    printf("Usage: pgm -c circleCenterRow circleCenterCol radius inFile outFile\n");
    printf("       pgm -e edgeWidth inFile outFile\n");
    printf("       pgm -ce circleCenterRow circleCenterCol radius edgeWidth inFile outFile\n");
    printf("       pgm -c -e circleCenterRow circleCenterCol radius edgeWidth inFile outFile\n");
}

int main(int argc, char **argv)
{
    char **header;
    int i, row, col, result;

    if(argc < 2)
    {
        usage();
    }
    else
    {
        /*char **header;
        FILE *fIn = NULL;
        FILE *fOut = NULL;
        int i, row, col, result;*/

        header = (char**) malloc(rowsInHeader * sizeof(char*));

        for(i = 0; i < rowsInHeader; i++)
        {
            header[i] = (char*) malloc(maxSizeHeadRow * sizeof(char));
        }

        char* option = argv[1];

        if( ( (strcmp(option, "-c") == 0) && argc == 7) )
        //if(strcmp(option, "-c") == 0)
        {
            int cr, cc, r;
            cr = atoi(argv[2]);
            cc = atoi(argv[3]);
            r = atoi(argv[4]);

            if(cr == 0 || cc == 0 || r == 0)
            {
                usage();
            }
            else
            {    
                FILE *fIn = NULL;
                fIn = fopen(argv[5], "r");

                if(fIn == NULL)
                {
                    //printf("\nUnable to open input file, or file does not exist!\n");
                    usage();
                }
                else
                {
                    int** pgm = pgmRead(header, &row, &col, fIn );
                    fclose(fIn);

                    result = pgmDrawCircle( pgm, row, col, cr, cc, r, header );

                    if(result == 1)
                    {
                        FILE* fOut = NULL;                            
                        fOut = fopen(argv[6], "w");


                        pgmWrite((const char**) header, (const int**) pgm, row, col, fOut);
                        fclose(fOut);

                        for(i = 0; i < row; i++)
                        {
                            free(pgm[i]);
                        }
                        free(pgm);
                        pgm = NULL;
                    }
                    else
                    {
                        printf("Invalid input file or unable to open!\n");
                    }
                }
            }
        }

        else if( ( (strcmp(option, "-e") == 0) && argc == 5) )
        {
            int e;
            e = atoi(argv[2]);

            if(e == 0)
            {
                usage();
            }
            else
            {   
                FILE* fIn = NULL; 
                fIn = fopen(argv[3], "r");

                if(fIn == NULL)
                {
                    //printf("\nUnable to open input file, or file does not exist!\n");
                    usage();
                }
                else
                {
                    int** pgm = pgmRead(header, &row, &col, fIn );
                    fclose(fIn);

                    result = pgmDrawEdge( pgm, row, col, e, header );

                    if(result == 1)
                    {
                        FILE* fOut = NULL;
                        fOut = fopen(argv[4], "w");

                        pgmWrite((const char**) header, (const int**) pgm, row, col, fOut);
                        fclose(fOut);

                        for(i = 0; i < row; i++)
                        {
                            free(pgm[i]);
                        }
                        free(pgm);
                    }
                    else
                    {
                        for(i = 0; i < row; i++)
                        {
                            free(pgm[i]);
                        }
                        free(pgm);
                        pgm = NULL;

                        printf("Unable to write output file!\n");
                    }
                }
            }
        }

        else if( ( (strcmp(option, "-ce") == 0) && argc == 8) )
        {
            int cr, cc, r, e;
            cr = atoi(argv[2]);
            cc = atoi(argv[3]);
            r = atoi(argv[4]);
            e = atoi(argv[5]);

            if(cr == 0 || cc == 0 || r == 0 || e == 0)
            {
                usage();
            }    
            else
            {
                FILE* fIn = NULL;
                fIn = fopen(argv[6], "r");

                if(fIn == NULL)
                {
                    //printf("\nUnable to open input file, or file does not exist!\n");
                    usage();
                }
                else
                {
                    int** pgm = pgmRead(header, &row, &col, fIn );
                    fclose(fIn);

                    result = pgmDrawCircle( pgm, row, col, cr, cc, r, header );

                    if(result == 1)
                    {
                        result = pgmDrawEdge(pgm, row, col, e, header);

                        if(result == 1)
                        {
                            FILE* fOut = NULL;
                            fOut = fopen(argv[7], "w");

                            pgmWrite((const char**) header, (const int**) pgm, row, col, fOut);
                            fclose(fOut);

                            for(i = 0; i < row; i++)
                            {
                                free(pgm[i]);
                            }
                            free(pgm);
                            pgm = NULL;
                        }
                    }
                    else
                    {
                        for(i = 0; i < row; i++)
                        {
                            free(pgm[i]);
                        }
                        free(pgm);
                        pgm = NULL;

                        printf("Unable to write output file!\n");                       
                    }
                }
            }                
        }

        else if( ( (strcmp(option, "-c") == 0) && ((strcmp(argv[2], "-e") == 0) && argc == 9) ) )
        {
            int cr, cc, r, e;
            cr = atoi(argv[3]);
            cc = atoi(argv[4]);
            r = atoi(argv[5]);
            e = atoi(argv[6]);

            if(cr == 0 || cc == 0 || r == 0 || e == 0)
            {
                usage();
            }    
            else
            {
                FILE* fIn = NULL;
                fIn = fopen(argv[7], "r");

                if(fIn == NULL)
                {
                    //printf("\nUnable to open input file, or file does not exist!\n");
                    usage();
                }
                else
                {
                    int** pgm = pgmRead(header, &row, &col, fIn );
                    fclose(fIn);

                    result = pgmDrawCircle( pgm, row, col, cr, cc, r, header );

                    if(result == 1)
                    {
                        result = pgmDrawEdge(pgm, row, col, e, header);

                        if(result == 1)
                        {
                            FILE* fOut = NULL;
                            fOut = fopen(argv[8], "w");

                            pgmWrite((const char**) header, (const int**) pgm, row, col, fOut);
                            fclose(fOut);

                            for(i = 0; i < row; i++)
                            {
                                free(pgm[i]);
                            }
                            free(pgm);
                            pgm = NULL;
                        }
                    }
                    else
                    {
                        for(i = 0; i < row; i++)
                        {
                            free(pgm[i]);
                        }
                        free(pgm);
                        pgm = NULL;
                        free(header);
                        header = NULL;

                        printf("Unable to write output file!\n");                       
                    }
                }
            } 
        }

        else
        {
            usage();
        }

        for(i = 0; i < rowsInHeader; i++)
        {
            free(header[i]);
        }

        free(header);
        header = NULL;

        return 0;
    }

    return -1;
}

int** pgmRead( char** header, int* numRows, int* numCols, FILE* in  )
{
	int i, j, rows, cols;

    for(i = 0; i < rowsInHeader; i++)
    {
        fgets(header[i], maxSizeHeadRow, in);
    }

    sscanf(header[2], "%d %d", numCols, numRows);
    cols = *numCols;
    rows = *numRows;

    int** data;
    data = (int **) malloc(rows * sizeof(int *));

    for(i = 0; i < rows; i++)
    {
        data[i] = (int *)malloc(cols * sizeof(int));
    }

    for(i = 0; i < rows; i++)
    {
        for(j = 0; j < cols; j++)
        {
            fscanf(in, "%d", &data[i][j]);
        }
    }

    return data;
}

int pgmWrite( const char **header, const int **pixels, int numRows, int numCols, FILE *out )
{
   int i, j;

   for(i = 0; i < rowsInHeader; i++)
   {
       fprintf(out, "%s", header[i]);
   }

   for(i = 0; i < numRows; i++)
   {
       for(j = 0; j < numCols; j++)
       {
           fprintf(out, "%d ", pixels[i][j]);
       }
       fprintf(out, "\n");
   }

    return 0;
}

double distance( int p1[], int p2[] )
{
    int x, y;

    x = p1[0] - p2[0];
    y = p1[1] - p2[1];

    //return (double) sqrt(((pow(x,2)) + pow(y,2))); //undefined reference to `sqrt', fix w gcc -lm

    return (double) pow(((pow(x,2)) + pow(y,2)), .5); //undefined reference to `pow`, fix w gcc -lm
}

int pgmDrawCircle( int **pixels, int numRows, int numCols, int centerRow,
                   int centerCol, int radius, char **header )
{
    int i, j;
    double d;

    for(i = 0; i < numRows; i++) //for( i for each row)
    {
        for(j = 0; j < numCols; j++) //for(j for each col)
        {
            int p1[] = {i, j};
            int p2[] = {centerRow, centerCol};

            d = distance(p1, p2); 

            if(d <= radius)
            {
                pixels[i][j] = 0; //fill it in black
            }
        }
    }

    return 1;
}

int pgmDrawEdge( int **pixels, int numRows, int numCols, int edgeWidth, char **header )
{
   int x, y, north, east, south, west;

   north = edgeWidth;
   west = edgeWidth;
   south = numRows - north;
   east = numCols - west;

    for(x = 0; x < numRows; x++)
    {
        for(y = 0; y < numCols; y++)
        {
            if(x <= north)
            {
                pixels[x][y] = 0;
            }

            if(y >= east)
            {
                pixels[x][y] = 0;
            }

            if(x >= south)
            {
                pixels[x][y] = 0;
            }

            if(y <= west)
            {
                pixels[x][y] = 0;
            }
        }
    }

    return 1;    
}
