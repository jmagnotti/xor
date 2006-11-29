#!/bin/bash

find . -name "*.cpp" | sed -e :a -e '/$/N; s/\n.*demo.*//g; ta' | sed -e :a -e '/$/N; s/\n/ /g; ta' | sed -e 's/\.\///g'

