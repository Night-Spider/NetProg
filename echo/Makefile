#Компилятор
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

#Исходные файлы
CLIENT_SRC = echo1.cpp
SERVER_SRC = serverecho.cpp

#Исполняемые файлы
CLIENT_EXE = echo1
SERVER_EXE = serverecho

#Правила сборки
all: $(CLIENT_EXE) $(SERVER_EXE)

$(CLIENT_EXE): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SERVER_EXE): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

#Очистка
clean:
	rm -f $(CLIENT_EXE) $(SERVER_EXE) *.o
