#include "request.h"
#include <cstring>


Request::Request(ll op, ll p0, ll p1, ll p2) : op(op)
{
    param[0] = p0;
    param[1] = p1;
    param[2] = p2;
}
