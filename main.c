#include <stdio.h>
#include <stdbool.h>

/**
 * E -> E + T | T
 * G
 * E -> T G | T
 * G -> + T | + T G
 *
 * T -> T * F | F
 * U
 * T -> F U | F
 * U -> * F | * F U
 *
 * F -> ( E ) | i
 *
 *
 *
 * E -> TG | T
 * G -> +T | +TG
 * T -> FU | F
 * U -> *F | *FU
 * F -> (E) | i
 *
 */

size_t cursor;
const char* str;

bool E();
bool G();
bool T();
bool U();
bool F();

// E -> TG | T
bool E(){
    if(!T()){
        return false;
    }
    size_t copy_cursor = cursor;
    if(!G()){
        cursor = copy_cursor;
    }
    return true;
}

// G -> +T | +TG
bool G(){
    if(str[cursor] != '+'){
        return false;
    }
    cursor++;
    if(!T()){
        return false;
    }
    size_t copy_cursor = cursor;
    if(!G()){
        cursor = copy_cursor;
    }
    return true;
}

// T -> FU | F
bool T(){
    if(!F()){
        return false;
    }
    size_t copy_cursor = cursor;
    if(!U()){
        cursor = copy_cursor;
    }

    return true;
}

// U -> *F | *FU
bool U(){
    if(str[cursor] != '*'){
        return false;
    }
    cursor++;
    if(!F()){
        return false;
    }
    if(str[cursor] == 0){
        return true;
    }
    size_t copy_cursor = cursor;
    if(!U()){
        cursor = copy_cursor;
    }
    return true;
}


// F -> (E) | i
bool F(){
    if(str[cursor] == 'i'){
        cursor++;
        return true;
    }
    if(str[cursor] != '('){
        return false;
    }
    cursor++;
    if(!E()){
        return false;
    }
    if(str[cursor] != ')'){
        return false;
    }
    cursor++;
    return true;
}

bool validate(const char* _str){
    str = _str;
    return E() && str[cursor] == 0;
}

int main(int argc, const char* argv[]) {
    if(argc < 2){
        printf("No se incluyo un parametro de cadena a comprobar");
        return -1;
    }
    printf(validate(argv[1]) ? "La cadena cumple con la gramatica\n" : "La cadena no cumple con la gramatica\n");
    return 0;
}
