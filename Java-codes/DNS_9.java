// 5) Implementation of DNS
import java.net.*;
import java.util.Scanner;

class DNS_9 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        System.out.println("Enter a domain name :");
        String domain = sc.nextLine();

        try {
            InetAddress[] addresses = InetAddress.getAllByName(domain);
            System.out.println("IP addresses for " + domain + ":");
            for (InetAddress address : addresses) {
                System.out.println(" - " + address.getHostAddress());
            }
        } catch (UnknownHostException e) {
            System.out.println("Could not resolve domain: " + e.getMessage());
        }
        sc.close();
    }
}

/*
Output:- 
javac DNS_9.java 
viishhnu@fedora:~/Backup/SEM-5/KMIT LABS/CN lab/Java-codes$ java DNS_9 
Enter a domain name :
www.google.com
IP addresses for www.google.com:
 - 142.250.194.228
 - 2404:6800:4002:825:0:0:0:2004
 */