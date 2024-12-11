#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Для системных вызовов read, write
#include <limits.h> // Для определения PATH_MAX

#define BUFFER_SIZE 1024 // Максимальный размер ввода пользователя

// ANSI-коды для цветов
#define COLOR_ORANGE_BOLD "\033[1;93m"
#define COLOR_CYAN_BOLD "\033[1;96m"
#define COLOR_RESET "\033[0m"

const char gush[] = "GUSH";
const char dollar_prompt[] = "$ ";

void show_prompt() {
    char cwd[PATH_MAX]; // Буфер для текущей директории
    if (getcwd(cwd, sizeof(cwd)) != NULL) {

        // Печатаем приглашение желтым цветом с жирным шрифтом
        write(STDOUT_FILENO, COLOR_CYAN_BOLD, strlen(COLOR_CYAN_BOLD));
        write(STDOUT_FILENO, gush, strlen(gush));
        write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));

        // Добавляем разделитель ':'
        write(STDOUT_FILENO, ":", 1);
    	
        // Печатаем директорию светло-голубым цветом с жирным шрифтом
        write(STDOUT_FILENO, COLOR_ORANGE_BOLD, strlen(COLOR_ORANGE_BOLD));
        write(STDOUT_FILENO, cwd, strlen(cwd));
        write(STDOUT_FILENO, COLOR_RESET, strlen(COLOR_RESET));

        write(STDOUT_FILENO, dollar_prompt, strlen(dollar_prompt));
        
    } else {
        perror("Ошибка получения текущей директории");
    }
}

int main() {
    char buffer[BUFFER_SIZE]; // Буфер для ввода пользователя
    ssize_t bytes_read;

    while (1) {
        show_prompt(); // Показываем приглашение

        // Считываем ввод пользователя
        bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
        if (bytes_read < 0) {
            perror("Ошибка чтения ввода");
            exit(EXIT_FAILURE);
        }

        buffer[bytes_read] = '\0';                // Завершаем строку нулевым символом
        buffer[strcspn(buffer, "\n")] = '\0';     // Убираем символ новой строки

        if (buffer[0] == '\0') { // Пропуск пустого ввода
            continue;
        }

        if (strcmp(buffer, "exit") == 0) { // Обработка выхода
            write(STDOUT_FILENO, "Exiting...\n", 11);
            break;
        }

        // Эхо-ввод
        write(STDOUT_FILENO, "You said: ", 10);
        write(STDOUT_FILENO, buffer, strlen(buffer));
        write(STDOUT_FILENO, "\n", 1);
    }

    return 0;
}

