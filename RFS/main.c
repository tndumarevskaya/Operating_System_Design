#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main()
{
    int infoOfProcesses[50][5]; // Matrix for storing Process Id, Arrival Time, Burst
    // Time, Average Waiting Time & Average
    // Turn Around Time.
    int i, j, n, total = 0, index, temp;
	int timeOfmoment = 0;
	int isTrue = 1;
    float avg_wt, avg_tat;
    printf("Enter number of process: ");
    scanf("%d", &n);
    printf("Enter Arrival Time:\n");
    // User Input Arrival Time and alloting Process Id.
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &infoOfProcesses[i][1]);
        infoOfProcesses[i][0] = i + 1;
		printf("Enter Burst Time: ");
		 // User Input Burst Time and alloting Process Id.
		 scanf("%d", &infoOfProcesses[i][2]);
    }
	
	 // Sorting process according to their Burst Time.
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++)
            if (infoOfProcesses[j][1] < infoOfProcesses[index][1])
                index = j;
        temp = infoOfProcesses[i][1];
        infoOfProcesses[i][1] = infoOfProcesses[index][1];
        infoOfProcesses[index][1] = temp;

        temp = infoOfProcesses[i][0];
        infoOfProcesses[i][0] = infoOfProcesses[index][0];
        infoOfProcesses[index][0] = temp;

		temp = infoOfProcesses[i][2];
        infoOfProcesses[i][2] = infoOfProcesses[index][2];
        infoOfProcesses[index][2] = temp;
    }
	//Algorithm random first served

	timeOfmoment = infoOfProcesses[0][1];
	for (i = 0; i < n; i++) {
		while (isTrue) {
			index = rand() % (n - i) + i;
			if (infoOfProcesses[index][1] <= timeOfmoment) {
				temp = infoOfProcesses[i][1];
				infoOfProcesses[i][1] = infoOfProcesses[index][1];
				infoOfProcesses[index][1] = temp;

				temp = infoOfProcesses[i][0];
				infoOfProcesses[i][0] = infoOfProcesses[index][0];
				infoOfProcesses[index][0] = temp;

				temp = infoOfProcesses[i][2];
				infoOfProcesses[i][2] = infoOfProcesses[index][2];
				infoOfProcesses[index][2] = temp;

				timeOfmoment += infoOfProcesses[i][2];
				if (infoOfProcesses[i + 1][2] > timeOfmoment) {
					timeOfmoment = infoOfProcesses[i + 1][1];
				}

				isTrue = 0;
			}
		}
		isTrue = 1;
	}

	infoOfProcesses[0][3] = 0;
   // Calculation of Waiting Times
    for (i = 1; i < n; i++) {
        infoOfProcesses[i][3] = 0;
        for (j = 0; j < i; j++)
            infoOfProcesses[i][3] += infoOfProcesses[j][2];
        total += infoOfProcesses[i][3];
    }
	avg_wt = (float)total / n;
    total = 0;
    printf("P	AT	BT	WT	TAT\n");
    // Calculation of Turn Around Time and printing the
    // data.
    for (i = 0; i < n; i++) {
        infoOfProcesses[i][4] = infoOfProcesses[i][2] + infoOfProcesses[i][3];
        total += infoOfProcesses[i][4];
        printf("P%d	%d	%d	%d	%d\n", infoOfProcesses[i][0],
            infoOfProcesses[i][1], infoOfProcesses[i][2], infoOfProcesses[i][3], infoOfProcesses[i][4]);
    }

	avg_tat = (float)total / n;
    printf("Average Waiting Time= %f", avg_wt);
    printf("\nAverage Turn-around-Time= %f", avg_tat);

    return 0;
}
