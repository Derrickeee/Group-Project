/*
 * ICT1002 (C Language) Group Project.
 *
 * This file implements the behaviour of the chatbot. The main entry point to
 * this module is the chatbot_main() function, which identifies the intent
 * using the chatbot_is_*() functions then invokes the matching chatbot_do_*()
 * function to carry out the intent.
 *
 * chatbot_main() and chatbot_do_*() have the same method signature, which
 * works as described here.
 *
 * Input parameters:
 *   inc      - the number of words in the question
 *   inv      - an array of pointers to each word in the question
 *   response - a buffer to receive the response
 *   n        - the size of the response buffer
 *
 * The first word indicates the intent. If the intent is not recognised, the
 * chatbot should respond with "I do not understand [intent]." or similar, and
 * ignore the rest of the input.
 *
 * If the second word may be a part of speech that makes sense for the intent.
 *    - for WHAT, WHERE and WHO, it may be "is" or "are".
 *    - for SAVE, it may be "as" or "to".
 *    - for LOAD, it may be "from".
 * The word is otherwise ignored and may be omitted.
 *
 * The remainder of the input (including the second word, if it is not one of the
 * above) is the entity.
 *
 * The chatbot's answer should be stored in the output buffer, and be no longer
 * than n characters long (you can use snprintf() to do this). The contents of
 * this buffer will be printed by the main loop.
 *
 * The behaviour of the other functions is described individually in a comment
 * immediately before the function declaration.
 *
 * You can rename the chatbot and the user by changing chatbot_botname() and
 * chatbot_username(), respectively. The main loop will print the strings
 * returned by these functions at the start of each line.
 */

#include <stdio.h>
#include <string.h>
#include "chat1002.h"

#define MAX_REPLIES 5

 // Define the file name so easy to configure in the future (?) Should probably create a config file and pull from there instead
const char* INI_FILE_NAME = "ICT1002_Group Project Assignment_Sample.ini";

// Create the arrays for the predefined trigger keywords and the bot replies
char* USER_GREETINGS[MAX_REPLIES] = {
		"Hello", "Hi", "Greetings", "Sup", "Morning"
};
char* CHATBOT_GREETINGS[MAX_REPLIES] = {
		"Hello", "Hi", "Greetings", "Sup", "What la"
};

/*
 * Get the name of the chatbot.
 *
 * Returns: the name of the chatbot as a null-terminated string
 */
const char *chatbot_botname() {

	return "Catbot";

}


/*
 * Get the name of the user.
 *
 * Returns: the name of the user as a null-terminated string
 */
const char *chatbot_username() {

	return "Kitty";

}


/*
 * Get a response to user input.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop (i.e. it detected the EXIT intent)
 */
int chatbot_main(int inc, char *inv[], char *response, int n) {

	/* check for empty input */
	if (inc < 1) {
		snprintf(response, n, "");
		return 0;
	}

	/* look for an intent and invoke the corresponding do_* function */
	if (chatbot_is_exit(inv[0]))
		return chatbot_do_exit(inc, inv, response, n);
	else if (chatbot_is_smalltalk(inv[0]))
		return chatbot_do_smalltalk(inc, inv, response, n);
	else if (chatbot_is_load(inv[0]))
		return chatbot_do_load(inc, inv, response, n);
	else if (chatbot_is_question(inv[0]))
		return chatbot_do_question(inc, inv, response, n);
	else if (chatbot_is_reset(inv[0]))
		return chatbot_do_reset(inc, inv, response, n);
	else if (chatbot_is_save(inv[0]))
		return chatbot_do_save(inc, inv, response, n);
	else {
		snprintf(response, n, "I don't understand \"%s\".", inv[0]);
		return 0;
	}

}


/*
 * Determine whether an intent is EXIT.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "exit" or "quit"
 *  0, otherwise
 */
int chatbot_is_exit(const char *intent) {

	return compare_token(intent, "exit") == 0 || compare_token(intent, "quit") == 0;

}


/*
 * Perform the EXIT intent.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_exit(int inc, char *inv[], char *response, int n) {

	snprintf(response, n, "Goodbye!");

	return 1;

}


/*
 * Determine whether an intent is LOAD.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "load"
 *  0, otherwise
 */
