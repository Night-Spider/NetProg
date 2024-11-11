#include <arpa/inet.h>
#include <csignal>
#include <ctime>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int main()
{
    int s = socket(AF_INET, SOCK_DGRAM, 0); // создание сокета IPv4 UDP
    if (s < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3306);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (bind(s, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка привязки сокета" << std::endl;
        close(s);
        return 1;
    }

    while (true) {
        struct sockaddr_in client_addr;
        unsigned int addr_len = sizeof(client_addr);
        char buf[256];
        
        ssize_t rc = recvfrom(s, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &addr_len);
        if (rc < 0) {
            std::cerr << "Ошибка получения данных" << std::endl;
            continue;
        }
        
        buf[rc] = '\0'; // Завершение строки
        std::cout << "Получено сообщение: " << buf << std::endl;

        time_t current_time = time(0);
        std::string datetime = ctime(&current_time); // принимает указатель типа time_t

        // Отправка времени клиенту
        ssize_t sent_bytes = sendto(s, datetime.c_str(), datetime.length(), 0, (struct sockaddr*)&client_addr, addr_len);
        if (sent_bytes < 0) {
            std::cerr << "Ошибка отправки данных" << std::endl;
        }
    }

    close(s);
    return 0;
}
