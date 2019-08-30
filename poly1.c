#include<stdio.h>
  #include<stdlib.h>

  struct pNode {
        int coeff, exp;
        struct pNode *next;
  };

  struct pNode *head1, *head2, *head3;

  /*
   * creates new Node and fill the given data
   */
  struct pNode * createNode(int coeff, int exp) {
        struct pNode *ptr;
        ptr = (struct pNode *) malloc(sizeof (struct pNode));
        ptr->coeff = coeff;
        ptr->exp = exp;
        ptr->next = NULL;
        return ptr;
  }

  /* insert data in decending order */
  void polyInsert(struct pNode ** myNode, int coeff, int exp) {
        struct pNode *xPtr, *yPtr, *zPtr = *myNode;
        xPtr = createNode(coeff, exp);
        /* if exp > exp in header then the new node is the header */
        if (*myNode == NULL || (*myNode)->exp < exp) {
                *myNode = xPtr;
                (*myNode)->next = zPtr;
                return;
        }
        /* placing new node in correct position - decending order */
        while (zPtr) {
                yPtr = zPtr;
                zPtr = zPtr->next;
                if (!zPtr) {
                        yPtr->next = xPtr;
                        break;
                } else if ((exp < yPtr->exp) && (exp > zPtr->exp)) {
                        xPtr->next = zPtr;
                        yPtr->next = xPtr;
                        break;
                }
        }
        return;
  }

  /* Adding poly nomial n2 and n3 and the output will be stroed in n1 list */
  void polynomial_add(struct pNode **n1, struct pNode *n2, struct pNode *n3) {
        struct pNode * temp;
        /* if both list not exit, then output list *n1 is NULL */
        if (!n2 && !n3)
                return;
        /* both list are present */
        while (n2 && n3) {
                if (*n1 == NULL) {
                        *n1 = (struct pNode *) malloc(sizeof (struct pNode));
                        temp = *n1;
                } else {
                        temp->next = (struct pNode *)malloc(sizeof (struct pNode));
                        temp = temp->next;
                }
                /* polynomial addition operation */
                if (n2->exp < n3->exp) {
                        temp->coeff = n3->coeff;
                        temp->exp = n3->exp;
                        n3 = n3->next;
                } else if (n2->exp > n3->exp) {
                        temp->coeff = n2->coeff;
                        temp->exp = n2->exp;
                        n2 = n2->next;
                } else {
                        temp->coeff = n2->coeff + n3->coeff;
                        temp->exp =  n2->exp;
                        n2 = n2->next;
                        n3 = n3->next;
                }
        }
        /*
         * if some nodes in input list (n2) left remain, then add those
         *  nodes to the output list (n3).
         */
        while (n2) {
                if (*n1 == NULL) {
                        *n1 = (struct pNode *) malloc(sizeof (struct pNode));
                        temp = *n1;
                } else {
                        temp->next = (struct pNode *) malloc(sizeof (struct pNode));
                        temp = temp->next;
                }
                temp->coeff = n2->coeff;
                temp->exp = n2->exp;
                n2 = n2->next;
        }

        /*
         * if some nodes in the input list (n3) left remain, then add those
         * nodes to the output list n3.
         */
        while (n3) {
                if (*n1 == NULL) {
                        *n1 = (struct pNode *) malloc(sizeof (struct pNode));
                        temp = *n1;
                } else {
                        temp->next = (struct pNode *) malloc(sizeof (struct pNode));
                        temp = temp->next;
                }
                temp->coeff = n2->coeff;
                temp->exp = n2->exp;
                n3 = n3->next;
        }
        return;
  }

  /* delete the given input list */
  struct pNode * deletePolyList(struct pNode *ptr) {
        struct pNode *temp;
        while (ptr){
                temp = ptr->next;
                free(ptr);
                ptr = temp;
        }
        return NULL;
  }

  /* traverse the given input list and print the data in each node */
  void walkPolyList(struct pNode *ptr) {
        int i = 0;
        while (ptr) {
                printf("%dX^%d %c ", ptr->coeff, ptr->exp, ptr->next?'+':'\0');
                ptr = ptr->next;
                i++;
        }
        printf("\n");
        return;
  }

  int main (int argc, char *argv[]) {
        int coeff, exp, i, n;
        FILE *fp1, *fp2;
        fp1 = fopen(argv[1], "r");
        fp2 = fopen(argv[2], "r");
        if (!fp1 || !fp2) {
                printf("Unable to open file\n");
                fcloseall();
                exit(0);
        }
        /* reading co-efficient and exponent from the file argv[1] */
        while (fscanf(fp1, "%d%d", &coeff, &exp) != EOF) {
                polyInsert(&head1, coeff, exp);
        }
        /* reading co-efficient and exponent from the input file argv[2] */
        while (fscanf(fp2, "%d%d", &coeff, &exp) != EOF) {
                polyInsert(&head2, coeff, exp);
        }
        walkPolyList(head1);
        walkPolyList(head2);
        polynomial_add(&head3, head1, head2);
        walkPolyList(head3);
        head1 = deletePolyList(head1);
        head2 = deletePolyList(head2);
        head3 = deletePolyList(head3);
        return 0;
  }
 
 First column in input files represent co-efficient and the second column represents exponents.


Output: (Polynomial Addition Using Linked List Example (in C))
  6 5
  7 4
  8 2

  7 5
  3 4
  5 3
