default: afadv

afadv: afadv.c
	gcc -Wall -O3 -o afadv afadv.c

install: afadv
	cp afadv /usr/bin/afadv
	cp afadv.sh /usr/bin/afadv.sh
	cp afadv16x16.png /usr/share/icons/hicolor/16x16/afadv.png
	cp afadv32x32.png /usr/share/icons/hicolor/32x32/afadv.png
	cp afadv64x64.png /usr/share/icons/hicolor/64x64/afadv.png
	cp afadv.desktop /usr/share/applications/afadv.desktop

zip:	afadv
	zip afadv.zip afadv afadv16x16.png afadv32x32.png afadv64x64.png afadv.desktop LICENSE-2.0.txt README.txt afadv.sh install.sh uninstall.sh
clean:
	$(RM) afadv afadv.zip

distclean: clean
