#define NLED 4
class User{

    private : 
        bool positions[NLED];
    
    public : 
        void addPos(int selected_pos){
            if(selected_pos < NLED && selected_pos > 0){
                positions[selected_pos]=true;
            }
        }

};