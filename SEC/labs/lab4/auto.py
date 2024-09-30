# importing the requests library
import requests
  
# post a request and return the status code
def post_request(URL, PARAMS):
    try:
        # sending get request and saving the response as response object
        r = requests.post(url = URL, data = PARAMS)
        return r.text #r.status_code 
    except:
        return "ERROR"


def check(xss): 
    URL = "http://127.0.0.1:3000/challenge/1"
    PARAMS = {"input": xss}
    result = post_request(URL,PARAMS)
    if result.find('xss'):
        print(result)
#        print("found")
    


def main():
    xss = check('<script>aa</script>')
    
if __name__ == "__main__":
    main()
