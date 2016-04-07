#!/usr/bin/python
## get subprocess module 
import locale
import time

## call date command ##
 
## Talk with date command i.e. read data from stdout and stderr. Store this info in tuple ##
##Interact with process: Send data to stdin. Read data from stdout and stderr, until end-of-file is reached. Wait for process to terminate. The optional input argument should be a string to be sent to the child process, or None, if no data should be sent to the child.
#(output, err) = p.communicate()
 
## Wait for date to terminate. Get return returncode ##
#p_status = p.wait()

def get_macs():
	with open('mac.txt', 'r') as inf:
		macs = inf.read().split()
		return macs

def write_macs(macs):
	with open('mac.txt', 'w') as outf:
		outf.write('\n'.join(macs))

def add_mac(mac):
	with open('mac.txt', 'a') as outf:
		outf.write('\n' + mac)

import time

def program():
	i = 0
	oldColumns = []
	while i < 100:
		encoding = locale.getdefaultlocale()[1] 
		newColumns = []
		print(i + 1)
		import subprocess
		p3 = subprocess.Popen(['runas', '/noprofile', '/user:Administrator', "arp -d *"], stdout=subprocess.PIPE, shell=False)

		# p3 = subprocess.Popen("arp -d *", stdout=subprocess.PIPE, shell=False)
		p3.wait()
		# p = subprocess.Popen("arp -a -v", stdout=subprocess.PIPE, shell=False)
		# for line in p.stdout:
		# 	columns = line.decode(encoding).split()
		# 	if columns:
		# 		for colm in columns:
		# 			if colm == "invalid":
		# 				print "ping ", columns[0]
		# 				p2 = subprocess.Popen("ping " + columns[0], stdout=subprocess.PIPE, shell=False)
		# 				p2.wait()

		p = subprocess.Popen("arp -a", stdout=subprocess.PIPE, shell=False)
		p.wait()
		for line in p.stdout:
			columns = line.decode(encoding).split()
			newColumns = [x for x in columns if len(x) == 17]
			# if columns:
			# 	for colm in columns:
			# 		if len(colm) == 17:
			# 			newColumns.append(colm)
			# 			print "The current macs on network: " + colm

		print newColumns
		#scrie noile macuri
		write_macs(newColumns)

		if len(oldColumns) == 0:
			oldColumns = newColumns
		else:
			for myColumn in oldColumns:
				testing = 0
				for mySecondColumn in newColumns:
					if myColumn == mySecondColumn:
						testing = 1
						break
				if testing == 0:
					print 'Not found: ', myColumn
					#adauga macul in lista
					add_mac(myColumn)
		print 'My old macs: ', oldColumns
		oldColumns = get_macs()
		print 'My new macs: ', oldColumns
		# print oldColumns
		p.wait()
		i+=1
		time.sleep(3)

program()
# oldColumns = ['asd', '123', '234']
# newColumns = ['asd', '1232', '2343']
# oldColumns += newColumns
# oldColumns = {x for x in oldColumns + newColumns}
# print set(oldColumns)
# write_macs(['asda-sd', '2wq-e', 'ew-rq'])
# add_mac('231213-asddsa')
# get_macs()
