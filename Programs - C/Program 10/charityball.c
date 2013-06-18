/* ****************** */
/* P10 - Charity Ball */
/* Justin Bisignano   */
/* COP 3223 Section 4 */
/* 11/24/2012         */
/* ****************** */

//////////////////////////////////////////////////
// This program has implemented the following:  //
//     (1) Ticket Sales and Total Revenue       //
//     (2) Raffle Ticket Sales and Award Raffle //
//     (3) Drink Ticket Sales                   //
//     (4) Auction Ticket Sales, Award Auction, //
//             and Award Person                 //
//                                              //
// But has not yet successfully implemented:    //
//          Nothing! All Parts Implemented      //
//////////////////////////////////////////////////

#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_GUESTS 1000
#define MAX_AUCTION_ITEMS 1000
#define MAX_RAFFLE_TICKETS 100000
#define MAX_RAFFLE_PRIZES 100
#define DRINK_KINDS 10
#define COMMAND_SIZE 20

// Structs
typedef struct {
    int numPresaleTickets;
    int ticketNumber;
    float presaleCost;
    float doorCost;
} ticket_sales;

typedef struct {
    int open;
    int numItems;
    int currentWinner[MAX_AUCTION_ITEMS];
    float currentBid[MAX_AUCTION_ITEMS];
    float itemMarketPrice[MAX_AUCTION_ITEMS];
    float minBidIncrement;
} auction_struct;

typedef struct {
    int numTicketsLeft;
    int ticketCost; // int, because the instructions said it is strange to not have a ticket cost in whole dollars
    int numPrizes;
    int ticketIndex;
    int ticketOwner[MAX_RAFFLE_TICKETS];
    float prizeValue[MAX_RAFFLE_PRIZES];
} raffle_struct;

typedef struct {
    int stock[DRINK_KINDS];
    float price[DRINK_KINDS];
} drink_struct;

// Function Prototypes
float buyTicket(FILE *ofp, ticket_sales* tickets, int numSold);
void bidItem(FILE *ofp, auction_struct* auction, int itemNum, int personNum, float bidAmount);
int buyRaffle(FILE *ofp, raffle_struct* raffle, float personNet[], int numSold, int personNumber);
float buyDrink(FILE *ofp, drink_struct* drinks, int numSold, int drinkNumber);
void printRevenue(FILE *ofp, float revenue);
void closeAuction(FILE *ofp, auction_struct* auction);
void initilizeArray(int array[], int length, int value);
void awardRaffle(FILE *ofp, raffle_struct* raffle, float personNet[], int item, int ticketNumber);
void awardPerson(FILE *ofp, ticket_sales* tickets, float personNet[], int ID);
float awardAuction(FILE *ofp, auction_struct* auction, float personNet[], int itemNum);


