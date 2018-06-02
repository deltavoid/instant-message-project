#include "IMC.h"


IMC::IMC()
{
    um = new UserManager();
    gm = new GroupManager();
    ghm = new GroupHandlerManager(gm);
    rhm = new RequestHandlerManager(um, gm, ghm);
    chm = new ConnectionHandlerManager(rhm);
    ce = new ConnectionEntry(chm);
}

IMC::~IMC()
{
    delete ce;
    delete chm;
    delete rhm;
    delete ghm;
    delete gm;
    delete um;
}