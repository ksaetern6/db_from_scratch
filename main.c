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
*name: MetaCommandResult_t
*type: enumerator 
*desc:
*/
enum MetaCommandResult_t{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
};
typedef enum MetaCommandResult_t MetaCommandResult;
/*
*name: PreparedResult_t
*type: enumerator 
*desc:
*/
enum PreparedResult_t {
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENT
};
typedef enum PreparedResult_t PreparedResult
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
        /*
        *
        * PART 1 CODE HERE
        if(strcmp(input_buffer->buffer, ".exit")==0){
            exit(EXIT_SUCCESS);
        }
        else{
            printf("Unrecognized command '%s' .\n", input_buffer->buffer);
        }
        * END PART ONE CODE
        */ 
        /*
        *
        * SQLite meta commands that start with dot operator '.'
        */
        if (input_buffer->buffer[0]) == '.'{
            switch (do_meta_command(input_buffer)){
                case (META_COMMAND_SUCCESS):
                    continue;
                case (META_COMMAND_UNRECOGNIZED_COMMAND):
                    printf("Unrecognized command '%s'\n", input_buffer->buffer);
                    continue;
            }//end switch
        }//end if
        Statement statement;
        /*
        * SQLite "frontend"
        * line of input into our internal representation of a statement.
        */
        switch (prepare_statement(input_buffer, &statement)){
            case (PREPARE_SUCCESS):
                break;
            case (PREPARE_UNRECOGNIZED_STATEMENT):
                printf("Unrecognized keyword at start '%s'.\n", input_buffer->buffer);
                continue;
        }//end switch
        //execute_command() is our virtual machine.
        execute_statement(&statement);
        printf("Executed.\n");
    }//end while loop
    return 0;   
}