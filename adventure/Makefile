default: adventure

adventure: adventure.c
	gcc -Wall -O3 -o adventure adventure.c

clean:
	$(RM) adventure.o adventure

install: adventure
	cp adventure /usr/bin/adventure
	cp adventure16x16.png /usr/share/icons/hicolor/16x16/adventure.png
	cp adventure32x32.png /usr/share/icons/hicolor/32x32/adventure.png
	cp adventure64x64.png /usr/share/icons/hicolor/64x64/adventure.png
	cp adventure.desktop /usr/share/applications/adventure.desktop

distclean: clean
	$(RM) adventure
