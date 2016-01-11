FLAGS	= -std=c++11

life: main.cpp
	mpic++ $(FLAGS) $^

clean:
	rm a.out

