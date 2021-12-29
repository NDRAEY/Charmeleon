def reformat(dat): # just align to 8
    work = dat[2:] # without '0b'
    ln = len(work) # length
    return ("0"*(8-ln))+work # returning without '0b'

def read_8_8(data): # just read 16 bytes, decode into binary
    r = data.read(16)
    return [reformat(bin(int(n))) for n in r]

def normview(data): # just print the char(acter) of font (debug)
    dat = '\n'.join(data)
    dat = dat.replace("0"," ")
    dat = dat.replace("1","\u2588") # it's the full block character
    return dat

if __name__=="__main__":
    fp = open("IBM_VGA_8x16.bin","rb")
    size = len(fp.read())
    fp.seek(0)
    print("#include \"font.h\"\nchar* getfont(){\n\tconst char font[%d*16] = {"%size)
    for i in range(size//16):
        dt = read_8_8(fp)
        for j in dt:
            print(','.join(j)+",")
        print("\n")
    print("\t};\n\treturn (char*)(&font);\n}")
