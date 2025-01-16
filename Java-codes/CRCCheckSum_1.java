// 1) Write a program to compute CRC code for the polynomials CRC-12, CRC-16 and CRC CCIP
import java.util.Scanner;

public class CRCCheckSum_1 {
    
    // XOR operation
    static String xor(String a, String b) {
        StringBuilder result = new StringBuilder();
        for (int i = 0; i < b.length(); i++) {
            result.append(a.charAt(i) == b.charAt(i) ? '0' : '1');
        }
        return result.toString();
    }

    // Calculate CRC
    static String computeCRC(String data, String generator) {
        int genLen = generator.length();
        String dividend = data + "0".repeat(genLen - 1); // this divided is called as code word
        
        for (int i = 0; i <= dividend.length() - genLen; i++) {
            if (dividend.charAt(i) == '1') {
                dividend = dividend.substring(0, i) +
                        xor(dividend.substring(i, i + genLen), generator) +
                        dividend.substring(i + genLen);
            }
        }
        
        return dividend.substring(dividend.length() - genLen + 1);
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Input data and generator
        System.out.print("Enter data to be transmitted: ");
        String data = sc.next();
        System.out.print("Enter the generator polynomial: ");
        String generator = sc.next();

        // Compute CRC at sender's end
        String crc = computeCRC(data, generator);
        String codeword = data + crc;
        System.out.println("Data padded with CRC: " + codeword);
        System.out.println("CRC or Check value: " + crc);

        // Simulate receiver end
        System.out.print("Enter the received data: ");
        String received = sc.next();
        String receivedCRC = computeCRC(received, generator);
        
        System.out.println("Data received: " + received);
        if (receivedCRC.equals("0".repeat(generator.length() - 1))) {
            System.out.println("No error detected");
        } else {
            System.out.println("Error detected");
        }
        sc.close();
    }
}
/*
Output:-

Enter data to be transmitted: 1101011011  
Enter the generator polynomial: 1101  
Data padded with CRC: 1101011011110  
CRC or Check value: 110  
Enter the received data: 1101011011110  
Data received: 1101011011110  
No error detected  

 */