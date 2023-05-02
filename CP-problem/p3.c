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
    printf("%d wysyła sygnał wstrzymania do pozostałych procesów: %d %d\n", getpid(), getpid()-1, getpid()-2);
    kill(getpid()-1, SIGUSR1);
    kill(getpid()-2, SIGUSR1);
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
    printf("%d wysyła sygnał wznowienia do pozostałych procesów: %d %d\n", getpid(), getpid()-1, getpid()-2);
    kill(getpid()-1, SIGUSR2);
    kill(getpid()-2, SIGUSR2);
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
    printf("%d wysyła sygnał zabicia do pozostałych procesów: %d %d\n", getpid(), getpid()-1, getpid()-2);
    kill(getpid()-1, SIGPROF);
    kill(getpid()-2, SIGPROF);
    kill(getpid()-3, SIGPROF);
    kill(getpid(), SIGPROF);
}
//6.Funkcja kończąca program
void receiveKill(int sig){
    printf("%d odebrał sygnał zabicia: %d\n",getpid(), sig);
    signal(sig, SIG_IGN);
    running = 0;
    close(fifo);
    kill(getpid(), SIGKILL);
}

int main()
{
    printf("P3 running!\n");
    sleep(2);
    umask(0);
    mkfifo(FIFO, 0666);
    char out[5];
    //7. Otwarcie kolejki fifo
    fifo = open(FIFO, O_RDONLY);
    if(read(fifo, out, 5)>0 && *out != '\n'){
                printf("Proces %d - odebralem wartosc: %s\n",getpid(), out);
    }
    //8. Zmienna running odpowiedzialna za działanie programu i zmienna waitFor odpowiadająca za czytanie z kolejki fifo
    while(running){
        if(waitFor){
            if(read(fifo, out, 5)>0 && *out != '\n'){
                printf("Proces %d - odebralem wartosc: %s\n",getpid(), out);
            }
        }
        //9. Odbieranie sygnałów i przekazywanie ich do określonych funkcji
        signal(SIGINT, sendStopToOthers);
        signal(SIGUSR1, receiveStop);
        signal(SIGQUIT, sendResumeToOthers);
        signal(SIGUSR2, receiveResume);
        signal(SIGILL, sendKillToOthers);
        signal(SIGPROF, receiveKill);
    }
    return 0;
}
