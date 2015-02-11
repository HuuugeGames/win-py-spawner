#
# yeah, rlyy simple for now
#
# mingw | native python
#CXXFLAGS= -Ic:/Python27/include
#LDLIBS=-Lc:/Python27/libs -lpython27

# cygwin / unix
CXXFLAGS= -I/usr/include/python2.7
LDLIBS= -lpython2.7

win-py-spawner.exe: win-py-spawner.o readme.o
	$(CXX) $^ -o $@ $(LDFLAGS) $(LDLIBS)

readme.c: README.md
	echo "const char* readme = " > $@
	sed -e 's/"/\\"/g' -e 's/$$/\\n"/' -e 's/^/"/' $< >> $@
	echo ";" >> $@

clean:
	rm -rf win-py-spawner.exe win-py-spawner.o
