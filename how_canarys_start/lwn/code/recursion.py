#! /usr/bin/python
max_wrapper = 10
for i in range(1,max_wrapper):
	open("wrapper%d"%i,'w').write("#! ./wrapper%d -%d\n"%(i-1,i-1))
