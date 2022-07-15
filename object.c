#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L_CHAR 1
#define L_INT 4

#define T_NONE 0
#define T_CHAR 1
#define T_INT 2

typedef struct {
    char type;
    char size;
    void *var;
} Object;

typedef Object C_Char;
typedef Object C_Int;

Object objInit(int size){
    Object object = {(char)T_NONE, (char)size, malloc(size)};
    return object;
}

void objDestroy(Object *object){
    if(object){
        free(object->var);
        object->var = NULL;
    }
}

void objConvert(Object *object, void *var, int size){
    if(object && var){
        if(object->size != size){
            free(object->var);
            object->var = malloc(size);
            object->size = (char)size;
        }
        memcpy(object->var, var, size);
    }
}

void memInt(Object *object, int var){
    objConvert(object, &var, L_INT);
}

int *intVar(const Object object){
    if(object.size == L_INT){
        return (int *)object.var;
    }else{
        return NULL;
    }
}

C_Int Int(int var){
    Object object = objInit(L_INT);
    memInt(&object, var);
    object.type = (char)T_INT;
    return object;
}

void memChar(Object *object, char var){
    objConvert(object, &var, L_CHAR);
}

char *charVar(const Object object){
    if(object.size == L_CHAR){
        return (char *)object.var;
    }else{
        return NULL;
    }
}

C_Char Char(char var){
    Object object = objInit(L_CHAR);
    memChar(&object, var);
    object.type = (char)T_CHAR;
    return object;
}

#define objVar(object) \
    ((object.type) == (T_INT))?(*intVar(object)): \
    ((object.type) == (T_CHAR))?(*charVar(object)): \
    (NULL)\



int main() {
    C_Char cChar = Char('6');
    C_Int cInt = Int(66);

    printf("%c\n", objVar(cChar));
    printf("%d\n",objVar(cInt));

    Object object = cChar;
    printf("%c\n", objVar(object));

    object = cInt;
    printf("%d\n",objVar(object));

    objDestroy(&object);

    return 0;
}
