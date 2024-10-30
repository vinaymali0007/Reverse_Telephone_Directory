#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 1000

// Define a 1structure for a contact
struct Contact {
    char phone_number[15];
    char first_name[50];
    char last_name[50];
    char address[100];
};

struct Contact hashTable[HASH_SIZE];

// Hash function to convert a phone number to an index
int hashFunction(char phone_number[]) {
    int sum = 0;
    for (int i = 0; phone_number[i] != '\0'; i++)
    {
        sum += phone_number[i];
    }
    return sum % HASH_SIZE;
}
// Function to check if the entered phone number is already present in the entries
int findContactByPhoneNumber(char phone_number[]) {
    int index = hashFunction(phone_number);
    for (int i = 0; i < HASH_SIZE; i++) {
        if (strcmp(phone_number, hashTable[index].phone_number) == 0) {
            return index; // Entry with the same phone number exists
        }
        index = (index + 1) % HASH_SIZE; // Linear probing to find the next availability
    }
    return -1; // Entry with the same phone number not found
}

// Function to insert a contact into the hash table
void insertContact(char phone_number[], char first_name[], char last_name[], char address[]) {
    int index = hashFunction(phone_number);

    if (findContactByPhoneNumber(phone_number) != -1) {
        printf("Duplicate phone number. Entry not accepted.\n");
    } else {
        while (hashTable[index].phone_number[0] != '\0') {
            
            index = (index + 1) % HASH_SIZE;
        }

        strcpy(hashTable[index].phone_number, phone_number);
        strcpy(hashTable[index].first_name, first_name);
        strcpy(hashTable[index].last_name, last_name);
        strcpy(hashTable[index].address, address);
        printf("Contact added successfully.\n");
    }
}

// Function to update first name, last name, and address for a given phone number
void updateContact(char phone_number[], char first_name[], char last_name[], char address[]) {
    int index = findContactByPhoneNumber(phone_number);

    if (index != -1) {
        strcpy(hashTable[index].first_name, first_name);
        strcpy(hashTable[index].last_name, last_name);
        strcpy(hashTable[index].address, address);
        printf("Contact updated successfully.\n");
    } else {
        printf("No update can be done since the entry does not exist.\n");
    }
}

// Function to search for a contact by phone number
int searchContact(char phone_number[]) {
    int index = findContactByPhoneNumber(phone_number);

    if (index != -1) {
        return index;
    } else {
        return -1;
    }
}

// Function to delete a contact by phone number
void deleteContact(char phone_number[]) {
    int index = findContactByPhoneNumber(phone_number);

    if (index != -1) {
        strcpy(hashTable[index].phone_number, "");
        printf("Contact deleted successfully.\n");
    } else {
        printf("Contact not found.\n");
    }
}

// Function to display the entire phonebook
void displayPhonebook() {
    printf("\nPhonebook Entries:\n");
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashTable[i].phone_number[0] != '\0') {
            printf("Phone Number: %s, First Name: %s, Last Name: %s, Address: %s\n",
                   hashTable[i].phone_number, hashTable[i].first_name, hashTable[i].last_name, hashTable[i].address);
        }
    }
}

// Function to load contacts from a file
void loadContactsFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file for reading.\n");
        return;
    }

    char phone_number[15];
    char first_name[50];
    char last_name[50];
    char address[100];

    while (fscanf(file, "%s %s %s %s", phone_number, first_name, last_name, address) == 4) {
        insertContact(phone_number, first_name, last_name, address);
    }

    fclose(file);
}

// Function to save contacts to a file
void saveContactsToFile(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }

    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashTable[i].phone_number[0] != '\0') {
            fprintf(file, "%s %s %s %s\n", hashTable[i].phone_number, hashTable[i].first_name, hashTable[i].last_name, hashTable[i].address);
        }
    }

    fclose(file);
}

int main() {
    int choice;
    char phone_number[15];
    char first_name[50];
    char last_name[50];
    char address[100];

    // Load contacts from a file (if available)
    loadContactsFromFile("contacts.txt");

    while (1) {
        printf("\nPhonebook Management System:\n");
        printf("1. Add Contact\n");
        printf("2. Update First Name, Last Name, and Address\n");
        printf("3. Search Contact\n");
        printf("4. Display Phonebook\n");
        printf("5. Delete Contact\n");
        printf("6. Save Contacts to File\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter Phone Number: ");
                scanf("%s", phone_number);
                printf("Enter First Name: ");
                scanf("%s", first_name);
                printf("Enter Last Name: ");
                scanf("%s", last_name);
                printf("Enter Address: ");
                scanf("%s", address);
                insertContact(phone_number, first_name, last_name, address);
                break;
            case 2:
                printf("Enter Phone Number to Update (First Name, Last Name, and Address): ");
                scanf("%s", phone_number);
                printf("Enter New First Name: ");
                scanf("%s", first_name);
                printf("Enter New Last Name: ");
                scanf("%s", last_name);
                printf("Enter New Address: ");
                scanf("%s", address);
                updateContact(phone_number, first_name, last_name, address);
                break;
            case 3:
                printf("Enter Phone Number to Search: ");
                scanf("%s", phone_number);
                int foundIndex = searchContact(phone_number);
                if (foundIndex != -1) {
                    printf("Contact found:\n");
                    printf("Phone Number: %s, First Name: %s, Last Name: %s, Address: %s\n",
                           hashTable[foundIndex].phone_number, hashTable[foundIndex].first_name, hashTable[foundIndex].last_name, hashTable[foundIndex].address);
                } else {
                    printf("Contact not found.\n");
                }
                break;
            case 4:
                displayPhonebook();
                break;
            case 5:
                printf("Enter Phone Number to Delete: ");
                scanf("%s", phone_number);
                deleteContact(phone_number);
                break;
            case 6:
                // Save contacts to a file
                saveContactsToFile("contacts.txt");
                printf("Contacts saved to file.\n");
                break;
            case 7:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
