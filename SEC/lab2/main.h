#include "curl/curl.h"
#include <curl/easy.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define FORM_FIELD_SIZE 256

char* username = "username=";
char* password = "&password=";
char* challenge = "&challenge=";

const int USERNAME_LEN = 9;
const int PASSWORD_LEN = 10;
const int CHALLENGE_LEN = 11;
const int STARTING_POST_LEN =  USERNAME_LEN + PASSWORD_LEN + CHALLENGE_LEN; 

char* setup_post_field(char*, char*, char*);
