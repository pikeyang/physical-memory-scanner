#include"init.h"

void banner_init() {

    system("clear");

    char filename[] = "./banner.txt"; //文件名
    FILE *fp; 
    char StrLine[1024];             //每行最大读取的字符数
    if((fp = fopen(filename,"r")) == NULL) //判断文件是否存在及可读
    { 
        printf("error!"); 
        exit(0);
    } 
    printf("\n\n\n\n\n");
    while (!feof(fp)) 
    { 
        fgets(StrLine,1024,fp);  //读取一行
        printf("\t\t\t\t%s", StrLine); //输出
    } 

    fclose(fp);                     //关闭文件


    sleep(3);
    system("clear");
    return ; 
}