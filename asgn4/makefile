all : protectfile setkey

protectfile: protectfile.c
	cc protectfile.c rijndael.c -o protectfile

setkey: setkey.c
	cc setkey.c -o setkey

clean:
	rm protectfile setkey
