#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
*name: InputBuffer_t
*type: struct
*
*/
struct InputBuffer_t {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
};
/*
*
*/
typedef struct InputBuffer_t InputBuffer;
/*
*name: new_input_buffer
*type: InputBuffer*
*
*/
InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    
    return input_buffer;
}
/*
*name: print_prompt()
*type: void
*
*/
void print_prompt() { printf("db > "); }

/*
*name: read_input()
*type: void
*para: InputBuffer* input_buffer
*
*/
void read_input(InputBuffer* input_buffer){
    ssize_t bytes_read = getline(&(input_buffer->buffer), &(input_buffer->buffer_length), stdin);
    if (bytes_read <= 0){
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    // ignore trailing newline
    input_buffer->input_length = bytes_read - 1;
    input_buffer->buffer[bytes_read - 1] = 0;
}
/*
*Main function has an infinite loop that prints the 
*prompt, gets a line of input, then processes that 
*line of input.
*/

int main(int argc, char* argv[]){
    
    InputBuffer* input_buffer = new_input_buffer();
    while(true){
        print_prompt();
        read_input(input_buffer);
        
        if(strcmp(input_buffer->buffer, ".exit")==0){
            exit(EXIT_SUCCESS);
        }
        else{
            printf("Unrecognized command '%s' .\n", input_buffer->buffer);
        }
    }
    return 0;   
}