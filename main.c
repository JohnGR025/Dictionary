/*  Developer's Info:
    Ioannis-Nektarios Bourbouriotis
    A.M: 2022202400025
    dit24025@go.uop.gr

    Alexandros Papadopoulos
    A.M: 2022202400156
    dit24156@go.uop.gr
*/

/*Import Files*/
#include "FunctionFolder\case1.h"
#include "FunctionFolder\case2.h"
#include "FunctionFolder\case3.h"
#include "FunctionFolder\case4.h"
#include "FunctionFolder\generalf.h"
#include "FunctionFolder\structs.h"

//Main Function
int main(void)
{
    srand(time(NULL)); //Set random values seed

    //Variables
    int i, check=0, count=0, total_products=0, total_orders=0;
    char option;
    char name[SIZE_NAMES]={0}; //For input uses
    Product *pHead = NULL; //product List (Storage)
    Order *oHead = NULL; //Order Priority Queue
    Order *order = NULL;
    Product *product=NULL, *tail=NULL, *temp=NULL;
    Order *tempOrder=NULL;

    //Starting
    printf("\nWork shift started. We wish you a VERY productive day!\n");
    do
    {
        do //Menu with available actions
        {
            printf("\n-Menu Options-\n");
            printf("1) Insert a new product\n");
            printf("2) Insert a new order\n");
            printf("3) Print a package\n");
            printf("4) Execute an order\n");
            printf("0) Exit\n");
            printf("Choose an option to continue: ");
            scanf("%c", &option);
            bufferCleaner(); //Clean the input buffer
            if (option<'0' || option>'4')
            {
                clearTerminal(); //"Clears" screen
                printf("Wrong input!\n");
                continue;
            }
        } while (option<'0' || option>'4');

        switch (option) //Execute options
        {
        case '1': //Insert a new product
            insertProduct(&pHead, &oHead, NULL, &pHead); //Insert the package to the storage depending the check value
            total_products++; //+1 product has been stored
        break;
        
        case '2': //Insert a new order
            order = (Order*)malloc(sizeof(Order));
            if(order == NULL) //Memory exception
            {
                printf("Memory for order was not allocated.\n");
                break;
            }

            //Set start value
            order->products = NULL;
            //Customer's Code
            do
            {
                printf("Give your code: ");
                scanf("%s", order->ccode);
                check = checkCustomerCode(oHead, order->ccode);
                bufferCleaner(); //Clean the input buffer
            } while (check==0);

            //Company's Name
            printf("Give company's name: ");
            fgets(order->cname, SIZE_NAMES, stdin);

            //Products' Count
            do
            {
                printf("How many products will the order contain: ");
                scanf("%s", name);
                bufferCleaner(); //Clean the input buffer
                order->pcount = convertStringToInt(name);
            } while (order->pcount==0);

            //Enter Product/s info
            order->products = NULL; // Start with NULL
            for (i = 0; i < order->pcount; i++) //For every product
                insertProduct(&pHead, &oHead, &order, &(order->products));
        
            orderPriority(&oHead, &pHead, &order); //Sets order's priority
            insertOrder(&oHead, &order); //Insert the order to the Order list
            clearTerminal(); //"Clears" screen
            printf("Your order has been stored!\n");
        break;

        case '3': //Print a package
            if (pHead==NULL) //Storage empty
            {
                clearTerminal(); //"Clear" screen
                printf("The storage has nothing but air inside.\n");
                continue;
            }

            printf("\nInput an EAN code, a name or * to print everything on storage: ");
            fgets(name, SIZE_NAMES, stdin);

            //The program checks all the EAN nums for the inputed code if won't inputed completely
            printPackages(name, &pHead);
            printf("\nPrinting finished\n");

            waitKeyPress(); //Wait until keypress
            clearTerminal();
        break;

        case '4': //Execute the orders
            clearTerminal(); //"Clears" screen

            //Check the values of the heads
            if (oHead==NULL)
            {
                printf("There are no orders to be executed yet.\n");
                continue;
            }
            if (pHead == NULL)
            {
                printf("The storage is empty. How do you expect to execute orders?\n");
                continue;
            }

            total_orders += executeOrders(&oHead, &pHead); //Execute current orders
            if (oHead==NULL)
            {
                printf("You finished every order so far.\n");
                waitKeyPress(); //Wait until keypress
                clearTerminal();
                continue;
            }

            //Calculate the priority of the remain orders
            printf("Calculation of priorities on remaining orders begins\n");
            tempOrder = oHead;
            while (tempOrder!=NULL)
            {
                orderPriority(&oHead, &pHead, &tempOrder); //Recalculate priorities
                tempOrder = tempOrder->next; //Next order
            }
            
            OrderSelectionSort(&oHead); //Change the nodes so the Order queue remains as priority queue
            printf("Calculation of priorities finished\n");
            waitKeyPress(); //Wait until keypress
            clearTerminal();
        break;
        }

        //clearTerminal(); //Cleans the screen (just an illusion)
    } while (option!='0');

    //Free every allocated memory
    printf("Closing the storage...\n");
    freeMemoryOrder(&oHead);
    freeMemoryProduct(&pHead);

    //End of program
    clearTerminal(); //Cleans the screen (just an illusion)
    printf("Work shift ended. Thanks for your work today!\n");
    printf("--Work Summary--\n");
    printf("Total orders executed: %d\n", total_orders);
    printf("Total products stored: %d\n", total_products);
    printf("See you tommorow!\n");
    return 0;
}

