#!/bin/bash

sed -e 's/\tinline virtual void //' < ../../event/KeyboardListener.h |
sed -e 's/\(\) {}//' | sed -e 's/.*/\tvoid KeyboardDemo::& { cout << "&" << endl; }/' > handlecode.cpp

