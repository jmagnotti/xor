#! /usr/bin/env python3.0
import os

files = os.listdir(os.getcwd())
files.sort()
print(files)
i = 0
for f in files:
	name = f.split('.')
	if (len(name) > 1 and name[1] == 'jpg'):
		print("making file: " + str(i) ) 
		os.rename(f, "image"+str(i)+".jpg")
		i = i + 1 
