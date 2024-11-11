#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

int main() {
    // Создание UDP сокета
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    // Настройка адреса сервера
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(3306); // Порт сервера
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP-адрес сервера

    // Сообщение для отправки
    const char* message = "дата?";

    // Отправка сообщения серверу
    ssize_t sent_bytes = sendto(sock, message, strlen(message), 0,
                                 (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (sent_bytes == -1) {
        std::cerr << "Ошибка отправки данных" << std::endl;
        close(sock);
        return 1;
    }

    std::cout << "Сообщение отправлено: " << message << std::endl;

    // Получение ответа от сервера
    char buf[256];
    struct sockaddr_in from_addr;
    socklen_t from_len = sizeof(from_addr);
    ssize_t recv_bytes = recvfrom(sock, buf, sizeof(buf) - 1, 0,
                                   (struct sockaddr*)&from_addr, &from_len);
    if (recv_bytes == -1) {
        std::cerr << "Ошибка получения данных" << std::endl;
        close(sock);
        return 1;
    }

    buf[recv_bytes] = '\0'; // Завершение строки
    std::cout << "Ответ от сервера: " << buf << std::endl;

    // Закрытие сокета
    close(sock);
    return 0;
}
