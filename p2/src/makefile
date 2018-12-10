default:clean all


clean: 
	rm -rfv /usr/src/servers/is/proto.h
	rm -rfv /usr/src/minix/kernel/proc.h 
	rm -rfv /usr/src/minix/servers/is/dmp.c 
	rm -rfv /usr/src/minix/servers/is/dmp_kernel.c

all:
	cp -fv src/dmp.c /usr/src/minix/servers/is/dmp.c
	cp -fv src/dmp_pm.c /usr/src/minix/servers/is/dmp_kernel.c
	cp -fv src/proc.h /usr/src/minix/kernel/proc.h
	cp -fv src/proto.h usr/src/servers/is/proto.h


