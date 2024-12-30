/*Write a program to compute CRC code for the polynomials

sample Input and Output:- 

Enter data to be transmitted: 11100011                                         
Enter the Generating polynomial: 11001                                       
Data padded with n-1 zeros : 111000110000
CRC or Check value is : 0000
Final data to be sent : 111000110000
Enter the received data: 11100011                
Data received: 11100011
No error detected 


*/
// Method-1
// #include <stdio.h>
// #include <string.h>

// void xorOperation(char dividend[], char generator[], int n) {


//     for (int i = 0; i < n; i++) {


//         if (dividend[i] == generator[i])
//             dividend[i] = '0';
//         else
//             dividend[i] = '1';
            
        
//     }

// }

// void crc(char data[], char generator[], char crcCode[]) 

// {

//     int dataLen = strlen(data);
//     int genLen = strlen(generator);
//     char temp[128];
//     strcpy(temp, data);
//     for (int i = dataLen; i < dataLen + genLen - 1; i++) {
//         temp[i] = '0';
//      }
//     temp[dataLen + genLen - 1] = '\0'; // representing EOS
//     char dividend[128];
//     strncpy(dividend, temp, genLen);

//     for (int i = 0; i < dataLen; i++) {


//         if (dividend[0] == '1'){
//         xorOperation(dividend, generator, genLen);
//         }
//         for (int j = 0; j < genLen - 1; j++){

//             dividend[j] = dividend[j + 1];
//         }
//         dividend[genLen - 1] = temp[i + genLen];
    

//     }

//     strncpy(crcCode, dividend, genLen - 1);
//     crcCode[genLen - 1] = '\0';

// }

// int main(){
//     char data[128], generator[128], crcCode[128], transmitted[128];
    
//     printf("Enter data to be transmitted: ");
//     scanf("%s", data);
    
//     printf("Enter the Generating polynomial: ");
//     scanf("%s", generator);

//     printf("Data padded with n-1 zeros : ");
//     crc(data, generator, crcCode);
//     printf("%s%s", data, crcCode);
    
//     printf("CRC or Check value is : %s", crcCode);

//     strcpy(transmitted, data);
//     strcat(transmitted, crcCode);
//     printf("Final data \nto be sent : %s", transmitted);

//     printf("Enter the received data: ");
//     scanf("%s", transmitted);

//     printf("Data received: %s", transmitted);

//     crc(transmitted, generator, crcCode);

//     // Note :- Be careful to replace the zeros String for varying inputs , or write a seperate zeroGeneratingFunc to generate 0s of lenght = genLen - 1
//     if (strcmp(crcCode, "0000") == 0)
//         printf("No error detected\n");
//     else
//         printf("Error detected\n");

//     return 0;

// }


// Method-2 , much more Modular 



#include <stdio.h>
#include <string.h>

// XOR operation between dividend and divisor
void xor(char dividend[], char divisor[], int genLen) {
    for (int i = 0; i < genLen; i++) {
        dividend[i] = (dividend[i] == divisor[i]) ? '0' : '1';
    }
}

// Compute CRC for the given dataWord using the generator polynomial
void computeCRC(char dataWord[], char generator[], char crcCode[]) {
    int dataLen = strlen(dataWord);
    int genLen = strlen(generator);

    // Step 1: Form the codeword by appending genLen-1 zeros to the dataWord
    char temp[128];
    strcpy(temp, dataWord);

    for (int i = dataLen; i < dataLen + genLen - 1; i++) {
        temp[i] = '0';
    }
    temp[dataLen + genLen - 1] = '\0'; // Mark the end of the codeword

    // Step 2: Start the modulo-2 division (using XOR operation)
    char dividend[128];
    strncpy(dividend, temp, genLen); // Initialize the dividend with the first genLen characters of codeword

    for (int i = 0; i < dataLen; i++) {
        // Perform XOR if the first bit is 1
        if (dividend[0] == '1') {
            xor(dividend, generator, genLen);
        }

        // Shift bits to the left by one position to bring down the next bit
        for (int j = 0; j < genLen - 1; j++) {
            dividend[j] = dividend[j + 1];
        }
        
        // Bring down the next bit from temp (the codeword)
        dividend[genLen - 1] = temp[i + genLen];
    }

    // Copy the result (remainder) to crcCode
    strncpy(crcCode, dividend, genLen - 1);
    crcCode[genLen - 1] = '\0';
}

// Function to simulate the sender's end
void sender(char dataWord[], char generator[]) {
    // Redundant bits (CRC check value) will be calculated
    char redudantBits[128];
    computeCRC(dataWord, generator, redudantBits);

    // Display the padded data and the CRC check value
    printf("Data padded with zeros: %s%s\n", dataWord, redudantBits);
    printf("CRC or Check value: %s\n", redudantBits);

    // Create the codeword (dataWord + redundantBits) to be sent to receiver
    char codeWord[128];
    strcpy(codeWord, dataWord);
    strcat(codeWord, redudantBits);

    printf("Final data to be sent: %s\n", codeWord); // This should be sent to the receiver side
}

// Helper function to generate a zero string of a given length
void generateZeroString(char zeroStr[], int len) {
    for (int i = 0; i < len; i++) {
        zeroStr[i] = '0';
    }
    zeroStr[len] = '\0';
}

// Function to simulate the receiver's end
void receiver(char codeWord[], char generator[], int genLen) {
    char crcCode[128];
    computeCRC(codeWord, generator, crcCode); // Compute the CRC (remainder) for the received codeword

    printf("Data received: %s\n", codeWord);

    // Create a zero string of length genLen - 1 to compare with remainder
    char zeroStr[genLen - 1];
    generateZeroString(zeroStr, genLen - 1);

    // Check if the remainder is all zeros (indicating no error)
    if (strcmp(crcCode, zeroStr) == 0) {
        printf("No error detected\n");
    } else {
        printf("Error detected\n");
    }
}

int main() {
    char data[128], generator[128], received[128];

    printf("Enter data to be transmitted: ");
    scanf("%s", data); // Input the dataWord that needs to be transmitted

    printf("Enter the generator polynomial: ");
    scanf("%s", generator); // Input the generator polynomial

    // Sender process with the agreed-upon generator polynomial
    sender(data, generator);

    printf("Enter the received data: ");
    scanf("%s", received);

    // Receiver verifies if the received data has errors
    receiver(received, generator, strlen(generator));

    return 0;
}
