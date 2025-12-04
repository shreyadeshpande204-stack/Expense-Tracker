#include <stdio.h>
#include <string.h>

void addexpense();
void viewexpense();
int totalexpense();
void searchexpense();
void category();
void monthlyexpense();

int main()
{
    int choice;
    while (1)
    {
        printf("1. Add new expense\n");
        printf("2. View expense\n");
        printf("3. Total Expense\n");
        printf("4. Search for an expense\n");
        printf("5. Category-wise expense\n");
        printf("6. Monthly expense\n");
        printf("7. Exit\n");
        printf("Enter your choice:\n");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                printf("You chose to add\n");
                addexpense();
                break;

            case 2:
                printf("You chose to view\n");
                viewexpense();
                break;

            case 3:
                printf("You chose total expenses\n");
                totalexpense();
                break;

            case 4:
                printf("You chose to search\n");
                searchexpense();
                break;

            case 5:
                printf("You chose category-wise expenses\n");
                category();
                break;

            case 6:
                printf("You chose monthly expense\n");
                monthlyexpense();
                break;

            case 7:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Exiting...\n");
                return 0;
        }
    }

    return 0;
}

void addexpense()
{
    char category[50];
    char date[20];
    float amount;
    int n, i = 0;

    printf("Enter how many expenses you want to add\n");
    scanf("%d", &n);
    getchar();

    FILE *fp = fopen("Expenses.txt", "a");

    if (fp == NULL)
    {
        printf("Error in opening the file\n");
        return;
    }

    while (i < n)
    {
        printf("Enter Category: ");
        scanf(" %[^\n]", category);

        printf("Enter Date DD/MM/YYYY: ");
        scanf(" %[^\n]", date);

        printf("Enter amount: ");
        scanf("%f", &amount);

        fprintf(fp, "%s %s %.2f\n", category, date, amount);
        i++;
    }

    fclose(fp);
}

void viewexpense()
{
    FILE *fp;
    char line[200];

    fp = fopen("Expenses.txt", "r");

    if (fp == NULL)
    {
        printf("No expenses found!\n");
        return;
    }

    printf("\nExpenses\n");

    while (fgets(line, sizeof(line), fp))
    {
        printf("%s", line);
    }

    fclose(fp);
}

int totalexpense()
{
    FILE *fp;
    char category[50], date[20];
    float amount, total = 0;

    fp = fopen("Expenses.txt", "r");

    if (fp == NULL)
    {
        printf("Unable to open file!\n");
        return 1;
    }

    while (fscanf(fp, "%s %s %f", category, date, &amount) == 3)
    {
        total += amount;
    }

    fclose(fp);

    printf("Total Amount Spent = %.2f\n", total);
    return 0;
}

void searchexpense()
{
    FILE *fp = fopen("Expenses.txt", "r");
    char line[200], key[50];

    if (fp == NULL)
    {
        printf("Unable to open file!\n");
        return;
    }

    printf("Enter word to search: ");
    getchar();
    fgets(key, sizeof(key), stdin);

    key[strcspn(key, "\n")] = 0;

    printf("\nResults\n");

    while (fgets(line, sizeof(line), fp))
    {
        if (strstr(line, key))
        {
            printf("%s", line);
        }
    }

    fclose(fp);
}

void category()
{
    FILE *fp = fopen("Expenses.txt", "r");
    char line[200], category[50];

    if (fp == NULL)
    {
        printf("Cannot open file!\n");
        return;
    }

    printf("Enter category: ");
    getchar();
    fgets(category, sizeof(category), stdin);

    category[strcspn(category, "\n")] = 0;

    printf("\nResult\n");

    while (fgets(line, sizeof(line), fp))
    {
        if (strncmp(line, category, strlen(category)) == 0)
        {
            printf("%s", line);
        }
    }

    fclose(fp);
}

void monthlyexpense()
{
    FILE *fp = fopen("Expenses.txt", "r");
    char line[200], category[50], date[20];
    float amount, total = 0;
    int userMonth;

    if (fp == NULL)
    {
        printf("Cannot open file!\n");
        return;
    }

    printf("Enter month (1-12): ");
    scanf("%d", &userMonth);

    printf("\n--- Expenses for month %d ---\n", userMonth);

    while (fgets(line, sizeof(line), fp))
    {
        if (sscanf(line, "%s %s %f", category, date, &amount) == 3)
        {
            int month = (date[3] - '0') * 10 + (date[4] - '0');

            if (month == userMonth)
            {
                total += amount;
                printf("%s", line);
            }
        }
    }

    fclose(fp);

    printf("\nTotal expense for month %d = %.2f\n", userMonth, total);
}
