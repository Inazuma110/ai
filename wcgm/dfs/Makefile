run: 14
14:
	g++ -std=c++14 main.cpp -Wall -g -fsanitize=undefined -D_GLIBCXX_DEBUG
	./a.out > out
	cat out
11:
	g++ -std=c++11 main.cpp -Wall -g -fsanitize=undefined -D_GLIBCXX_DEBUG
	cat input | ./a.out
