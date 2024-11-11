#include <arpa/inet.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <ctime>
#include <cstring>

int main() {
    // Создание TCP сокета
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        std::cerr << "Ошибка создания сокета" << std::endl;
        return 1;
    }

    // Настройка адреса сервера
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Привязка сокета к адресу
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "Ошибка привязки сокета" << std::endl;
        close(server_socket);
        return 1;
    }

    // Прослушивание входящих соединений
    if (listen(server_socket, 5) < 0) {
        std::cerr << "Ошибка прослушивания" << std::endl;
        close(server_socket);
        return 1;
    }

    std::cout << "Сервер запущен и ожидает подключения..." << std::endl;

    while (true) {
        // Принятие входящего соединения
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);
        int client_socket = accept(server_socket, (struct sockaddr*)&client_addr, &addr_len);
        if (client_socket < 0) {
            std::cerr << "Ошибка принятия соединения" << std::endl;
            continue;
        }

        // Получение сообщения от клиента
        char buf[256];
        ssize_t recv_bytes = recv(client_socket, buf, sizeof(buf) - 1, 0);
        if (recv_bytes < 0) {
            std::cerr << "Ошибка получения данных" << std::endl;
            close(client_socket);
            continue;
        }
        buf[recv_bytes] = '\0'; // Завершение строки
        std::cout << "Получено сообщение: " << buf << std::endl;

        // Отправка текущего времени клиенту
        time_t current_time = time(0);
        std::string datetime = ctime(&current_time);

        // Удаляем символ новой строки, если он есть
        if (!datetime.empty() && datetime[datetime.length() - 1] == '\n') {
            datetime.erase(datetime.length() - 1); // Удаляем символ новой строки
        }

        // Проверка, что строка не пустая перед отправкой
        if (!datetime.empty()) {
            ssize_t sent_bytes = send(client_socket, datetime.c_str(), datetime.length(), 0);
            if (sent_bytes < 0) {
                std::cerr << "Ошибка отправки данных" << std::endl;
            }
        } else {
            std::cerr << "Ошибка: строка времени пустая" << std::endl;
        }

        // Закрытие соединения с клиентом
        close(client_socket);
    }

    // Закрытие серверного сокета
    close(server_socket);
    return 0;
}
