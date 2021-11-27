/*
 * ICT1002 (C Language) Group Project.
 *
 * This file implements the chatbot's knowledge base.
 *
 * knowledge_get() retrieves the response to a question.
 * knowledge_put() inserts a new response to a question.
 * knowledge_read() reads the knowledge base from a file.
 * knowledge_reset() erases all of the knowledge.
 * knowledge_write() saves the knowledge base in a file.
 *
 * You may add helper functions as necessary.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "chat1002.h"
#include "minIni.h"


/*
 * Get the response to a question.
 *
 * Input:
 *   intent   - the question word
 *   entity   - the entity
 *   response - a buffer to receive the response
 *   n        - the maximum number of characters to write to the response buffer
 *
 * Returns:
 *   KB_OK(0), if a response was found for the intent and entity (the response is copied to the response buffer)
 *   KB_NOTFOUND(-1), if no response could be found
 *   KB_INVALID(-2), if 'intent' is not a recognised question word
 */
int knowledge_get(const char *intent, const char *entity, char *response, int n) {
    char buff[256];

    ini_gets(intent, entity, 0, response, 255, "data.ini");
    if (compare_token(response, "") == 0){
        return KB_NOTFOUND;
    }
    else {
        return KB_OK;
    }


}


/*
 * Insert a new response to a question. If a response already exists for the
 * given intent and entity, it will be overwritten. Otherwise, it will be added
 * to the knowledge base.
 *
 * Input:
 *   intent    - the question word
 *   entity    - the entity
 *   response  - the response for this question and entity
 *
 * Returns:
 *   KB_OK, if successful
 *   KB_NOMEM, if there was a memory allocation failure
 *   KB_INVALID, if the intent is not a valid question word
 */
int knowledge_put(const char *intent, const char *entity, const char *response) {
    int success;
	//add to data.ini
    success = ini_puts( intent, entity, response, "data.ini");
    if (success == 0){
        return KB_INVALID;
    }

	return KB_OK;

}


/*
 * Read a knowledge base from a file.
 *
 * Input:
 *   f - the file
 *
 * Returns: the number of entity/response pairs successful read from the file
 */
int knowledge_read(const char *filename) {
    char section[32];
    char key[64];
    char response[255];
    int pairs = 0;
    int success;
 
    //loop through sections
    for (int s = 0; ini_getsection(s, section, sizeof(section), filename); s++){
        //check is section is vaild
        if (compare_token(section, "What") == 0 || compare_token(section, "Where") == 0 || compare_token(section, "Who") == 0){
            //loop through keywords
            for (int k = 0; ini_getkey(section, k, key, sizeof(key), filename); k++){
                //get response value
                ini_gets(section, key, 0, response, sizeof(response), filename);
                //add response to data.ini
                success = ini_puts(section, key, response, "data.ini");
                //if successful, add pairs
                if (success == 1){
                    pairs++;
                }
            }
        }
    }
	return pairs;
}


/*
 * Reset the knowledge base, removing all know entitities from all intents.
 */
void knowledge_reset() {
    FILE *data;
    FILE *backup;
    char *buffer;
    int length;

    data = fopen("data.ini", "w");
    backup = fopen("databackup.ini", "r");
    //save backup contents
    fseek (backup, 0, SEEK_END);
    length = ftell (backup);
    fseek (backup, 0, SEEK_SET);
    buffer = malloc (length);
    if (buffer)
    {
        fread (buffer, 1, length, backup);
    }
    fclose (backup);
    //paste to data file
    fwrite(buffer, length, 1, data);
    fclose(data);
}


typedef struct node {
	char entity[MAX_ENTITY];
	char response[MAX_RESPONSE];
	struct node *next;
} NODE;

typedef NODE * ptr;

ptr what_head = NULL;
ptr where_head = NULL;
ptr who_head = NULL;

/*
 * Write the knowledge base to a file.
 *
 * Input:
 *   f - the file
 */
void knowledge_write(FILE *f){

    // Writes 'what' linked list into the file
	ptr pointer = what_head;
    fprintf(f, "[WHAT]\n");
    while(pointer != NULL) {
        fprintf(f,"%s=%s\n", pointer->entity, pointer->response);
        pointer = pointer->next;
    }

	// Writes 'where' linked list into the file
	pointer = where_head;
	fprintf(f, "\n[WHERE]\n");
    while(pointer != NULL) {
        fprintf(f,"%s=%s\n", pointer->entity, pointer->response);
        pointer = pointer->next;
    }

	// Writes 'who' linked list into the file
	pointer = who_head;
	fprintf(f, "\n[WHO]\n");
    while(pointer != NULL) {
        fprintf(f,"%s=%s\n", pointer->entity, pointer->response);
        pointer = pointer->next;
    }
}
