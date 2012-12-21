default: adventure

adventure: adventure.c
	gcc -Wall -O3 -o adventure adventure.c

install: adventure
	cp adventure /usr/bin/adventure
	cp adventure.sh /usr/bin/adventure.sh
	cp adventure16x16.png /usr/share/icons/hicolor/16x16/adventure.png
	cp adventure32x32.png /usr/share/icons/hicolor/32x32/adventure.png
	cp adventure64x64.png /usr/share/icons/hicolor/64x64/adventure.png
	cp adventure.desktop /usr/share/applications/adventure.desktop

zip:	adventure
	zip adventure.zip adventure adventure16x16.png adventure32x32.png adventure64x64.png adventure.desktop LICENSE-2.0.txt README.txt adventure.sh install.sh uninstall.sh
clean:
	$(RM) adventure adventure.zip

distclean: clean