// Main Function
int main(void){
    // Initilize Variables
    int i, numEvents, k, n, p, t, item, ID; // Variables k, n, p, and t named as per the Program 10 input file format specification. Because i was taken for looping, the specification's use of i is replaced by item and ID
    float d; // d represents the dollar amount of a bid, as per the input specification.
    float revenue = 0;
    char command[COMMAND_SIZE];

    // To keep track of a person's net gain, we'll use this array
    float personNet[MAX_GUESTS];

    // Initilize Structs
    ticket_sales tickets;
    tickets.ticketNumber = 0;
    auction_struct auction;
    auction.open = 1;
    raffle_struct raffle;
    raffle.ticketIndex = 0;
    drink_struct drinks;

    // Open Files
    FILE *ifp;
    ifp = fopen("auction.txt", "r"); // There wasn't a specific input file name given, so I'm leaving this as simply "auction.txt"
    FILE *ofp;
    ofp = fopen("auction.out", "w");


    // Get the first 8 lines of the input file and act on them
    // Ticket info is on line 1
    fscanf(ifp, "%f%f%d", &tickets.presaleCost, &tickets.doorCost, &tickets.numPresaleTickets);
    revenue += tickets.presaleCost * tickets.numPresaleTickets; // Add the presale tickets to the total revenue
    tickets.ticketNumber = tickets.numPresaleTickets-1; // Set the current ticket number index

    // Auction info is on lines 2 and 3
    fscanf(ifp, "%d%f", &auction.numItems, &auction.minBidIncrement);
    for(i=0; i<auction.numItems; i++)
        fscanf(ifp, "%f", &auction.itemMarketPrice[i]);
    // Initilize the auction.currentWinner array so that each item gets set to -1 to indicate no winner.
    initilizeArray(auction.currentWinner, auction.numItems, -1);
    initilizeArray(auction.currentBid, auction.numItems, 0);

    // Raffle info is on lines 4 and 5
    fscanf(ifp, "%d%d%d", &raffle.numTicketsLeft, &raffle.ticketCost, &raffle.numPrizes);
    for(i=0; i<raffle.numPrizes; i++)
        fscanf(ifp, "%f", &raffle.prizeValue[i]);
    // Initilize the raffle.ticketOwner array so that each ticket is set to -1 to indicate no owner.
    initilizeArray(raffle.ticketOwner, raffle.numTicketsLeft, -1);

    // Drink info is on lines 6 and 7
    for(i=0; i<DRINK_KINDS; i++)
        fscanf(ifp, "%d", &drinks.stock[i]);
    for(i=0; i<DRINK_KINDS; i++)
        fscanf(ifp, "%f", &drinks.price[i]);

    // Line 8 is the number of events that will come after this line.
    fscanf(ifp, "%d", &numEvents);


    // Create outer main loop
    for(i=0; i<numEvents; i++){
        // Get event from file
        fscanf(ifp, "%s", command);

        // Check event and run the appropriate function
        if(strcmp(command, "BUY") == 0){
            // Could be either TICKET, RAFFLE, or DRINK. Scan in next token and compare.
            fscanf(ifp, "%s", command);
            if(strcmp(command, "TICKET") == 0){
                fscanf(ifp, "%d", &k);
                revenue += buyTicket(ofp, &tickets, k);
            }
            else if(strcmp(command, "RAFFLE") == 0){
                fscanf(ifp, "%d%d", &k, &p);
                revenue += buyRaffle(ofp, &raffle, personNet, k, p);
            }
            else if(strcmp(command, "DRINK") == 0){
                fscanf(ifp, "%d%d", &k, &n);
                revenue += buyDrink(ofp, &drinks, k, n);
            }
        }
        else if(strcmp(command, "BIDITEM") == 0){
                fscanf(ifp, "%d%d%f", &k, &p, &d);
                bidItem(ofp, &auction, k, p, d);
        }
        else if(strcmp(command, "CLOSEAUCTION") == 0)
            closeAuction(ofp, &auction);

        else if(strcmp(command, "AWARD") == 0){
            fscanf(ifp, "%s", command);
            if(strcmp(command, "RAFFLE") == 0){
                fscanf(ifp, "%d%d", &item, &t);
                awardRaffle(ofp, &raffle, personNet, item, t);
            }
            else if(strcmp(command, "AUCTION") == 0){
                fscanf(ifp, "%d", &item);
                revenue += awardAuction(ofp, &auction, personNet, item);
            }
            else if(strcmp(command, "PERSON") == 0){
                fscanf(ifp, "%d", &ID);
                awardPerson(ofp, &tickets, personNet, ID);
            }
        }
        else if(strcmp(command, "TOTAL") == 0){
            fscanf(ifp, "%s", command);
            if(strcmp(command, "REVENUE") == 0)
                printRevenue(ofp, revenue);
        }
    }
    // Since we are done with the files, close them
    fclose(ifp);
    fclose(ofp);

    // Program Completed, so return 0.
    return 0;
}

// Returns the revenue made from buying tickets
float buyTicket(FILE *ofp, ticket_sales* tickets, int numSold){
    int start = tickets->ticketNumber;

    // It was guarenteed that the number of guests won't exceed 1000, but it's always good to check, just in case.
    if((start+numSold)>=MAX_GUESTS)
        numSold = (MAX_GUESTS-1) - start;

    // Set increase the ticket number by the number of tickets sold.
    tickets->ticketNumber += numSold;

    // Print the output to the file and return to main
    fprintf(ofp, "SOLD TICKETS %d - %d\n", start+1, start+numSold);
    return numSold * tickets->doorCost;
}

