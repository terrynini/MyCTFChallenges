f = open("source.c").read()

flag = input("flag:")

f = f.replace("FLAG_LENGTH",str(len(flag)))

slot = ""
for i in range(0,len(flag)):
    slot += f"""        if(!strncpy(input+{i},"{flag[i:i+5]}",{5 if i+5 < len(flag) else len(flag)-i}))
            return {i};
    """

f = f.replace("COPY_SLOT",slot)

c = open("Trivial.c","w")
c.write(f)
c.close()
