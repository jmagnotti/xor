#!/bin/bash

# Yet another crazy sed script! :-D

# This one pulls out event methods from KeyboardListener.h
# and generates methods for this demo, storing them
# temporarily in handlecode.cpp.

sed -e 's/\tinline virtual void //' < ../../event/KeyboardListener.h |
sed -e 's/\(\) {}//' | sed -e 's/.*/\tvoid KeyboardDemo::& { cout << "&" << endl; }/' > handlecode.cpp

