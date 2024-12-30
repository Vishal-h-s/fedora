// 1) Write a program to compute CRC code for the polynomials CRC-12, CRC-16 and CRC CCIP


import java.util.Scanner;

public class CRCChecksum_1 {

    public static void xor(char[] dividend, char[] divisor) {
        for (int i = 0; i < divisor.length; i++) {
            dividend[i] ^= divisor[i];
        }
    }

    public static void computeCRC(String dataWord, String generator, char[] crcCode) {
        char[] temp = (dataWord + "0".repeat(generator.length() - 1)).toCharArray();
        char[] dividend = new char[generator.length()];
        System.arraycopy(temp, 0, dividend, 0, generator.length());

        for (int i = 0; i < dataWord.length(); i++) {
            if (dividend[0] == '1')
                xor(dividend, generator.toCharArray());
            System.arraycopy(dividend, 1, dividend, 0, generator.length() - 1);
            dividend[generator.length() - 1] = temp[i + generator.length()];
        }
        System.arraycopy(dividend, 0, crcCode, 0, generator.length() - 1);
    }

    public static void sender(String dataWord, String generator) {
        char[] redundantBits = new char[generator.length() - 1];
        computeCRC(dataWord, generator, redundantBits);
        System.out.println("Final data to be sent: " + dataWord + new String(redundantBits));
    }

    public static void receiver(String codeWord, String generator) {
        char[] crcCode = new char[generator.length() - 1];
        computeCRC(codeWord, generator, crcCode);
        System.out.println(new String(crcCode).equals("0".repeat(generator.length() - 1)) ? "No error detected"
                : "Error detected");
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter data to be transmitted: ");
        String data = sc.next();
        System.out.print("Enter the generator polynomial: ");
        String generator = sc.next();
        sender(data, generator);
        System.out.print("Enter the received data: ");
        receiver(sc.next(), generator);
        sc.close();
    }
}
