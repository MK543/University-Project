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
int notStop = 1;
//1.Funkcja do przesyłania innym sygnału stopu
void sendStopToOthers(int sig){
    printf("%d wysyła sygnał wstrzymania do pozostałych procesów: %d %d %d\n", getpid(), getpid()+1, getpid()+2, getpid()+3);
    kill(getpid()+1, SIGUSR1);
    kill(getpid()+2, SIGUSR1);
    kill(getpid()+3, SIGUSR1);
    signal(sig, SIG_IGN);
}
//2.Funkcja do przesyłania innym sygnału wznowienia
void sendResumeToOthers(int sig){
    printf("%d wysyła sygnał wznowienia do pozostałych procesów: %d %d %d\n", getpid(), getpid()+1, getpid()+2, getpid()+3);
    kill(getpid()+1, SIGUSR2);
    kill(getpid()+2, SIGUSR2);
    kill(getpid()+3, SIGUSR2);
    signal(sig, SIG_IGN);
}
//3.Funkcja do przesyłania innym sygnału zakończenia działania
void sendKillToOthers(int sig){
    printf("%d wysyła sygnał zabicia do pozostałych procesów: %d %d %d\n", getpid(), getpid()+1, getpid()+2, getpid()+3);
    signal(sig, SIG_IGN);
    kill(getpid()+1, SIGPROF);
    kill(getpid()+2, SIGPROF);
    kill(getpid()+3, SIGPROF);
    kill(getpid(), SIGPROF);
}
//4.Funkcja kończąca program
void receiveKill(int sig){
    printf("%d odebrał sygnał zabicia: %d\n",getpid(), sig);
    signal(sig, SIG_IGN);
    int qid;
    key_t msgkey;
    msgkey=ftok(".",'m');
    if((qid = msgget(msgkey, IPC_CREAT | 0660)) == -1){
        perror("Błąd tworzenia kolejki komunikatów\n");
        exit(1);
    }
    printf("Delete!\n");
    //Zamknięcie kolejki komunikatów
    if(msgctl(qid, IPC_RMID, 0) == -1){
        printf("Błąd usuwania kolejki komunikatów");
        exit(1);
    }
    printf("Kolejka zamknięta\n");
    notStop = 0;

}

int main(int args, char* argv[])
{
    //5.Stworzenie kolejki
    umask(0);
    mkfifo(FIFO, 0666);
     printf("Parent PID: %d \n", getpid());
    int p1, p2, p3;
    int true = 1;
    //6.Powołanie procesów potomnych
    if((p1=fork())==0){
        execlp("./p1","./p1", NULL);
    }
    else if((p2=fork())==0){
        execlp("./p2","./p2", NULL);
    }
    else if((p3=fork())==0){
        execlp("./p3","./p3", NULL);
    }
    else{
        //7.Nasłuchiwanie odpowiednicy sygnałów
        printf("Children PID: %d %d %d\n", p1, p2, p3);
        while(notStop){
        signal(SIGINT, sendStopToOthers);
        signal(SIGQUIT, sendResumeToOthers);
        signal(SIGILL, sendKillToOthers);
        signal(SIGPROF, receiveKill);
        }
    }
    printf("Koniec programu\n");
    return 0;
}

