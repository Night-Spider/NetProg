#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>

int main() {
    // Создание TCP сокета
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    // Настройка адреса сервера
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080); // Порт сервера
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // IP-адрес сервера

    // Установка соединения с сервером
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка подключения к серверу" << std::endl;
        close(sock);
        return 1;
    }

    // Сообщение для отправки
    const char* message = "дата?";

    // Отправка сообщения серверу
    ssize_t sent_bytes = send(sock, message, strlen(message), 0);
    if (sent_bytes == -1) {
        std::cerr << "Ошибка отправки данных" << std::endl;
        close(sock);
        return 1;
    }

    std::cout << "Сообщение отправлено: " << message << std::endl;

    // Получение ответа от сервера
    char buf[256];
    ssize_t recv_bytes = recv(sock, buf, sizeof(buf) - 1, 0);
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
