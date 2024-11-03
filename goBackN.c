/*Develop a simple data link layer that performs the flow control using the Go Back N protocol in   “c”

Sample Output:-

Starting Go-Back-N Protocol Simulation...

Sender: Sending Frame 0
Receiver: Frame 0 received
Sender: Sending Frame 1
Receiver: Frame 1 lost (simulated)
Sender: Sending Frame 2
Receiver: Frame 2 received
Sender: Sending Frame 3
Receiver: Frame 3 received
Sender: Acknowledgment received for Frame 0
Sender: No new acknowledgment, resending frames from 1
Sender: Sending Frame 1
Receiver: Frame 1 received
Sender: Acknowledgment received for Frame 3
...
Simulation complete.


*/
#include <stdio.h>
#include <stdbool.h> // for using bool datatype
#include <stdlib.h> // for srand()
#include <unistd.h> // for usleep(time in microseconds) => Suspends the program till that time
#include <time.h> // for time(time_t *t) , it returns the current calender time , by passing 0 or NULL returns current time as Integer

#define WINDOW_SIZE 4      
#define TOTAL_FRAMES 10    

// declare the sender and receiver functions 
void sender();
void receiver(int frame);

int next_frame_to_send = 0;    
int ack_received = -1;         
bool frame_acknowledged[TOTAL_FRAMES] = { false}; 

int main(){
    
    srand(time(0));  
    printf("Starting Go-Back-N Protocol Simulation...\n\n");
    sender();
    printf("\nSimulation complete.\n");
    return 0;

}
void sender(){
    while (ack_received < TOTAL_FRAMES - 1){
        int frames_in_window = 0;
        for (int i = next_frame_to_send; i < next_frame_to_send + WINDOW_SIZE && i < TOTAL_FRAMES; i++){
            if (!frame_acknowledged[i]){
                printf("Sender: Sending Frame %d\n", i);
                receiver(i);
                frames_in_window++;
            }
        }
        int ack = next_frame_to_send + (rand() % frames_in_window);
        printf("Sender: Acknowledgment received for Frame %d\n", ack);
        if (ack > ack_received){
            for (int j = ack_received + 1; j <= ack; j++){
                frame_acknowledged[j] = true;
            }
            ack_received = ack;
            next_frame_to_send = ack + 1;
        }
        else{
            printf("Sender: No new acknowledgment, resending frames from %d\n", next_frame_to_send);
        }
        usleep(500000); 
    }
}
void receiver(int frame){
    int rand_failure = rand() % 5;  
    if (rand_failure == 0){
        printf("Receiver: Frame %d lost (simulated)\n", frame);
    }
    else{
        printf("Receiver: Frame %d received\n", frame);
    }
}