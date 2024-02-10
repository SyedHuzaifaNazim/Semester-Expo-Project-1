#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Define a structure to hold user information
struct UserInfo {
    char nic[20];
    char name[50];
    char fatherName[50];
    char rolePrefix;
    int licenseNumber;
};

void generateLicense(struct UserInfo *user, FILE *file)
{
    // Set role prefix based on user's role
    switch (user->rolePrefix)
    {
        case 'f':
        case 'F':
            user->rolePrefix = 'F';
            break;
        case 'w':
        case 'W':
            user->rolePrefix = 'W';
            break;
        case 'r':
        case 'R':
            user->rolePrefix = 'R';
            break;
        default:
            printf("Invalid role. Please enter 'f' for farmer, 'w' for wholesaler, or 'r' for retailer.\n");
            return;
    }

    // Get user information
    printf("Enter your NIC: ");
    scanf("%s", user->nic);

    printf("Enter your name: ");
    scanf(" %[^\n]", user->name);

    printf("Enter your father's name: ");
    scanf(" %[^\n]", user->fatherName);

    // Seed the random number generator
    srand(time(NULL));

    // Generate a 6-digit license number
    user->licenseNumber = 100000 + rand() % 900000;

    // Save user information and license number to the respective file
    fprintf(file, "%c%06d\t%s\t%s\t%s\n", user->rolePrefix, user->licenseNumber, user->nic, user->name, user->fatherName);

    // Display the license number to the user
    system("cls");
    
    printf("Your license number: %c%06d\n", user->rolePrefix, user->licenseNumber);
}

void fileComplaint()
{
    char userID[20];
    char complaint[100];
    char licenseNumber[8];

    printf("Enter your ID: ");
    scanf("%s", userID);

    printf("Describe your complaint: ");
    scanf(" %[^\n]", complaint);

    printf("Enter the license number you are complaining about: ");
    scanf("%s", licenseNumber);

    FILE *complaintFile = fopen("complaints.txt", "a");
    fprintf(complaintFile, "Complainant_ID: %s\nComplaint: %s\nLicense Number: %s\n\n", userID, complaint, licenseNumber);
    fclose(complaintFile);
    printf("Complaint filed successfully.\n");
}

int countComplaints(const char *licenseNumber)
{
    int count = 0;
    char line[256];
    FILE *complaintFile = fopen("complaints.txt", "r");

    if (complaintFile == NULL)
	{
        return 0;
    }

    while (fgets(line, sizeof(line), complaintFile) != NULL)
	{
        if (strstr(line, licenseNumber) != NULL)
		{
            count++;
        }
    }

    fclose(complaintFile);
    return count;
}

int main()
{
	do{
	struct UserInfo user;
	
    char choice;

    printf("\n\n                           Do you want to register (R) or complain (C) or you want to know the number of complaint of a license (N)? ");
    scanf("%c\n\n", &choice);

    if (choice == 'R' || choice == 'r')
	{
		char role;
	    FILE *file;
	
	    printf("Who are you? (Enter 'f' for farmer, 'w' for wholesaler, or 'r' for retailer): ");
	    scanf(" %c", &role);
	
		user.rolePrefix = role;

	    switch (role)
        {
            case 'f':
            case 'F':
                file = fopen("farmer_license.txt", "a");
                generateLicense(&user, file);
                fclose(file);
                break;
            case 'w':
            case 'W':
                file = fopen("wholesaler_license.txt", "a");
                generateLicense(&user, file);
                fclose(file);
                break;
            case 'r':
            case 'R':
                file = fopen("retailer_license.txt", "a");
                generateLicense(&user, file);
                fclose(file);
                break;
            default:
                printf("Invalid role. Please enter 'f' for farmer, 'w' for wholesaler, or 'r' for retailer.\n");
                break;
        }
    }
	
	else if (choice == 'C' || choice == 'c')
	{
       fileComplaint();
    }
	
	else if (choice == 'N' || choice == 'n')
	{
	    char licenseNumber[8];
	    printf("Enter your license number to check complaints: ");
	    scanf("%s", licenseNumber);
	
	    int complaintCount = countComplaints(licenseNumber);
	    printf("Number of complaints against license number %s: %d\n", licenseNumber, complaintCount);
		}	
	else
	{
        printf("Invalid choice. Please enter 'R' to register or 'C' to complain.\n");
    }
 }
}
 while(choice==0);
 
	printf(".....moye moye");
 
 printf("hello");
    return 0;
}

