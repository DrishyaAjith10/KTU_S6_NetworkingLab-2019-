#include <stdio.h>

struct router
{
    unsigned cost[20];
    unsigned from[20];
} routingTable[10];

int main()
{
    int costmat[20][20];

    int routers;
    int i, j, k;

    int otherShorterPathExists;

    printf("Enter the number of routers: ");
    scanf("%d", &routers);

    printf("\nEnter the cost matrix:\n");

    // Input cost matrix
    for (i = 0; i < routers; i++)
    {
        for (j = 0; j < routers; j++)
        {
            scanf("%d", &costmat[i][j]);

            // Distance to itself is always 0
            if (i == j)
            {
                costmat[i][j] = 0;
            }

            // Initial routing table setup
            routingTable[i].cost[j] = costmat[i][j];

            // Initially assume direct path
            routingTable[i].from[j] = j;
        }
    }

    // Distance Vector Algorithm
    do
    {
        otherShorterPathExists = 0;

        for (i = 0; i < routers; i++)
        {
            for (j = 0; j < routers; j++)
            {
                for (k = 0; k < routers; k++)
                {
                    // Check if path through router k is shorter
                    if (routingTable[i].cost[j] >
                        costmat[i][k] + routingTable[k].cost[j])
                    {
                        // Update shorter distance
                        routingTable[i].cost[j] =
                            costmat[i][k] +
                            routingTable[k].cost[j];

                        // Update next hop
                        routingTable[i].from[j] = k;

                        // Another improvement found
                        otherShorterPathExists = 1;
                    }
                }
            }
        }

    } while (otherShorterPathExists);

    // Print routing tables
    for (i = 0; i < routers; i++)
    {
        printf("\n\nRouting Table for Router %d\n", i + 1);

        for (j = 0; j < routers; j++)
        {
            printf("To Router %d via Router %d -> Distance = %d\n",
                   j + 1,
                   routingTable[i].from[j] + 1,
                   routingTable[i].cost[j]);
        }
    }

    printf("\n");

    return 0;
}