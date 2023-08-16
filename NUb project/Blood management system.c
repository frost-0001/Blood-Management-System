#include<stdio.h>
#include<string.h>

char ID[7];

void CreAcc(FILE *file)
{
    while (1)
    {
        printf("If you want to proceed with NID choose N or if you want to proceed with  Birth certificate choose B. \n");
        printf("Enter the first character (N or B): \n");
        scanf(" %c", &ID[0]);

        if (ID[0] == 'N' || ID[0] == 'B')
        {
            break;
        }
        else
        {
            printf("Invalid option. Please try again.\n");
        }
    }
    printf("Enter last 5 numbers of your NID if you chose N or Birth Certificate if you chose B: \n");

    for (int i = 0; i < 5; i++)
    {
        scanf(" %c", &ID[i + 1]);
    }

    printf("Your ID is: ");
    for (int i = 0; i < 6; i++)
    {
        printf("%c", ID[i]);
    }
    printf("\n");

    char name[25];
    int age;
    char address[60];
    char BG[3];
    char gender;
    char lastDonationDate[12];
    char contactNumber[12];
    char RcontactNumber[12];

    getchar();
    printf("Enter your name: ");
    scanf("%[^\n]", name);

    printf("Enter your age: ");
    scanf("%d", &age);
    getchar();

    printf("Press M(male) or F(Female) or O(others): \n");
    scanf("%c",&gender);
    getchar();

    printf("Enter your address: \n");
    scanf("%[^\n]", address);

    printf("Enter your Blood group: \n");
    scanf("%s",&BG);

    printf("Enter the last date of your blood donation (e.g., DD/MM/YYYY): \n");
    scanf("%s",&lastDonationDate);

    printf("Enter your contact number : \n");
    scanf("%s",&contactNumber);

    printf("Enter contact number of a relative: \n");
    scanf("%s",&RcontactNumber);


    fprintf(file, "Name: %s\n", name);
    fprintf(file, "ID: %s\n", ID);
    fprintf(file, "Age: %d\n", age);
    fprintf(file, "Gender: %c\n",gender);
    fprintf(file, "Blood Group: %s\n",BG);
    fprintf(file, "Address: %s\n", address);
    fprintf(file, "Last date of blood donation: %s\n", lastDonationDate);
    fprintf(file, "Contact Number : %s\n",contactNumber);
    fprintf(file, "Contact Number of relative: %s\n\n\n\n",RcontactNumber);
    fclose(file);

    printf("Account created successfully");
    printf("\n\n\n");
}


void upAcc()
{
    {
        char searchID[7];
        printf("Enter the ID (first character and last 5 numbers): ");
        scanf("%s", searchID);

        FILE *file = fopen("database.txt", "r+");
        if (file == NULL)
        {
            printf("There is some problem with local Database.Try Again later\n");
            return;
        }

        char line[150];
        int found = 0;

        while (fgets(line, sizeof(line), file) != NULL)
        {
            char ID[7];
            if (sscanf(line, "ID: %6s", ID) == 1)
            {
                if (strcmp(ID, searchID) == 0)
                {
                    found = 1;

                    char address[100], lastDonationDate[20];
                    printf("Enter the updated address: ");
                    scanf(" %[^\n]", address);

                    printf("Enter the updated last date of blood donation (e.g., DD/MM/YYYY): ");
                    scanf(" %[^\n]", lastDonationDate);

                    // Update address and last donation date directly in the file
                    fseek(file, -1, SEEK_CUR); // Move the cursor one position back from the current position
                    fprintf(file, "Address: %s\n", address);
                    fprintf(file, "Last Donation Date: %s\n", lastDonationDate);

                    break; // Once we've updated the record, we don't need to search further
                }
            }
        }

        fclose(file);

        if (!found)
        {
            printf("Record not found for the given ID.\n");
        }
        else
        {
            printf("Record updated successfully.\n");
        }
    }

}




