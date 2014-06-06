default:
	g++ main.cpp -g3 -fno-inline -O0 surferclient.cpp baglanti.cpp -Wall -Wno-unused-function -Wno-unused-variable -Wno-unused-but-set-variable -Wno-multichar -lpthread /usr/lib/x86_64-linux-gnu/libboost_thread.a /usr/lib/x86_64-linux-gnu/libboost_system.a -o surferclient