int chatbot_is_load(const char *intent) {

	/* to be implemented */
    if (compare_token(intent, "load") == 0){   
        return 1;
    }
    
	return 0;

}


/*
 * Load a chatbot's knowledge base from a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after loading knowledge)
 */
int chatbot_do_load(int inc, char *inv[], char *response, int n) {

	/* to be implemented */
    int cmd = 0;
    //check if file provided by user exists
    
    //check if second word is from or not
    if (compare_token(inv[1],"from") == 0){
        cmd = knowledge_read(inv[2]);
        FILE *ptr;
        ptr = fopen(inv[2], "r");
        if (ptr == NULL){
            snprintf(response, n, "File does not exist");
        }
        fclose(ptr);
    }
    else{
        cmd = knowledge_read(inv[1]);
        FILE *ptr;
        ptr = fopen(inv[1], "r");
        if (ptr == NULL){
            snprintf(response, n, "File does not exist");
        }
        fclose(ptr);
    }
    
    if (cmd > 0){
        snprintf(response, n, "Successfully loaded %d pairs", cmd);
    }
	return 0;

}


/*
 * Determine whether an intent is a question.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_question(const char *intent) {
    if (compare_token(intent, "what") == 0 || compare_token(intent, "where") == 0 || compare_token(intent, "who") == 0)
    {
        return 1;
    }
    return 0;
}


/*
 * Answer a question.
 *
 * inv[0] contains the the question word.
 * inv[1] may contain "is" or "are"; if so, it is skipped.
 * The remainder of the words form the entity.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after a question)
 */
int chatbot_do_question(int inc, char *inv[], char *response, int n) {

	//initialise empty string to store entity
    char string[MAX_ENTITY]="\0";
    //check second word inv[1] if == "is" or "are"
    if (compare_token(inv[1], "is") == 0 || compare_token(inv[1], "are") == 0){
        for (int i = 2; i < inc;i++){
            //concatenate the remaining words to form the entity
            strcat(string, inv[i]);
        }
    }
    else{
        for (int i = 1; i < inc;i++){
            //concatenate the remaining words to form the entity
            strcat(string, inv[i]);
        }
    }
    int r = knowledge_get(inv[0], string, response,  n);
    //no response found for the matching intent & entity
    if (r == -1){
        //ask user for input to add to db
        char qns[MAX_ENTITY] ="I don't know. ";
        char space[2] = " ";
        for (int i = 0; i < inc; i++){
            strcat(qns, inv[i]);
            strcat(qns, space);
        }
        prompt_user(response, 255, qns);
        knowledge_put( inv[0], string, response);
        snprintf(response, MAX_RESPONSE, "Thank You");
    }

	return 0;

}


/*
 * Determine whether an intent is RESET.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "reset"
 *  0, otherwise
 */
int chatbot_is_reset(const char *intent) {

	/* to be implemented */
    if (compare_token(intent, "reset") == 0){
        return 1;
    }

	return 0;

}


/*
 * Reset the chatbot.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after beign reset)
 */
int chatbot_do_reset(int inc, char *inv[], char *response, int n) {

	knowledge_reset();
    snprintf(response, n, "Reset successful");

	return 0;

}


/*
 * Determine whether an intent is SAVE.
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is "what", "where", or "who"
 *  0, otherwise
 */
int chatbot_is_save(const char *intent) {

	/* to be implemented */
	if (compare_token(intent, "save") == 0) {
		return 1;
	}
	else {
		return 0;
	}


}


/*
 * Save the chatbot's knowledge to a file.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0 (the chatbot always continues chatting after saving knowledge)
 */
