#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO "my_fifo"
int waitFor = 1;
int running = 1;
int fifo;

//1.Funkcja do przesyłania innym sygnału stopu
void sendStopToOthers(int sig){
    printf("%d wysyła sygnał wstrzymania do pozostałych procesów: %d %d\n", getpid(), getpid()-1, getpid()+1);
    kill(getpid()-1, SIGUSR1);
    kill(getpid()+1, SIGUSR1);
    signal(sig, SIG_IGN);
    kill(getpid(), SIGUSR1);
}
//2.Funkcja wykonująca wstrzymanie przesyłania danych
void receiveStop(int sig){
    printf("%d odebrał sygnał wstrzymania: %d\n",getpid(), sig);
    signal(sig, SIG_IGN);
    waitFor = 0;
}
//3.Funkcja do przesyłania innym sygnału wznowienia
void sendResumeToOthers(int sig){
    printf("%d wysyła sygnał wznowienia do pozostałych procesów: %d %d\n", getpid(), getpid()-1, getpid()+1);
    kill(getpid()-1, SIGUSR2);
    kill(getpid()+1, SIGUSR2);
    signal(sig, SIG_IGN);
    kill(getpid(), SIGUSR2);
}
//4.Funkcja wykonująca wznowienie przesyłania danych
void receiveResume(int sig){
    printf("%d odebrał sygnał wznowienia: %d\n",getpid(), sig);
    signal(sig, SIG_IGN);
    waitFor = 1;
}
//5.Funkcja do przesyłania innym sygnału zakończenia działania
void sendKillToOthers(int sig){
    printf("%d wysyła sygnał zabicia do pozostałych procesów: %d %d\n", getpid(), getpid()-1, getpid()+1);
    kill(getpid()-1, SIGPROF);
    kill(getpid()+1, SIGPROF);
    kill(getpid()-2, SIGPROF);
    kill(getpid(), SIGPROF);
}
//6.Funkcja kończąca program
void receiveKill(int sig){
    printf("%d odebrał sygnał zabicia: %d\n",getpid(), sig);
    signal(sig, SIG_IGN);
    running = 0;
    //kill(getpid(), SIGKILL);
    printf("Kolejka zamknięta\n");
}
//7. Struktura służąca do wymiany wysyłania i odbierania informacji
//w kolejce komunikatów
static struct sembuf buf;

struct mymsgbuf
{
    long mtype;
    char i[1];
}queue;

struct mymsgbuf readbuffer;

int main()
{
    printf("P2 running!\n");
    sleep(3);
    FILE *fp2;
    int s=0;
    int qid;
    char c;
    int wybor2;
    key_t msgkey;
    msgkey=ftok(".",'m');

    char in[5];
    umask(0);
    //8. Otwarcie kolejki komunikatów
    fifo = open(FIFO, O_WRONLY);

    fp2=fopen("hex.txt","w+");
    if(fp2==NULL)
    {
        perror("Blad otwierania pliku2");
        exit(1);
    }
    if((qid=msgget(msgkey,IPC_CREAT|0660))==-1)
    {
        perror("Blad otwierania kolejki komunikatow");
        exit(1);
    }
    readbuffer.mtype=1;

    printf("Potwierdz swoj wybor: ");
    scanf("%d",&(wybor2));
    switch(wybor2)
    {
        case 1:
        //9. Czytanie z klawiatury do momentu sygnału zakończenia lub znaku spacji.
            msgrcv(qid,&readbuffer,sizeof(struct mymsgbuf)-sizeof(long),readbuffer.mtype,0);
            sprintf(in, "0x%x\n", *readbuffer.i);
            write(fifo, in, 5);
            while((*readbuffer.i)!=' ' && running)
            {
                //10. Jeśli zmienna waitFor zostanie zmieniona w wyniku sygnału wstrzymania proces nie będzie czytał z kolejki
                if(waitFor){
                printf("Proces %d - odebralem wartosc: %c      hex: 0x%x\n",getpid(),*readbuffer.i,*readbuffer.i);
                fprintf(fp2,"0x%x\n",*readbuffer.i);
                msgrcv(qid,&readbuffer,sizeof(struct mymsgbuf)-sizeof(long),readbuffer.mtype,0);

                sprintf(in, "0x%x\n", *readbuffer.i);
                write(fifo, in, 5);

                s++;
                }

                signal(SIGINT, sendStopToOthers);
                signal(SIGUSR1, receiveStop);
                signal(SIGQUIT, sendResumeToOthers);
                signal(SIGUSR2, receiveResume);
                signal(SIGILL, sendKillToOthers);
                signal(SIGPROF, receiveKill);
            }
            break;
        case 2:
            while(msgrcv(qid,&readbuffer,sizeof(struct mymsgbuf)-sizeof(long),readbuffer.mtype,IPC_NOWAIT)!=-1)
            {
                if(waitFor){
                printf("Proces %d - odebralem wartosc: %c      hex: 0x%x\n",getpid(),*readbuffer.i,*readbuffer.i);
                fprintf(fp2,"0x%x\n",*readbuffer.i);

                
                sprintf(in, "0x%x\n", *readbuffer.i);
                write(fifo, in, 5);

                s++;
                }
                //11. Obsługa odbieranych sygnałów
                signal(SIGINT, sendStopToOthers);
                signal(SIGUSR1, receiveStop);
                signal(SIGQUIT, sendResumeToOthers);
                signal(SIGUSR2, receiveResume);
                signal(SIGILL, sendKillToOthers);
                signal(SIGPROF, receiveKill);
            }
            break;
        default:
            printf("Bledny wybor!\n");
            return 0;
    }


    rewind(fp2);

    sleep(1);
    printf("Pobrano %d znakow.\n",s);
    fclose(fp2);
    kill(getpid()-2, SIGILL);
    return 0;
}

