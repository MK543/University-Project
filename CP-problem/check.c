#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    FILE *fp2;
    fp=fopen("./tekst.txt","r");
    fp2=fopen("./hex.txt","r");
    if(fp==NULL)
    {
        perror("Blad otwierania pliku1");
        exit(1);
    }
    if(fp2==NULL)
    {
        perror("Blad otwierania pliku2");
        exit(1);
    }
    int first;
    int second;
    char str2;
    char line[256];
    char c;
    while ((c=fgetc(fp))!=EOF && fgets(line,256, fp2))
    {
        printf("%c = ", c);
        printf("%s", line);
        if(strtol(line, 0, 0) != c){
            printf("Dane nie sa jednakowe!\n");
            return 1;
        }

    }
    printf("Dane sa jednakowe!\n");
    fclose(fp2);
    fclose(fp);
    return 0;
}