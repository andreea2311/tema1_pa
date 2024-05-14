build:
	gcc main.c library.c -o lanParty
	./lanParty date/t1/c.in date/t1/d.in r.out
clean:
	rm -f lanParty