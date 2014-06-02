default:
	g++ main.cpp surferclient.cpp baglanti.cpp -lpthread /usr/lib/x86_64-linux-gnu/libboost_thread.a /usr/lib/x86_64-linux-gnu/libboost_system.a -o surferclient
