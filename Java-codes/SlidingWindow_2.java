/*
2) Develop a simple data link layer that performs the flow control using the sliding window protocol, and loss recovery using the Go-Back-N mechanism.

 */
import java.util.Random;

class SlidingWindow_2 {

    private static final int WINDOW_SIZE = 4;
    private static final int TOTAL_FRAMES = 10;

    private static int nextFrameToReceive = 0;
    private static int nextFrameToSend = 0;
    private static int ackReceived = -1; 
    private static boolean[] frameAcknowledged = new boolean[TOTAL_FRAMES];

    public static void main(String[] args) {
        System.out.println("[Sender] Starting Sliding Window Protocol with Go-Back-N.");
        sender();
        System.out.println("[Sender] Transmission completed.");
    }

    public static void sender() {
        while (ackReceived < TOTAL_FRAMES - 1) {

            // Send frames within the window
            for (int i = nextFrameToSend; i < nextFrameToSend + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
                if (!frameAcknowledged[i]) {
                    System.out.println("[Sender] Sending Frame " + i);
                    receiver(i);
                }
            }

            // Simulate acknowledgment from receiver
            int ack = nextFrameToReceive - 1;
            System.out.println("[Sender] ACK for Frame " + ack + " received successfully.");

            if (ack > ackReceived) {
                for (int j = ackReceived + 1; j <= ack; j++) {
                    frameAcknowledged[j] = true;
                }
                ackReceived = ack;
                nextFrameToSend = ack + 1;
            } else {
                System.out.println("[Sender] No new acknowledgment, resending frames from " + nextFrameToSend);
            }
        }
    }

    public static void receiver(int frame) {
        Random random = new Random();
        int randFailure = random.nextInt(5); // Random failure simulation (20% chance of failure)

        if (randFailure == 0) {
            System.out.println("[Receiver] Frame " + frame + " lost during transmission.");
        } else if (frame == nextFrameToReceive) {
            System.out.println("[Receiver] Frame " + frame + " received.");
            nextFrameToReceive++;
        } else {
            System.out.println("[Receiver] Frame " + frame + " discarded.");
        }
    }
}

/*
Output:-

[Sender] Starting Sliding Window Protocol with Go-Back-N.
[Sender] Sending Frame 0
[Receiver] Frame 0 lost during transmission.
[Sender] Sending Frame 1
[Receiver] Frame 1 discarded.
[Sender] Sending Frame 2
[Receiver] Frame 2 lost during transmission.
[Sender] Sending Frame 3
[Receiver] Frame 3 discarded.
[Sender] ACK for Frame -1 received successfully.
[Sender] No new acknowledgment, resending frames from 0
[Sender] Sending Frame 0
[Receiver] Frame 0 received.
[Sender] Sending Frame 1
[Receiver] Frame 1 lost during transmission.
[Sender] Sending Frame 2
[Receiver] Frame 2 discarded.
[Sender] Sending Frame 3
[Receiver] Frame 3 discarded.
[Sender] ACK for Frame 0 received successfully.
[Sender] Sending Frame 1
[Receiver] Frame 1 received.
[Sender] Sending Frame 2
[Receiver] Frame 2 received.
[Sender] Sending Frame 3
[Receiver] Frame 3 received.
[Sender] Sending Frame 4
[Receiver] Frame 4 received.
[Sender] ACK for Frame 4 received successfully.
[Sender] Sending Frame 5
[Receiver] Frame 5 received.
[Sender] Sending Frame 6
[Receiver] Frame 6 received.
[Sender] Sending Frame 7
[Receiver] Frame 7 received.
[Sender] Sending Frame 8
[Receiver] Frame 8 received.
[Sender] ACK for Frame 8 received successfully.
[Sender] Sending Frame 9
[Receiver] Frame 9 received.
[Sender] ACK for Frame 9 received successfully.
[Sender] Transmission completed
 */