#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define SHIFT_AMOUNT 5

int main()
{
    char original[100];

    bool validMessage = false;
    printf("Enter the message to be encrypted(Upper case only): ");
    fgets(original, sizeof(original), stdin);
    int orilen = strnlen(original, sizeof(original)) - 1;
    while (!validMessage)
    {
        validMessage = true;

        for (int i = 0; i < orilen; i++)
        {
            if (!isupper(original[i]))
            {
                printf("\n");
                printf("Message must contain only uppercase characters\n");
                printf("Enter again: ");
                fgets(original, sizeof(original), stdin);
                orilen = strnlen(original, sizeof(original)) - 1;

                validMessage = false;
                break;
            }
        }
    }

    char *encrytedMessage = malloc((orilen + 1) * sizeof(char));
    for (int i = 0; i < orilen; i++)
    {
        encrytedMessage[i] = original[i] + SHIFT_AMOUNT;
        if (encrytedMessage[i] > 'Z')
        {
            encrytedMessage[i] -= 'Z' - 'A' + 1;

            //'[' is at 91 and ('Z' is 90 in table)
            //'Z' is 90 and 'A' is 68 , so 'Z' - 'A' + 1 is 26
            //'[' is changed from 91 to 91 - 26, which is 65 i.e ('A')
        }
    }
    encrytedMessage[orilen] = '\0';

    int encryplen = orilen;
    char *decry = malloc((encryplen + 1) * sizeof(char));
    for (int i = 0; i < encryplen; i++)
    {
        decry[i] = encrytedMessage[i] - SHIFT_AMOUNT;
        if (decry[i] < 'A')
        {
            decry[i] += 'Z' - 'A' + 1;
            //'@' is at 64 in table ('A' is at 65 at table)
            //'Z' is 90, 'A' is 65, so 'Z' - 'A' + 1 is 26
            //'@' is changed from 64 to 64 + 26 , which is 90 ('Z')
        }
    }
    decry[encryplen] = '\0';

    printf("\n");
    printf("Original Message : %s", original);
    printf("Encrypted Message: %s\n", encrytedMessage);
    printf("Decrypted Message: %s\n", decry);

    free(encrytedMessage);
    encrytedMessage = NULL;
    free(decry);
    decry = NULL;
}