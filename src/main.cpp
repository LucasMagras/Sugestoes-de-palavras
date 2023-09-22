#include "read.hpp"
#include <time.h>

int main() 
{
    double timespent = 0.0;

    clock_t begin = clock();
    fake_main();
    clock_t end = clock();
    
    timespent += (double)(end - begin) / CLOCKS_PER_SEC;
    cout << endl << "TEMPO DE EXECUÇÃO: "<< timespent << " SEGUNDOS" << endl;

    return 0;
}