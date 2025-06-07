import random

result = ""
for i in range(1000):
    if(random.random() < 0.5):
        result += "G"
    else:
        result += "H"

myfile = open("generated.txt", "w")
myfile.write(result)