#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "imc.h"

IMC* imc;

int main()
{
    imc = new IMC();

    sleep(10000);

    return 0;
}