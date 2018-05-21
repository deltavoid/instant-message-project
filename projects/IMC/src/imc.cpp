#include "imc.h"

IMC::IMC()
{
    user_manager = new UserManager();
    group_manager = new GroupManager();
    backend = new RequestCentre(user_manager, group_manager);
    frontend = new RequestEntry(backend);
}

IMC::~IMC()
{
    delete frontend;
    delete backend;
    delete group_manager;
    delete user_manager;
}