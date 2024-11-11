#Компилятор
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11

#Исходные файлы
CLIENT_SRC = dt.cpp
SERVER_SRC = server.cpp

#Исполняемые файлы
CLIENT_EXE = dt
SERVER_EXE = server

#Правила сборки
all: $(CLIENT_EXE) $(SERVER_EXE)

$(CLIENT_EXE): $(CLIENT_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SERVER_EXE): $(SERVER_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

#Очистка
clean:
	rm -f $(CLIENT_EXE) $(SERVER_EXE) *.o
