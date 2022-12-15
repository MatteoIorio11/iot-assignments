#include "Converter.h"

char* Converter::ConvertStringToArray(String input){
    // Length (with one extra character for the null terminator)
    int str_len = input.length() + 1; 

    // Prepare the character array (the buffer) 
    char output[str_len];
    // Copy it over 
    input.toCharArray(output, str_len);
    return output;
}