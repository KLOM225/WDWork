int main() {
	// 接收HTTP报文
	ssize_t len = 0;
	char buf[1024] = { 0 };
	recv(net_fd, &len, sizeof(ssize_t), MSG_WAITALL);
	recv(net_fd, buf, len, MSG_WAITALL);
	printf("buf: %s \n", buf);

	 //解析HTTP报文 - 获得信息
	char *begin = strstr(buf, "/"); 
	char *end = strstr(begin, " "); 
	char path[100] = {0};
	strncpy(path, begin,end-begin );
	printf("path: %s \n", path);

	// 解析HTTP报文 - 获得信息
	char *begin = strstr(buf, "file_name\":\"");
	begin = strstr(begin, ":");
	begin = strstr(begin, "\"");
	char *end = strstr(begin + 1, "\"");

	char file_name[100] = { 0 };
	strncpy(file_name, begin + 1, end - begin - 1);

	// 读取文件内容
	int file_fd = open(file_name, O_RDONLY);
	char file_buf[1024] = { 0 };
	ssize_t ret = read(file_fd, file_buf, sizeof(file_buf));

	// 构建响应报文
	char response[4096] = { 0 };
	char *str = "HTTP/1.1 200 OK \r\nContent-Length:";
	sprintf(response, "%s%ld%s%s", str, ret, "\r\n\r\n", file_buf);

	// 返回响应报文
	int response_len = strlen(response);
	send(net_fd, &response_len, sizeof(ssize_t), 0);
	send(net_fd, response, response_len, 0);

}