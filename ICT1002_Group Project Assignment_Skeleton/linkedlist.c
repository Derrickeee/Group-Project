#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "chat1002.h"

/* Linked list concept that holds the functions to support knowledge.c
 * The buffer is initialized as a global variable within knowledge.c
 * And every editting is done within the file
 * Methods here involve retrieval only.
*/

/*Use this to check the total structure of the list*/
void printLinkedList(node *head) {
    node *cursor = head;
    int count = 1;
    while (cursor != NULL) {
        printf("Data at node%d is: %s\n", count, cursor->answer);
        cursor = cursor->next;
        count++;
    }

}

/*Always inserts in front. Remember to put head to catch the node pointer from this method.*/
node *insertNode(node *head, const char *intent, const char *entity, const char *answer)
{
    node *newnode = (node *) malloc(sizeof(node));
    if(head != NULL)
    {
        //Check if a node of the same question and type already exist in the buffer
        node *exist = getNode(head, intent, entity);
        if(exist != NULL)
        {
            //Change the existing node's answer (load intent)
            strcpy(exist->answer, answer);
            return head;
        }
        else
        {
            //To end the route and create a new node instead
            newnode->next = head;
            strcpy(newnode->intent, intent);
            strcpy(newnode->entity, entity);
            strcpy(newnode->answer, answer);
            return (newnode);
        }
    }
    else
    {
        //Create a new node and insert into the front
        newnode->next = head;
        strcpy(newnode->intent, intent);
        strcpy(newnode->entity, entity);
        strcpy(newnode->answer, answer);
        return (newnode);
    }
}

/*Get answer based on intent filter and entity filter*/
char *getAnswer(node *head, const char *intent, const char *entity) {
    node *cursor = head;
    if (cursor != NULL) {
        while (cursor != NULL) {
            if (compare_token(intent, cursor->intent) == 0) {
                if (compare_token(entity, cursor->entity) == 0) {
                    return cursor->answer;
                }
            }
            cursor = cursor->next;
        }
    }
    return NULL;
}

//Get existing Node (for insertion and load purposes)
node *getNode(node *head, const char *intent, const char *entity) {
    node *cursor = head;
    if (cursor != NULL) {
        /*To check multiple cursors*/
        while (cursor != NULL) {
            if (compare_token(intent, cursor->intent) == 0) {
                if (compare_token(entity, cursor->entity) == 0) {
                    return cursor;
                }
            }
            cursor = cursor->next;
        }
    }
    return NULL;
}
