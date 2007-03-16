# !/bin/bash

ln -sf Makefile.unix Makefile
cd src/demo && ln -sf Makefile.unix Makefile
cd ../.. && java makehelp.Make

