#include "IMC.h"


IMC::IMC()
{
    um = new UserManager();
    gm = new GroupManager();
    ghm = new GroupHandlerManager(gm);
    chm = new ConnectionHandlerManager(um, gm, ghm);
    ce = new ConnectionEntry(chm);
}

IMC::~IMC()
{
    delete ce;
    delete chm;
    delete ghm;
    delete gm;
    delete um;
}