//Jeremy Thorne - Average Calculator
//This project gets input for multiple assignments and labs and returns your average along with a few other numbers
//moss is the anti cheat software at uofg if you were wondering

#include <stdio.h>

int main()
{

    //all the input vars
    double weeklyLabMark;
    double dailyPracticeMark;
    double lab1Mark;
    double lab2Mark;
    double assignment1Mark;
    double assignment2Mark;
    double assignment3Mark;
    double goalMark;
    int moss1;
    int moss2;
    int moss3;

    //mark weight vars
    double weeklyLabWeight;
    weeklyLabWeight  = 0.1;
    double dailyPracticeWeight;
    dailyPracticeWeight = 0.1;
    double lab1Weight;
    lab1Weight = 0.1;
    double lab2Weight;
    lab2Weight = 0.1;
    double assignment1Weight;
    assignment1Weight = 0.05;
    double assignment2Weight;
    assignment2Weight = 0.1;
    double assignment3Weight;
    assignment3Weight = 0.1;
    double finalWeight;
    finalWeight = 0.35;

    //other vars
    int labBonus;
    double marksTotal;
    double examMarkNeeded;
    int examMarkNeededPercent;

    //getting all the inputs for the program
    printf("Enter the following marks (0 - 100 percent)\n");

    printf("Weekly Labs: ");
    scanf("%lf", &weeklyLabMark);

    printf("Daily Practice: ");
    scanf("%lf", &dailyPracticeMark);

    printf("Lab Exam I: ");
    scanf("%lf", &lab1Mark);

    printf("Lab Exam II: ");
    scanf("%lf", &lab2Mark);

    printf("Assignment 1: ");
    scanf("%lf", &assignment1Mark);

    printf("MOSS output for A1 (0 / 1): ");
    scanf("%d", &moss1);

    printf("Assignment 2: ");
    scanf("%lf", &assignment2Mark);

    printf("MOSS output for A2 (0 / 1): ");
    scanf("%d", &moss2);

    printf("Assignment 3: ");
    scanf("%lf", &assignment3Mark);

    printf("MOSS output for A3 (0 / 1): ");
    scanf("%d", &moss3);

    printf("\n\n");
    printf("How much do you desire as an overall course grade: ");
    scanf("%lf", &goalMark);

    //if statement checking if the student gets the bonus marks
    if((lab1Mark == 100) && (lab2Mark == 100))
    {
        labBonus = 3;
    }

    //changing assignment marks based on moss outputs (if moss = 0 then the grade will = 0)
    assignment1Mark *= moss1;
    assignment2Mark *= moss2;
    assignment3Mark *= moss3;

    //calculating average
    //I split up the adding of the marks to make it look better
    marksTotal = (weeklyLabMark * weeklyLabWeight) + (dailyPracticeMark * dailyPracticeWeight);
    marksTotal += (lab1Mark * lab1Weight) + (lab2Mark * lab2Weight) + (assignment1Mark * assignment1Weight);
    marksTotal += (assignment2Mark * assignment2Weight) + (assignment3Mark * assignment3Weight) + labBonus;

    //calculating what is needed on the final
    examMarkNeeded = goalMark - marksTotal;

    //getting the percent needed by dividing mark needed by exam weight and adding one to round up always
    examMarkNeededPercent = examMarkNeeded / finalWeight;

    //checks if the student got all 0's on MOSS to see what to output
    if(moss1 == 0 && moss2 == 0 && moss3 == 0)
    {
        //output if cheating
        printf("***********************************************************\n");
        printf("You cannot pass the course - try harder next time\n");
        printf("***********************************************************\n");
    }
    else
    {
        //output for the program if not cheating  
        printf("************************************************************\n");
        printf("Assessment             Weight             Marks\n");
        printf("------------------------------------------------------------\n");
        printf("Weekly Labs            %0.0lf\t %15.2lf\n", weeklyLabWeight * 100, weeklyLabMark);
        printf("Daily Practice         %0.0lf\t %15.2lf\n", dailyPracticeWeight * 100, dailyPracticeMark);
        printf("Lab Exam I 	       %0.0lf\t %15.2lf\n", lab1Weight * 100, lab1Mark);
        printf("Lab Exam II	       %0.0lf\t %15.2lf\n", lab2Weight * 100, lab2Mark);
        printf("Bonus from lab exams:\t\t\t       %d\n", labBonus);
        printf("Assignment 1	       %0.0lf\t %15.2lf\n", assignment1Weight * 100, assignment1Mark);
        printf("Assignment 2	       %0.0lf\t %15.2lf\n", assignment2Weight * 100, assignment2Mark);
        printf("Assignment 3	       %0.0lf\t %15.2lf\n", assignment3Weight * 100, assignment3Mark);
        printf("Final Exam	       %0.0lf\t      To be determined\n\n", finalWeight * 100);
        printf("************************************************************\n\n");
        printf("Current course mark = %0.2lf / 65.00\n", marksTotal);
        printf("You need %0.2lf / 35.00 to reach your goal (%0.0lf)\n", examMarkNeeded, goalMark);
        printf("In percentage, you need %d %% to reach your goal (%0.0lf)\n", examMarkNeededPercent, goalMark);
        printf("************************************************************\n");

    }
    return 0;
}
