#include "message.h"



UserMessage::UserMessage(ll id) : message_id(id)
{
}

UserMessage::~UserMessage()
{
}

ll UserMessage::get_message()
{
    return message_id;
}

