#include "Converter.h"


String Converter::convertoArrayToString(char* array, int size){
    int index = 0;
    String output = "";
    for(index = 0; index < size; index++){
        output+=array[index];
        if(array[index] == '}'){
            break;
        }
    }    
    return output;
}
