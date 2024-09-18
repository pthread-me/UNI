#include "main.h"

#define CHALLENGE 1 // change to solve diff questions ig

int main(){

	char* username = calloc(1, sizeof(FORM_FIELD_SIZE));
	char* password = calloc(1, sizeof(FORM_FIELD_SIZE));
	char* challenge = calloc(1, sizeof(char));

	CURL* curl = curl_easy_init();
	if(curl == NULL){
		printf("err");
		exit(-64);
	}

	char* post_data = setup_post_field("111111111a", "aaaaaaaaaab", "1vvvvvvv2");

	curl_easy_setopt(curl, CURLOPT_URL,  "http://localhost:5000");
	curl_easy_setopt(curl, CURLOPT_COPYPOSTFIELDS, post_data);
	curl_easy_perform(curl);

}



char* setup_post_field(char* user, char* pass, char* c){
	int string_index = 0; 
	int user_len = strlen(user);
	int pass_len = strlen(pass);
	int c_len = strlen(c);

	// +1 for the \0
	int total_len = STARTING_POST_LEN + user_len + pass_len + c_len + 1; 
	char* post_data = calloc(1, total_len);
	
	memcpy(&post_data[string_index], username, USERNAME_LEN);
		string_index+=USERNAME_LEN;
	memcpy(&post_data[string_index], user, user_len);
		string_index+=user_len;
	memcpy(&post_data[string_index], password, PASSWORD_LEN);
		string_index+=PASSWORD_LEN;
	memcpy(&post_data[string_index], pass, pass_len);
		string_index+=pass_len;
	memcpy(&post_data[string_index], challenge, CHALLENGE_LEN);
		string_index+= CHALLENGE_LEN;
	memcpy(&post_data[string_index], c, c_len);
		string_index+= c_len;

	post_data[string_index +1] = '\0';

	return post_data;
}


