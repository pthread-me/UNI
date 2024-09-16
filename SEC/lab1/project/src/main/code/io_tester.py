import hashlib

def input_parser(func):
    path = ""
    while True:
        try:
            i = input()
            p_path = func(i)
            if(not p_path == ""): path = p_path
        except EOFError:
                return path

def process_input(s):
    project_path = ""
    if("full path" in s):
        print(s)
        name, path = s.strip().split(":")
        path = path.split("/")
        idx = 0
        for i in range(len(path)-1):
            if(path[i] == "project" and path[i+1] == "src"):
                idx = i
                break
        project_path = "/".join(path[idx:])
        print("current project path: " + project_path)
    else: print(s)
    return project_path

path = input_parser(process_input)
m = hashlib.sha256()
m.update(path.encode("utf-8"))
m.digest()

print("Path Hash: " + m.hexdigest())

