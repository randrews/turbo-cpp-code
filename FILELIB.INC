#include <fstream.h>
#include <string.h>
#include <assert.h>


ofstream fileout;
ifstream filein;

void open(char *filename);
void close();

void open(char *filename)
{
strcat(filename,".dat");
fileout.open(filename);
filein.open(filename);
}

void close()
{
fileout.close();
filein.close();
}