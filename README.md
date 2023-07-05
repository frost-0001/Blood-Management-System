#include<stdio.h>
#include<stdlib.h>
void CreAcc()
{
    char name[50];
    int age;

    printf("Enter your full name: ");
    fgets(name, sizeof(name), stdin);

    printf("Enter your age: ");
    scanf("%d", &age);

    printf("\n\n\n");
    if (age<18)
    {
        printf("Warning!!!! \nDue to become a minor you can't donate your blood...\n");
    }
    printf("Name: %s\n", name);
    printf("Age: %d\n", age);
}

int main()

{
    printf("\n\n\t\t\t\t\t\t...........................\n");
    printf("\t\t\t\t\t\t: BLOOD MANAGEMENT SYSTEM :\n");
    printf("\t\t\t\t\t\t:.........................:\n\n\n\n");
    printf("\n\n\t\t\t\t GIVE BLOOD SAVE LIFE\n\n\n");
    printf("\t\t\t\t WELCOME TO BDS, PLEASE AVOID MONEY TRANSACTION\n\n\n");
    while(1)
    {
        int press;
        printf("\t\t\t\t press 1 to Create Account\n"
               "\t\t\t\t press 2 to Update Account\n"
               "\t\t\t\t press 3 to Delete Account\n"
               "\t\t\t\t press 4 to Read Donor List\n"
               "\t\t\t\t press 5 to Search For Donor\n"
               "\t\t\t\t press 6 to Cancel Donation\n"
               "\t\t\t\t press 0 to Exit\n");
        printf("\n\n\n");

        scanf("%d",&press);
        getchar();

        if(press==1)
        {
            CreAcc();
        }
    }
}
