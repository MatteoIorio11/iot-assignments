#ifndef BOT_H
#define BOT_H
#define NLEDS 4

using namespace std;

class Bot{
    private:
        bool leds[NLEDS] = {false};
    public:
        void generateSequence();
        bool* getLeds();
        bool validate(int position, bool val);
        bool validate(bool* input_array);
        void allLedsOff();
};
#endif