void delAcc()
{
    char searchID[7];
    printf("Enter the ID (first character and last 5 numbers) to delete: ");
    scanf("%s", searchID);

    FILE *file = fopen("database.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the database file.\n");
        return;
    }

    FILE *tempFile = fopen("temp.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error creating a temporary file.\n");
        fclose(file);
        return;
    }

    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        char ID[7];
        if (sscanf(line, "ID: %6s", ID) == 1)
        {
            if (strcmp(ID, searchID) == 0)
            {
                found = 1;
                fprintf(tempFile, "%s (Person no longer available)\n", line);
            }
            else
            {
                fprintf(tempFile, "%s", line);
            }
        }
        else
        {
            fprintf(tempFile, "%s", line);
        }
    }

    fclose(file);
    fclose(tempFile);

    if (!found)
    {
        remove("temp.txt");
        printf("Record not found for the given ID.\n");
    }
    else
    {
        remove("database.txt");
        rename("temp.txt", "database.txt");
        printf("Account Deleted.\n");
    }
}


struct Donor
{
    char bloodGroup[10];
    char location[50];
};
void inner_system(int press)
{
    FILE *file;
    char  date[20];
    char bg[5];
    char loc[100];
    char ch;
    int PassCode=1234;
    int EnterCode;


    if (press == 4)
    {
        printf("This Sector Belongs to Admins Only\n");
        printf("Enter The PassCode:");
        scanf("%d",&EnterCode);
        if(EnterCode==PassCode)
        {
            printf("Access Granted\n");
            printf("----------------------------\n");
            file=fopen("database.txt","r");
            if(file==NULL)
            {
                printf("file doesn't exist");
            }
            else
            {
                while(!feof(file))
                {
                    ch=fgetc(file);
                    printf("%c",ch);
                }
                fclose(file);
            }
        }
        else
        {
            printf("Access Denied\n");
        }
    }
    else if (press == 5)
    {
        printf("Enter Blood Group: ");
        scanf(" %s", &bg);
        printf("Enter Location: ");
        scanf(" %s", &loc);
        printf("Enter Date of Donation: ");
        scanf("%s", &date);
        FILE *file = fopen("database.txt", "r");
        if (file == NULL)
        {
            printf("Failed to open the file.\n");
            //return 1;
        }

        struct Donor donor;

        while (fscanf(file, "%s %s", donor.bloodGroup, donor.location) != EOF)
        {
            if (strstr(donor.location, loc) != NULL || strstr(donor.bloodGroup, bg) != NULL)
            {
                printf("Blood Group: %s    \n", donor.bloodGroup);
                printf("Location: %s\n", donor.location);
                printf("-----------------------\n");
            }
        }

        fclose(file);


    }



    else if(press==0 )
    {
        printf("Thank You for using our service");
        //return 0;

    }
}



int main()
{
    printf("\n\n\t\t\t\t\t\t...........................\n");
    printf("\t\t\t\t\t\t: BLOOD MANAGEMENT SYSTEM :\n");
    printf("\t\t\t\t\t\t:.........................:\n\n");
    printf("\n\t\t\t\t\t\tGIVE BLOOD SAVE LIFE\n\n\n");
    printf("\t\t\t\t WELCOME TO BDS, PLEASE AVOID MONEY TRANSACTION\n\n");
    while (1)
    {
        FILE *file;
        int press;
        printf("\t\t\t\t\t\t press 1 to Create Account\n"
               "\t\t\t\t\t\t press 2 to Update Account\n"
               "\t\t\t\t\t\t press 3 to Delete Account\n"
               "\t\t\t\t\t\t press 4 to Read Donor List\n"
               "\t\t\t\t\t\t press 5 to Search For Donor\n"
               "\t\t\t\t\t\t press 0 to Exit\n");
        printf("\n\n\n");

        scanf("%d", &press);
        getchar();

        if (press == 1)
        {
            file=fopen("database.txt", "a");
            if(file==NULL)
            {
                printf("There Is something wrong with local Database.");
            }
            CreAcc(file);
        }
        if (press == 2)
        {
            upAcc();
        }
        if(press == 3)
        {
            delAcc();

        }
        if(press == 0)
        {
            break;
        }
        inner_system(press);

    }

    return 0;
}

