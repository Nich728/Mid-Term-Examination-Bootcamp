struct Patient {
    char DOB[25];
    char name[105];
    int day;
    int month;
    int year;
};

struct Node {
    Patient patient;
    Node *prev, *next;

} *head, *tail, *curr;