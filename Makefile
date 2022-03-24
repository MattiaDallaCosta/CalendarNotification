compile:
	g++ daemon.cpp Task.cpp MyUtils.cpp Message.cpp -o daemon -std=c++20
	g++ sender.cpp Message.cpp -o sender -std=c++20 `pkg-config --cflags --libs libnotify`

run:
	./daemon


