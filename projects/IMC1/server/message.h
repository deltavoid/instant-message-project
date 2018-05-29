#ifndef MESSAGE_H
#define MESSAGE_H

typedef long long ll;

struct Message
{
    ll message_id;
    ll user_id;
    ll group_id;

    Message(ll message_id = 0, ll user_id = 0, ll group_id = 0);
};

#endif