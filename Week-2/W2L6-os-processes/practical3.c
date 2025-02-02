#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]){
    if(argc != 2){
        fprintf(stderr, "Must input only 2 parameters");
        return 2;
    }

    char* fixed_str = "hello";

    if(strcmp(argv[1], fixed_str )){
        return 0;
    }else{
        return 1;
    }
}
