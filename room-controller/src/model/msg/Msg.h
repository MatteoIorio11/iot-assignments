#ifndef __MSG__
#define __MSG__

#include <Arduino.h>
class Msg {
    private:
        String content;
    public:
        Msg(const String& content);
        String getContent();
};

#endif