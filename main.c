#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Char {
    char value ;
    struct Char *nextPtr ;
} ;
typedef struct Char* ptrChar ;


struct Int {
    int value ;
    struct Int *nextPtr ;
} ;
typedef struct Int* ptrInt ;


void addStackI(ptrInt *, int) ; int delStackI(ptrInt *) ; void printStackI(ptrInt) ;          //int stack functions
void addStackC(ptrChar *, char) ; char delStackC(ptrChar *) ; void printStackC(ptrChar) ;   //char stack functions
void process(char *input, ptrChar *cRoot, ptrInt *iRoot) ;                                      //operation function



int main()
{
    ptrInt iRoot = NULL ;
    ptrChar cRoot = NULL ;
    
    puts("Please enter a mathematical operation : ") ;
    char commands[100] ; fgets(commands, 100, stdin) ;
    
    char *token = strtok(commands, " ") ;                                                                   //Divide sentence to parts
    while(token != NULL) {
        process(token, &cRoot, &iRoot) ;                                                                //Operation on tokenized parts
        token = strtok(NULL, " ") ;
    }
    
    printf("Your Result is -> ") ;  printStackI(iRoot) ;                                                              //Show result
}
// ( 1 + ( ( 3 * 6 ) * ( 2 * 5 ) ) )



















void process(char *input, ptrChar *cRoot, ptrInt *iRoot)                                           //Gets tokens to perform process
{
    if ( input[0] == '(' ) ;
    else if ( input[0] == '+' ) addStackC(cRoot, '+') ;
    else if ( input[0] == '-' ) addStackC(cRoot, '-') ;
    else if ( input[0] == '*' ) addStackC(cRoot, '*') ;
    else if ( input[0] == '/' ) addStackC(cRoot, '/') ;
    else if ( input[0] == ')' ) {
        int iValue = delStackI(iRoot) ;
        char cValue = delStackC(cRoot) ;
        
        if(cValue == '+') iValue += delStackI(iRoot) ;
        else if(cValue == '-') iValue -= delStackI(iRoot) ;
        else if(cValue == '*') iValue *= delStackI(iRoot) ;
        else if(cValue == '/') iValue /= delStackI(iRoot) ;
        
        addStackI(iRoot, iValue) ;
    } else
        addStackI(iRoot, atoi(input)) ; //atoi(const char*) converts string to int
}















//----------------   Stack definitions -------------------------------
void addStackI(ptrInt *rootPtr, int value)
{
    ptrInt newPtr = malloc( sizeof(ptrInt) ) ;
    
    if(newPtr != NULL) {
        newPtr->value = value ;
        newPtr->nextPtr = *rootPtr ;
        
        *rootPtr = newPtr ;
    } else
        puts("Memory is not available.") ;
}


int delStackI(ptrInt *rootPtr)                                        //When you delete int from stack, it means you are using it
{
    if( *rootPtr == NULL ) {
        puts("Stack is already empty.") ; return 0 ;
    } else {
        ptrInt temp = *rootPtr ; int value = temp->value ;                                      //Create int to return deleted value
        *rootPtr = (*rootPtr)->nextPtr ;
        
        free(temp) ; return value ;
    }
}


void printStackI(ptrInt currentPtr)
{
    while(currentPtr != NULL) {
        printf(" %d ", currentPtr->value) ;
        currentPtr = currentPtr->nextPtr ;
    }
    
    puts("") ;
}





void addStackC(ptrChar *rootPtr, char value)
{
    ptrChar newPtr = malloc( sizeof(ptrChar) ) ;
    
    if(newPtr != NULL) {
        newPtr->value = value ;
        newPtr->nextPtr = *rootPtr ;
        
        *rootPtr = newPtr ;
    } else
        puts("Memory is not available.") ;
}



char delStackC(ptrChar *rootPtr)                                     //When you delete char from stack, it means you are using it
{
    if( *rootPtr == NULL ) {
        puts("Stack is already empty.") ; return '\0' ;
    } else {
        ptrChar temp = *rootPtr ; char value = temp->value ;                                   //Create char to return deleted value
        *rootPtr = (*rootPtr)->nextPtr ;
        
        free(temp) ; return value ;
    }
}



void printStackC(ptrChar currentPtr)
{
    while(currentPtr != NULL) {
        printf(" %c ->", currentPtr->value) ;
        currentPtr = currentPtr->nextPtr ;
    }
    
    puts(" NULL\n") ;
}
