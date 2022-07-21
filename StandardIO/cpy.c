#include <stdio.h>
#include<stdlib.h>
#define APACITY 4096
int main(){
    FILE * input= fopen("烈火战马(Live)--GAI周延.mp3","rb");
    FILE * output= fopen("cp战马.mp3","wb");
 
    if(input==NULL){
        printf("文件无法打开");
        exit(0);
    }
 
    if(output==NULL){
        printf("文件无法打开");
        exit(0);
    }
 
    int buffer [APACITY];//或int * buffer = malloc(APACITY);
    int validCount = 0;//实际存入多少个数据项
    while((validCount=fread(buffer,sizeof(int),APACITY,input))!=0){
        fwrite(buffer,sizeof(int),validCount,output);
    }
 
    fclose(input);
    fclose(output);
    printf("文件复制完成");
    return 0;
}
