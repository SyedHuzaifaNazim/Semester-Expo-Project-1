#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <time.h>

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
	char type[10];
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
    
	    if (user->rolePrefix == 'F') {
	    strcpy(type, "Farmer");
		} else if (user->rolePrefix == 'W') {
		    strcpy(type, "Wholesaler");
		} else {
	    strcpy(type, "Retailer");
		}

    // Display the license number to the user
    system("cls");
    printf("\n\n                   --------------------------------\n");
	printf("\t  (((((((( Congratulation You Are Registered )))))))))\n");
	printf("                   --------------------------------\n\n\n\n");
    printf("\t _________________________________\n\n");
    printf("\t| -Your NIC: %s\n",user->nic);
    printf("\t| -Your Name: %s\n",user->name);
    printf("\t| -Your Father Nmae: %s\n",user->fatherName);
    printf("\t| -Aloted license number: %c%06d\n", user->rolePrefix, user->licenseNumber);
    printf("\t| -Type: %s\n",type);
    printf("\t _________________________________\n\n\n\n\n");
}

void fileComplaint()
{
    char userID[20];
    char complaint[100];
    char licenseNumber[8];
    printf(" -Enter your ID: ");
    scanf("%s", userID);

    printf(" -Describe your complaint: ");
    scanf(" %[^\n]", complaint);

    printf(" -Enter the license number you are complaining about: ");
    scanf("%s", licenseNumber);

    FILE *complaintFile = fopen("complaints.txt", "a");
    fprintf(complaintFile, "Complainant_ID: %s\nComplaint: %s\nLicense Number: %s\n\n", userID, complaint, licenseNumber);
    fclose(complaintFile);
    printf("\n\n                   --------------------------------\n");
	printf("\t  (((((((( Complaint filed successfully. )))))))))\n");
	printf("                   --------------------------------\n\n\n\n\n");
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
		
	struct UserInfo user;
	
    char choice;;
    system("color a");
    printf("\n\n                   --------------------------------\n");
	printf("\t  (((((((( Welcome to our Fair Food System )))))))))\n");
	printf("                   --------------------------------\n");
    printf("\n\n\n -Do you want to register press (R)\n -For complain press (C)\n -If you want to know the number of complaint of a license press (N)\n");
    printf("\n -Your Option: ");
    scanf(" %c", &choice);
    if (choice == 'R' || choice == 'r')
	{
		char role;
	    FILE *file;
		system("cls");
	    printf("\n\nWho are you? (Enter 'f' for farmer, 'w' for wholesaler, or 'r' for retailer): ");
	    scanf(" %c", &role);
	
		user.rolePrefix = role;
		system("cls");
		system("color 7");
		printf("\n\n");
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
		system("cls");
		printf("\n\n");
       fileComplaint();
    }
	
	else if (choice == 'N' || choice == 'n')
	{
		system("cls");
	    char licenseNumber[8];
	    printf("\n\n -Enter your license number to check complaints: ");
	    scanf("%s", licenseNumber);
//	    printf("\n\n\n\n");
		system("cls");
	    int complaintCount = countComplaints(licenseNumber);
	    printf("\n\n\n\n\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
	    printf("\n *******  Number of complaints against license number %s is %d *******\n", licenseNumber, complaintCount);
	    printf("\n\t  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n\n\n\n");
		}	
	else
	{
        printf("Invalid choice. Please enter 'R' to register or 'C' to complain.\n");
    }

    return 0;
}