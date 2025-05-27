#include "Configuration.hpp"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <algorithm>

Configuration::Configuration(const std::string& config_file_path) {
    // 读取配置文件的代码，从../conf/server.conf
    // 读取服务器的IP地址、端口号、数据库连接信息等
    std::ifstream file(config_file_path);
    if (!file.is_open()) {
        perror("无法打开配置文件");
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        trim(line);
        if (line.empty() || line[0] == '#') continue; // 跳过空行和注释
        ParseLine(line);
    }

    Validate(); // 校验参数完整性
}

void Configuration::ParseLine(const std::string &line) {
    size_t pos = line.find_first_of(" \t");
    if (pos == std::string::npos) {
        throw std::runtime_error("无效配置行: " + line);
    }

    std::string key = line.substr(0, pos);
    std::string value = line.substr(pos + 1);
    trim(key);
    trim(value);

    if (key == "ip") {
        ip_ = value;
    } else if (key == "port") {
        int port = std::stoi(value);
        if (port < 1 || port > 65535) {
            throw std::out_of_range("端口超出范围: " + value);
        }
        port_ = static_cast<uint16_t>(port);
    } else if (key == "thread_num") {
        thread_num_ = std::stoi(value);
        if (thread_num_ <= 0) {
            throw std::invalid_argument("线程数必须为正整数: " + value);
        }
    } else if (key == "task_num") {
        task_num_ = std::stoi(value);
        if (task_num_ <= 0) {
            throw std::invalid_argument("任务数必须为正整数: " + value);
        }
    } else if (key == "video_path") {
        video_path_ = value;
        if (video_path_.back() != '/') {
            video_path_ += '/'; // 确保路径以斜杠结尾
        }
    } else if (key == "log_file") {
        log_file_ = value;
    } else {
        throw std::runtime_error("未知配置项: " + key);
    }
}

void Configuration::Validate() const {
    if (ip_.empty()) throw std::runtime_error("配置缺少IP地址");
    if (port_ == 0) throw std::runtime_error("配置缺少端口号");
    if (thread_num_ == 0) throw std::runtime_error("配置缺少线程数");
    if (task_num_ == 0) throw std::runtime_error("配置缺少任务数");
    if (video_path_.empty()) throw std::runtime_error("配置缺少视频路径");
    if (log_file_.empty()) throw std::runtime_error("配置缺少日志文件路径");
}


void Configuration::trim(std::string &s) {
    // 去除字符串前后空格
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}