int chatbot_do_save(int inc, char *inv[], char *response, int n) {

	/* to be implemented */
		char * invalidfs = "Please enter a filename in the following format: save to <filename>";
	if (inc < 2) {
		snprintf(response, n, "%s", invalidfs);
		return 0;
	}

	int indx = 1;
	if (compare_token(inv[1], "as") == 0 || compare_token(inv[1], "to") == 0){
		indx = 2;
	}

	if (indx == 2 && inc < 3) {
		snprintf(response, n, "%s", invalidfs);
		return 0;
	}
	
	char * filename = inv[indx];
	if (filename[0] == 0) {
		snprintf(response, n, "%s", invalidfs);
		return 0;
	}
	FILE * file;
	file = fopen(filename, "r");
	if (file != NULL) {
		char ans[3];
		prompt_user(ans, 3, "%s is present. Do you want to overwrite it? [Y/n]", filename);
		fclose(file);

		switch (ans[0]) {
			case 'n':
				snprintf(response, n, "My knowledge is not saved as the file provided exists");
				return 0;
			case 'Y':
				break;
			default:
				snprintf(response, n, "My knowledge is not saved as the file exists and I do not understand the response.");
				return 0;

		}
	}
	file = fopen(filename, "w");
	knowledge_write(file);
	fclose(file);
	
	snprintf(response, n, "My knowledge has been saved to %s", filename);


	return 0;

}


/*
 * Determine which an intent is smalltalk.
 *
 *
 * Input:
 *  intent - the intent
 *
 * Returns:
 *  1, if the intent is the first word of one of the smalltalk phrases
 *  0, otherwise
 */
int chatbot_is_smalltalk(const char *intent) {

	/* to be implemented */
	
// implementation of smalltalk with Profanity Warning
  /* Store the intent from user into an array of pointers*/
	const char *smalltalk[] = {
	            "good", "hello", "hey", "hi", "it", "its", "it's","wassup","sup","yo","fuck","fucking","fucked", "shit", "shitting", "crap", "kanina"
  };
  
	/*Declare length of array*/
  size_t length = sizeof(smalltalk)/sizeof(smalltalk[0]);
	
  /*Create a loop to loop through the array to compare each intent whether 
	is it in smalltalk[]. If yes, return 1*/
	for (int i = 0; i < length; i++) {
		if (compare_token(intent, smalltalk[i]) == 0) {
			return 1;
		}
	}
  
	return 0;

}


/*
 * Respond to smalltalk.
 *
 * See the comment at the top of the file for a description of how this
 * function is used.
 *
 * Returns:
 *   0, if the chatbot should continue chatting
 *   1, if the chatbot should stop chatting (e.g. the smalltalk was "goodbye" etc.)
 */
int chatbot_do_smalltalk(int inc, char *inv[], char *response, int n) {

	/* to be implemented */
/* Create an array of pointers to store all responses to smalltalk */
	const char *random_hi[] = {"Hi!", "Hello!", "Hello there!", "Hey hey~", "What's Up!!"};
	


	if (compare_token("good", inv[0]) == 0) {
		/* Check if the user specify "good" as the first word */
		if (inc > 1) {
      /* If the user specifies something else after "good", the chatbot will copy the word
			after "good" and respond with it */
			snprintf(response, n, "Good %s to you too, Kitty!", inv[1]);
		} else {
      /* If the user only specifies "good", the chatbot will respond with "Good day!" */
			snprintf(response, n, "Good day!");
		}
    
	} else if (compare_token("hello", inv[0]) == 0 || compare_token("hey", inv[0]) == 0 || compare_token("hi", inv[0]) == 0) {
		/* If the user's first word is any of the above, the bot will randomly generate a number
		and retrieve the respond from random_hi array */
		snprintf(response, n, "%s Kitty", random_hi[rand_int]);
    
	} else if (compare_token("it", inv[0]) == 0 || compare_token("its", inv[0]) == 0 || compare_token("it's", inv[0]) == 0) {
		/* If the user first word is any of the above, the bot will respond with "Indeed it is." */
		snprintf(response, n, "Indeed it is.");
    
	} else if (compare_token("fuck", inv[0]) == 0 || compare_token("fucking", inv[0]) == 0 || compare_token("fucked", inv[0]) == 0 || compare_token("shit", inv[0]) == 0 || compare_token("shitting", inv[0]) == 0 || compare_token("crap", inv[0]) == 0 || compare_token("kanina", inv[0]) == 0 ) {
    // Profanity warning from the bot
    snprintf(response, n, "That's not a very nice thing to say!");
	}
  
	return 0;

}
