#include <string>
#include "Logger.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <cstring>

#define LOG_PATH "../logs/logs.txt"

void Logger::write_to_log(std::string log_entry) {
    std::time_t current_time = std::time(nullptr);
    auto timestamp = ctime(&current_time);
    timestamp[strlen(timestamp) - 1] = '\0';
    buffer << timestamp << ": " << log_entry + "\n";
}

void Logger::flush_logs_to_file() {
    pthread_mutex_lock(&log_mutex);
    log_file.open (LOG_PATH, std::ios_base::app);
    log_file << buffer.str();
    log_file.close();
    pthread_mutex_unlock(&log_mutex);
    buffer.str(std::string());
}
std::time_t get_timestamp() {
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}