int buyRaffle(FILE *ofp, raffle_struct* raffle, float personNet[], int numSold, int personNumber){
    int max;

    if(numSold>(raffle->numTicketsLeft))
        numSold = raffle->numTicketsLeft;

    max = raffle->ticketIndex+numSold;
    // Only sell tickets if we have more to sell
    if(raffle->numTicketsLeft>0){
        // Print the first part of the output
        fprintf(ofp, "RAFFLE TICKETS %d - ", raffle->ticketIndex);

        // Use a while loop instead of the for loop to eliminate unnecessary variables and calculations.
        //for(i=raffle.ticketIndex; i<max; i++){
        while((raffle->ticketIndex)<max){
            raffle->ticketOwner[raffle->ticketIndex] = personNumber;
            raffle->ticketIndex++;
        }

        // Decrease the number of tickets left to sell, since we just sold some
        raffle->numTicketsLeft -= numSold;

        // Print the rest of the output
        fprintf(ofp, "%d given to PERSON %d\n", (raffle->ticketIndex)-1, personNumber);

        // Subtract the cost of tickets from the person's net gain
        personNet[personNumber] -= numSold * raffle->ticketCost;
        return numSold * raffle->ticketCost;
    }
    else
        fprintf(ofp, "NO RAFFLE TICKETS given to PERSON %d\n", personNumber);

    return 0;
}

void awardRaffle(FILE *ofp, raffle_struct* raffle, float personNet[], int item, int ticketNumber){
    int winnerID = raffle->ticketOwner[ticketNumber];
    fprintf(ofp, "RAFFLE %d WON BY PERSON %d\n", item, winnerID);

    // Add the net gain to the person
    personNet[winnerID] += raffle->prizeValue[item];
}

void initilizeArray(int array[], int length, int value){
    int i;
    for(i=0; i<length; i++) //////////////////////////// < or <=? Test with printf("%d", auction.currentWinner[auction.numItems]);
        array[i] = value;
}

void printRevenue(FILE *ofp, float revenue){
    fprintf(ofp, "TOTALREVENUE is $%.2f\n", revenue);
}

void closeAuction(FILE *ofp, auction_struct* auction){
    auction->open = 0;
    fprintf(ofp, "CLOSEAUCTION\n");
}

float buyDrink(FILE *ofp, drink_struct* drinks, int numSold, int drinkNumber){
    // If there aren't enough drinks, just sell what's left.
    if(numSold > drinks->stock[drinkNumber]){
        numSold = drinks->stock[drinkNumber];
        drinks->stock[drinkNumber] = 0;
    }
    else
        drinks->stock[drinkNumber] -= numSold;

    // Print Outputs and return the profit
    if(numSold == 0)
        fprintf(ofp, "NO DRINK %d SOLD\n", drinkNumber);
    else
        fprintf(ofp, "SOLD %d of DRINK %d\n", numSold, drinkNumber);

    return numSold * drinks->price[drinkNumber];
}

void bidItem(FILE *ofp, auction_struct* auction, int itemNum, int personNum, float bidAmount){
    if(auction->open){
        // Reject the bid if it is lower than the last bid or if it isn't raised by at least auction.minBidIncrement
        if(bidAmount<auction->currentBid[itemNum] || (bidAmount - auction->currentBid[itemNum]) < auction->minBidIncrement)
            fprintf(ofp, "BIDITEM %d REJECTED for PERSON %d at %.2f DOLLARS\n", itemNum, personNum, bidAmount);
        else{
            auction->currentBid[itemNum] = bidAmount;
            auction->currentWinner[itemNum] = personNum;
            fprintf(ofp, "BIDITEM %d ACCEPTED for PERSON %d at %.2f DOLLARS\n", itemNum, personNum, bidAmount);
        }
    }
    else
        fprintf(ofp, "BIDITEM %d REJECTED for PERSON %d at %.2f DOLLARS\n", itemNum, personNum, bidAmount);
}

float awardAuction(FILE *ofp, auction_struct* auction, float personNet[], int itemNum){
    fprintf(ofp, "AUCTION ITEM %d WON BY PERSON %d for $%.2f\n", itemNum, auction->currentWinner[itemNum], auction->currentBid[itemNum]);

    // Because they won, give the person a net gain from their prize
    personNet[auction->currentWinner[itemNum]] += auction->itemMarketPrice[itemNum] - auction->currentBid[itemNum];
    // Returns the amount of money gained from the top bid as the profit.
    return auction->currentBid[itemNum];
}

void awardPerson(FILE *ofp, ticket_sales* tickets, float personNet[], int ID){
    // Include their ticket price in the net gain/loss
    // If it was a presale ticket, use that cost. Else use regular cost
    if(ID<tickets->numPresaleTickets)
        personNet[ID] -= tickets->presaleCost;
    else
        personNet[ID] -= tickets->doorCost;

    // Check if the person is up or down, and print the proper result
    if(personNet[ID]>=0)
        fprintf(ofp, "PERSON %d is UP $%.2f\n", ID, personNet[ID]);
    else
        fprintf(ofp, "PERSON %d is DOWN $%.2f\n", ID, fabs(personNet[ID]));
}
