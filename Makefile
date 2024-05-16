build:
	gcc main.c library.c -o lanParty
	./lanParty date/t4/c.in date/t4/d.in r.out
clean:
	rm -f lanParty