from subprocess import call
import os, sys

# Open a file
dirs = os.listdir( "./input/" )
sorts = ['S','B', 'I', 'H', 'R']
comps = [100, 1000, 10000, 100000, 1000000, 10000000]

files = []
# This would print all the files and directories
for file in dirs:
	files.append(file)
for sort in sorts:
	for file in files:
		for i in comps:
			print('Sorting:',sort, file, i)
			name = './sort -a '+ sort + ' -t -f input/' + file + ' -n '+ str(i)
			os.system(name)
			print()
