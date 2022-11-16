#ifndef __JSONSERIALIZER__
#define __JSONSERIALIZER__

class JsonSerializer{
    public:
        void serializePreAlarm(double waterLevel);
        void serializeAlarm(double waterLevel, int angle);
};

#endif