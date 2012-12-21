default: adventure

adventure: adventure.c
	gcc -Wall -O3 -o adventure adventure.c

clean:
	$(RM) adventure.o adventure

install: adventure
	cp adventure /usr/bin/adventure
	cp adventure.png /usr/share/app-install/icons/adventure.png
	cp adventure.desktop /usr/share/applications/adventure.desktop

distclean: clean
	$(RM) adventure
