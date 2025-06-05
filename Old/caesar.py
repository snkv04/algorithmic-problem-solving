def caesar(text, key):
    # only deals with capital letters
    # key can also be negative for left rotations
    letters = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
        "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", 
        "U", "V", "W", "X", "Y", "Z"]
    encrypted = ""
    for character in text:
        if character == " ":
            encrypted += " "
        else:
            index = letters.index(character)
            encrypted += letters[(index + key) % 26]
    return encrypted

# print(caesar("WTGT XH PCDIWTG BTHHPVT IWPI NDJ HWDJAS WPKT CD IGDJQAT QGTPZXCV LXIW ATIITG UGTFJTCRN PCPANHXH", -15))
# for i in range(26):
#     print(caesar("BGDTCU BCEJ AAAAAA BCXKGT AAAAAA CPF BCPG BQQOGF VJTQWIJ VJG BQQ",i), f"key={i}")
print(caesar("BGDTCU BCEJ BCXKGT CPF BCPG BQQOGF VJTQWIJ VJG BQQ", -2))

def wtf(plaintext, key):
    letters = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J",
        "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", 
        "U", "V", "W", "X", "Y", "Z"]
    for char in plaintext:
        if char == " ":
            continue
        index = letters.index(char)
        string = char
        for i in range(1,key+1):
            string += " ⇒ " + letters[(index-i) % 26]
        print(string)
# wtf("JUST ANOTHER RANDOM MESSAGE TO ENCRYPT", 6)