# importing the requests library
import requests
  
# post a request and return the status code
def post_request(URL, PARAMS):
    try:
        # sending get request and saving the response as response object
        r = requests.post(url = URL, data = PARAMS)
        return r.status_code 
    except:
        return "ERROR"


def main():
    # define api-endpoint
    URL = "http:localhost:5000"
      
    # defining a params dict for the parameters to be sent to the API
    PARAMS = {"Username": "luv", "Password": "123"}
      
    # Create logic for trying different passwords
    

    # Check status of the current attempt
    print(post_request(URL, PARAMS))

if __name__ == "__main__":
    main()
