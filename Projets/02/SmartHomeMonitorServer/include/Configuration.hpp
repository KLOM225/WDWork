#pragma once

#include <fstream>
#include <string>
#include <stdexcept>
#include <cstdint>
#include <algorithm>

// 创建类Configuration，通过它读取服务器程序的输入信息
// 读取配置文件的代码，从../SmartHomeMonitorServer/conf/server.conf
// 辅助函数：去除字符串前后空格
void trim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

class Configuration {
public:
    explicit Configuration();

    // 获取配置参数
    std::string GetIP() const { return ip_; }
    uint16_t GetPort() const { return port_; }
    int GetThreadNum() const { return thread_num_; }
    int GetTaskNum() const { return task_num_; }
    std::string GetVideoPath() const { return video_path_; }
    std::string GetLogFile() const { return log_file_; }

private:
    std::string ip_;
    uint16_t port_ = 0;
    int thread_num_ = 0;
    int task_num_ = 0;
    std::string video_path_;
    std::string log_file_;

    void ParseLine(const std::string &line);
    void Validate() const;
};