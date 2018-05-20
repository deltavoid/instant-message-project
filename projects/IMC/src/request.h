#ifndef REQUEST_H
#define REQUEST_H

typedef long long ll;


/*
    add(uid, gid)
    remove(uid, gid)
    put(src_uid, dst_uid, message_id)
    put(src_uid, dst_gid, messate_id)
    get(uid)
*/
#define REQ_ADD         0x01  
#define REQ_REMOVE      0x02
#define REQ_PUT_USER    0x11
#define REQ_PUT_GROUP   0x12
#define REQ_GET         0x21

class Request
{public:
    ll op;
    ll param[3];

    Request(ll op = 0, ll p0 = 0, ll p1 = 0, ll p2 = 0);
    ~Request();
};


#endif
