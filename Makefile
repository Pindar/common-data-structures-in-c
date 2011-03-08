#all: 
#	make -i -C src

test: CppUTest/lib/libCppUTest.a
	make -i -C tests

clean:
	make -i -C tests clean
	make -i -C CppUTest clean
#	make -i -C src clean
	

CppUTest/lib/libCppUTest.a:
	pwd
	make -i -C CppUTest