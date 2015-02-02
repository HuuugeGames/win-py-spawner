# win-py-spawner
Simple, minimalistic exe that runs sibling py script for windows.

## Story

Starting process on Windows is slow: http://stackoverflow.com/questions/47845/why-is-creating-a-new-process-more-expensive-on-windows-than-linux

Some scripts that work (acceptably) well in Unix-like system are really slow on windows.
Some of them are python scripts evecuted via:

   #!/usr/bin/env python

Which in some cases evaluates to 3 processes:

* sh
* env
* final python

This script allows you directly execute python.

Usage:

    $ ls -
    win-py-spawner.exe # this program
    foo.py             # the script
    $ cp win-py-spawner.exe foo.exe
    $ ./foo.exe          # loads python runtime and executes foo.py directly withing sheband/usr/bin env etc.

## Why

Yes, it saves only < 10% of real time. But that may be enough in some cases.

May be usable also if you have "editor" written in python and need Windows easily associate some filetype with this editor. 
At least on old windowses you could associate document only with EXE files.
