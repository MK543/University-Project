#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
int running = 1;
int killFor = 0;
//1.Funkcja do przesyłania innym sygnału stopu 
void sendStopToOthers(int sig){
    printf("%d wysyła sygnał wstrzymania do pozostałych procesów: %d %d\n", getpid(), getpid()+1, getpid()+2);
    kill(getpid()+1, SIGUSR1);
    kill(getpid()+2, SIGUSR1);
    signal(sig, SIG_IGN);
    kill(getpid(), SIGUSR1);
}
//2.Funkcja wykonująca wstrzymanie przesyłania danych
void receiveStop(int sig){
    printf("%d odebrał sygnał wstrzymania: %d\n",getpid(), sig);
    signal(sig, SIG_IGN);
}
//3.Funkcja do przesyłania innym sygnału wznowienia
void sendResumeToOthers(int sig){
    printf("%d wysyła sygnał wznowienia do pozostałych procesów: %d %d\n", getpid(), getpid()+1, getpid()+2);
    kill(getpid()+1, SIGUSR2);
    kill(getpid()+2, SIGUSR2);
    signal(sig, SIG_IGN);
    kill(getpid(), SIGUSR2);
}
//4.Funkcja wykonująca wznowienie przesyłania danych
void receiveResume(int sig){
    printf("%d odebrał sygnał wznowienia: %d\n",getpid(), sig);
    signal(sig, SIG_IGN);
}
//5.Funkcja do przesyłania innym sygnału zakończenia działania
void sendKillToOthers(int sig){
    printf("%d wysyła sygnał zabicia do pozostałych procesów: %d %d\n", getpid(), getpid()+1, getpid()+2);
    kill(getpid()+1, SIGPROF);
    kill(getpid()+2, SIGPROF);
    kill(getpid()-1, SIGPROF);
    kill(getpid(), SIGPROF);
}
//6.Funkcja kończąca program
void receiveKill(int sig){
    printf("%d odebrał sygnał zabicia: %d\n",getpid(), sig);
    signal(sig, SIG_IGN);
    running = 0;
    kill(getpid(), SIGKILL);
}
//7. Struktura służąca do wymiany wysyłania i odbierania informacji
//w kolejce komunikatów
struct mymsgbuf
{
    long mtype;
    char i[1];
}queue;

struct mymsgbuf readbuffer;

int main()
{
    printf("P1 running!\n");
    FILE *fp;
    int wybor;
    int qid;
    key_t msgkey;
    char c;
    //8. Utworzenie kolejki komunikatów
    msgkey=ftok(".",'m');
    if((qid=msgget(msgkey,IPC_CREAT|0660))==-1)
    {
        perror("Blad otwierania kolejki komunikatow");
        exit(1);
    }
    printf("ODBIERANIE DANYCH ZNAKOWYCH\n");
    printf("1. Z klawiatury\n");
    printf("2. Z pliku\n");
    printf("Wybierz opcję: ");
    scanf("%d",&(wybor));
    switch(wybor)
    {
        case 1:
            sleep(6);
            fp=fopen("tekst.txt","w+");
            if(fp==NULL)
            {
                perror("Blad otwierania pliku1");
                exit(1);
            }
            printf("Wpisz znaki z klawiatury: \n");
            scanf("%c",&c);
            //9. Zmienna 'running' odpowiedzialna za działanie wysyłania danych do kolejki do momentu
            //wysłania sygnału zakończenia działania
            while(running&&c!=' ')
            {
                if(c!='\n')
                {

                    fputc(c,fp);
                    queue.i[0]=c;
                    queue.mtype=1;
                    //10. Wysłanie wiadomości za pomocą kolejki
                    if((msgsnd(qid,&queue,sizeof(struct mymsgbuf)-sizeof(long),0))==-1 )
                    {
                        perror("Blad wysylania komunikatu");
                        exit(1);
                    }
                    //11. Obsługa odbieranych sygnałów
                    signal(SIGINT, sendStopToOthers);
                    signal(SIGUSR1, receiveStop);
                    signal(SIGQUIT, sendResumeToOthers);
                    signal(SIGUSR2, receiveResume);
                    signal(SIGILL, sendKillToOthers);
                    signal(SIGPROF, receiveKill);
                }
                scanf("%c",&c);
            }
            queue.i[0]=' ';
            msgsnd(qid,&queue,sizeof(struct mymsgbuf)-sizeof(long),0);
            fclose(fp);
            break;
        case 2:
            //12. Czytanie z pliku
            fp=fopen("tekst.txt","r");
            if(fp==NULL)
            {
                perror("Blad otwierania pliku1");
                exit(1);
            }
            while((queue.i[0]=fgetc(fp))!=EOF)
            {
                queue.mtype=1;
                if((msgsnd(qid,&queue,sizeof(struct mymsgbuf)-sizeof(long),0))==-1)
                {
                    perror("Blad wysylania komunikatu");
                    exit(1);
                }
                //11. Obsługa odbieranych sygnałów
                signal(SIGINT, sendStopToOthers);
                signal(SIGUSR1, receiveStop);
                signal(SIGQUIT, sendResumeToOthers);
                signal(SIGUSR2, receiveResume);
                signal(SIGILL, sendKillToOthers);
                signal(SIGPROF, receiveKill);
            }
            fclose(fp);
            break;
        default:
            printf("Bledny wybor!\n");
            return 0;
    }
}
