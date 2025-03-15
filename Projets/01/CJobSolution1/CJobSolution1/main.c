
    // 读取标准输入
    char buf[60] = { 0 };
    read(STDIN_FILENO, buf, sizeof(buf));

    if (strlen(buf) == 2 && buf[0] == '1') {
        // 按照HTTP报文格式构建报文 (信息可以放在资源路径之后, 也可以放在正文里, 自由选择)
        char *str = "GET /1 HTTP/1.1 \r\nCookie:123456789\r\n\r\n{\"file_name\":\"1.txt\"}";
        ssize_t len = strlen(str);

        send(socket_fd, &len, sizeof(ssize_t), 0);
        send(socket_fd, str, strlen(str), 0);

        // 等待对方回传HTTP报文, 携带1.txt的内容信息


    }
    else if (strlen(buf) == 2 && buf[0] == '2') {
        // 按照HTTP报文格式构建报文 (信息可以放在资源路径之后, 也可以放在正文里, 自由选择)
        char *str = "GET /2 HTTP/1.1 \r\nCookie:123456789\r\n\r\n{\"file_name\":\"2.txt\"}";
        ssize_t len = strlen(str);

        send(socket_fd, &len, sizeof(ssize_t), 0);
        send(socket_fd, str, strlen(str), 0);

        // 等待对方回传HTTP报文, 携带2.txt的内容信息

    }

    char response[4096] = { 0 };
    ssize_t len = 0;
    recv(socket_fd, &len, sizeof(ssize_t), MSG_WAITALL);
    recv(socket_fd, response, len, MSG_WAITALL);
    printf("------ \n");
    printf("%s\n", response);
    printf("------ \n");

    close(socket_fd);
    return 0;
}