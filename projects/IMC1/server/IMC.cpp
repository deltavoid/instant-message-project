#include "IMC.h"


IMC::IMC()
{
    chm = new ConnectionHandlerManager();
    ce = new ConnectionEntry(chm);
}

IMC::~IMC()
{
    delete ce;
    delete chm;
}