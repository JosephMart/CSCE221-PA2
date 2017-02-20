from subprocess import call
import os, sys

# Open a file
dirs = os.listdir( "./input/" )
sorts = ['S', 'I', 'H']
comps = [10]

files = []
# This would print all the files and directories
for file in dirs:
	files.append(file)
for sort in sorts:
	for file in files:
		for i in comps:
			print('Sorting:',sort, file, i)
			name = './sort -c -a '+ sort + ' -t -f input/' + file + ' -n '+ str(i)
			os.system(name)
			print()
