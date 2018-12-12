default:clean all


clean: 
	rm -rfv /usr/servers/is/proto.h
	rm -rfv /usr/minix/kernel/proc.h 
	rm -rfv /usr/minix/servers/is/dmp.c 
	rm -rfv /usr/minix/servers/is/dmp_kernel.c

all:
	cp -fv src/dmp.c /usr/minix/servers/is/dmp.c
	cp -fv src/dmp_pm.c /usr/minix/servers/is/dmp_kernel.c
	cp -fv src/proc.h /usr/minix/kernel/proc.h
	cp -fv src/proto.h usr/servers/is/proto.h


