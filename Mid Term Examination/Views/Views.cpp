#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Controllers/Controllers.h"

int checkLeft(void) {
    curr = head;
    int count = 0;
    while (curr) {
        curr = curr->next;
        count++;
    }
    return count;
}

void printEnd(int left) {
    printf("Need %d more cure\n", left);
    curr = head;
    while (curr) {
        printf("%s %s\n", curr->patient.DOB, curr->patient.name);
    }
}

void getPatients(void) {
    int patientCount, medCount;
    scanf("%d %d", &patientCount, &medCount);

    char DOB[50], name[105];
    for (int i = 0; i < patientCount; i++) {
        getchar();
        scanf("%[^-]- %[^\n]", DOB, name);
        Patient temp;
        strcpy(temp.DOB, DOB);
        strcpy(temp.name, name);
        pushMid(temp);
        // curr = head;
        // while (curr) {
        //     printf("%s %s\n", curr->patient.DOB, curr->patient.name);
        //     curr = curr->next;
        // }
    }

    for (int i = 0; i < medCount; i++) {
        popHead();
    }

    int left = checkLeft();
    printEnd(left);
}

int main(void) {
    getPatients();    
    return 0;
}