#include "IMC.h"


IMC::IMC()
{
    um = new UserManager();
    gm = new GroupManager();
    chm = new ConnectionHandlerManager(um, gm);
    ce = new ConnectionEntry(chm);
}

IMC::~IMC()
{
    delete ce;
    delete chm;
    delete gm;
    delete um;
}