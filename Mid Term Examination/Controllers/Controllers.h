#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Models/Models.h"

Node *createNode(Patient patient) {
    Node *temp = (Node *)malloc(sizeof(Node));

    strcpy(temp->patient.name, patient.name);
    temp->next = temp->prev = NULL;
    char month[25];
    int idx = 0, flag = 0, dayLen = 0;
    for (int i = 0; i < strlen(patient.DOB); i++) {
        if (patient.DOB[i] == ' ') {
            flag = !flag;
            if (i < 2) {
                dayLen++;
            }
            continue;
        }

        if (flag) {
            month[idx] = patient.DOB[i];
            idx++;
        }
    }

    
    char months[12][25] = {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", 
                            "december"};
    
    char day[3];
    for (int i = 0; i < dayLen; i++) {
        day[i] = patient.DOB[i];
    }

    for (int i = 0; i < 12; i++) {
        if (strcmp(month, months[i]) == 0) {
            temp->patient.month = i + 1;
            break;
        }
    }

    if (dayLen == 2) {
        temp->patient.day = (day[0] - '0') * 10;
        temp->patient.day += day[1] - '0';
    } else {
        temp->patient.day = day[0] - '0';
    }

    int yearLen = 0;
    for (int i = strlen(patient.DOB) - 1; i >= strlen(patient.DOB) - 5; i--) {
        if (patient.DOB[i] == ' ') {
            break;
        } else {
            yearLen++;
        }
    } 

    char year[5];
    idx = 0;
    for (int i = yearLen; i >= 0; i--) {
        year[idx] = patient.DOB[i];
        idx++;
    }

    int multiply = 1000;
    temp->patient.year = 0;
    for (int i = 0; i < yearLen; i++) {
        temp->patient.year += (year[i] - '0') * multiply;
        multiply /= 10; 
    } 

    return temp;
}

void popHead() {
    if (head && head == tail) {
        head = tail = NULL;
        free(head);
    } else {
        Node *newHead = head->next;
        head->next = newHead->prev = NULL;
        free(head);
        head = newHead;
    }
}

void pushHead(Patient p) {
    Node *temp = createNode(p);

    if (!head) {
        head = tail = temp;
    } else {
        head->prev = temp;
        temp->next = head;
        head = temp;
    }
}

void pushTail (Patient p) {
    Node * temp = createNode(p);

    if (!head) {
        head = tail = temp;
    } else {
        temp->next = temp;
        temp->prev = tail;
        tail = temp;
    }
}

void pushMid(Patient p){
    Node *temp = createNode(p);
    
    puts("");
    if (!head) {
        head = tail = temp;
    } else if (head->patient.year > p.year) {
        pushHead(p);
    } else if (tail->patient.year < p.year) {
        pushTail(p);
    } else {
        curr = head;
        while (curr && curr->patient.year < temp->patient.year) {
            curr = curr->next;
        }  
        
        if (curr && curr->patient.year == temp->patient.year) {
            while (curr && curr->patient.month < temp->patient.month) {
                curr = curr->next;
            }

            if (curr && curr->patient.month == temp->patient.month) {
                while (curr && curr->patient.day < temp->patient.day) {
                    curr = curr->next;
                }   

                curr = curr->prev;
                temp->next = curr->next;
                curr->next->prev = temp;
                curr->next = temp;
                temp->prev = curr;
            } else {
                curr = curr->prev;
                temp->next = curr->next;
                curr->next->prev = temp;
                curr->next = temp;
                temp->prev = curr;
            }
        } else {
            curr = curr->prev;
            temp->next = curr->next;
            curr->next->prev = temp;
            curr->next = temp;
            temp->prev = curr;

        }
    }
}
