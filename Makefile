build:
	gcc main.c library.c -o lanParty
	./lanParty date/t7/c.in date/t7/d.in r.out
clean:
	rm -f lanParty