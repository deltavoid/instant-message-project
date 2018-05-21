#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "imc.h"

pthread_mutex_t mutex_cout;

IMC* imc;

int main()
{
    pthread_mutex_init(&mutex_cout, NULL);

    imc = new IMC();

    sleep(10000);

    return 0;
}