#include "imc.h"

IMC::IMC()
{
    user_manager = new UserManager();
    backend = new RequestCentre(user_manager);
    frontend = new RequestEntry(backend);
}

IMC::~IMC()
{
    delete frontend;
    delete backend;
    delete user_manager;
}