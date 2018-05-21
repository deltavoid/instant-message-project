#ifndef MESSAGE_H
#define MESSAGE_H

typedef long long ll;

class Message
{public:
    Message() {}
    virtual ~Message() {}
    virtual ll get_message() = 0;
};

class UserMessage : public Message
{public:
    ll message_id;

    UserMessage(ll id = 0);
    virtual ~UserMessage();

    ll get_message();
};

/*

class GroupMessage : public Message
{public:
    
    ll get_message();
};*/

#endif