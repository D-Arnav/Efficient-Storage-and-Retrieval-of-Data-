#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include "functions.h"

int main() {
  resetData();
  readCustomersFromFile();

  while(1)
  {
    printf("1.Create a new account\n2.Find your account\n3.Update your account\n4.Delete your account\n5.Exit\nEnter an option: ");
    int option, option2;
    scanf("%d", &option);
    printf("\n");

    int random, i;
    long long int ssn;
    char name[35];

    switch(option)
    {
      case 1:
        printf("Enter the following information for creating a new account\n----------------------------------------------------------------\n");

        Customer c;

        printf("Name: ");
        scanf("%s", &c.name);

        printf("Social Security Number (SSN): ");
        scanf("%lld", &c.ssn);

        while(1)
        {
          if(digits(c.ssn) == 9)
            break;
          else
            printf("enter a valid 9-digit ssn: ");
            scanf("%lld\n", &c.ssn);
        }

        char temp[100];
        gets(temp);
        c.address[0] = '\0';

        printf("\nAddress line 1: ");
        gets(temp);
        strcat(c.address, temp);

        printf("\nAddress line 2: ");

        gets(temp);
        strcat(c.address, "\n");
        strcat(c.address, temp);

        printf("\nCity: ");
        gets(temp);
        strcat(c.address, "\n");
        strcat(c.address, temp);

        printf("\nZipcode: ");
        gets(temp);
        strcat(c.address, " - ");
        strcat(c.address, temp);
        strcat(c.address, "\n");

        printf("\nDate of Birth\nDay: ");
        scanf("%d", &c.DOB.day);

        while(1)
        {
          if(checkIfDay(c.DOB.day))
            break;
          else
            printf("Enter a valid day: ");
            scanf("%d", &c.DOB.day);
        }

        printf("Month: ");
        scanf("%s", c.DOB.month);

        while(1)
        {
          if(checkIfMonth(c.DOB.month))
            break;
          else
            printf("enter a valid month: ");
            scanf("%s", c.DOB.month);
        }

        printf("Year: ");
        scanf("%d", &c.DOB.year);

        while(1)
        {
          if(checkIfYear(c.DOB.year))
            break;
          else
            printf("you need to be 18 to open a bank account: ");
            scanf("%d", &c.DOB.year);
        }

        printf("\nMartial Status: ");
        scanf("%s", c.status);

        while(1)
        {
          if(checkIfMartialStatus(c.status) == 1)
            break;
          else
            printf("Enter a valid martial status (Married/Unmarried): ");
            scanf("%s", c.status);
        }

        printf("\nAccount type: ");
        scanf("%s", c.account_type);

        while(1)
        {
          if(checkIfAccountType(c.account_type) == 1)
            break;
          else
            printf("enter a valid account type (Fixed/Saving): ");
            scanf("%s", c.account_type);
        }

        random = (c.DOB.day*c.DOB.year*1664525 + 1013904223)%10000;
        c.account_number = random > 0 ? random : -random;
        printf("\nYour account number is %d\n----------------------------------------------------------------\n\n", c.account_number);
        ssnRoot = insertNode(ssnRoot, c);
        linearProbingInsert(c);
        writeCustomersToFile(c);
      break;

      /*----------------------------------------------------------------*/

      case 2:
        option2 = 0;
        while(option2 != 1 && option2 != 2)
        {
          printf("1.Search by Name\n2.Search by SSN\nEnter an option: ");
          scanf("%d", &option2);

          if(option2 == 1){
            printf("Enter your name: ");
            scanf("%s", name);
            ssn = getSSN(ssnRoot, name);
          }
          else if(option2 == 2){
            printf("Enter your SSN: ");
            scanf("%lld", &ssn);
          }
          else
          {
            printf("Invalid option\n");
            continue;
          }
          i = linearProbingSearch(ssn);

          if (i == -1)
            break;

          printf("\nYour Details\n----------------------------------------------------------------\n");
          printf("SSN: %lld\n", customer[i].ssn);
          printf("Name: %s\n", customer[i].name);
          printf("Address: %s", customer[i].address);
          printf("Date of Birth: %d %s %d\n", customer[i].DOB.day, customer[i].DOB.month, customer[i].DOB.year);
          printf("Status: %s\n", customer[i].status);
          printf("Account Type: %s\n", customer[i].account_type);
          printf("Account Number: %d\n----------------------------------------------------------------\n\n", customer[i].account_number);
        }
      break;

      /*----------------------------------------------------------------*/

      case 3:
        printf("Enter your SSN: ");
        scanf("%lld", &ssn);
        i = linearProbingSearch(ssn);
        if (i == -1)
          break;

        printf("\nWhat do you want to modify\n1.Name\n2.Address\n3.Date of Birth\n4.Martial Status\n5.Account Type\nEnter an option: ");
        scanf("%d", &option2);

        switch(option2)
        {
          case 1:
            ssnRoot = deleteNode(ssnRoot, customer[i]);

            printf("Name: ");
            scanf("%s", &customer[i].name);

            ssnRoot = insertNode(ssnRoot, customer[i]);
          break;

          case 2:
            printf("Address (type 'end' after address): ");
            readString(customer[i].address);
          break;

          case 3:
            printf("Date of Birth\nday: ");
            scanf("%d", &customer[i].DOB.day);

            while(1)
            {
              if(checkIfDay(customer[i].DOB.day))
                break;
              else
                printf("enter a valid day: ");
                scanf("%d", &customer[i].DOB.day);
            }

            printf("month(in words): ");
            scanf("%s", customer[i].DOB.month);

            while(1)
            {
              if(checkIfMonth(customer[i].DOB.month))
                break;
              else
                printf("enter a valid month: ");
                scanf("%s", customer[i].DOB.month);
            }

            printf("year: ");
            scanf("%d", &customer[i].DOB.year);

            while(1)
            {
              if(checkIfYear(customer[i].DOB.year))
                break;
              else
                printf("you need to be 18 to open a bank account: ");
                scanf("%d", &customer[i].DOB.year);
            }
          break;

          case 4:
            printf("Martial Status: ");
            scanf("%s", customer[i].status);

            while(1)
            {
              if(checkIfMartialStatus(customer[i].status) == 1)
                break;
              else
                printf("enter a valid martial status (Married/Unmarried): ");
                scanf("%s", customer[i].status);
            }
          break;

          case 5:
            printf("Account type: ");
            scanf("%s", customer[i].account_type);

            while(1)
            {
              if(checkIfAccountType(customer[i].account_type) == 1)
                break;
              else
                printf("enter a valid account type (Fixed/Saving): ");
                scanf("%s", customer[i].account_type);
            }
          break;
        }
        printf("\n");
      break;

      /*----------------------------------------------------------------*/

      case 4:
        printf("Enter your SSN: ");
        scanf("%lld", &ssn);

        i = linearProbingSearch(ssn);
        if (i == -1)
          break;

        ssnRoot = deleteNode(ssnRoot, customer[i]);

        customer[i].ssn = 0;
        strcpy(customer[i].name, "\0");
      break;

      /*----------------------------------------------------------------*/

      case 5:
        printf("Thank you for using the bank system\nExiting...\n----------------------------------------------------------------");
        return 0;
      break;


    }
  }
  return 0;
}
