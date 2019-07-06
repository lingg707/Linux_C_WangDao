//该写法是设置全局变量，而不是每次传输的时候都要检查文件是否存在
static void do_retr(session_t *sess)
{
    // 下载文件
    // 断点续载

    // 创建数据连接
    if (get_transfer_fd(sess) == 0)
    {
        return;
    }

    long long offset = sess->restart_pos;
    sess->restart_pos = 0;

    // 打开文件
    int fd = open(sess->arg, O_RDONLY);
    if (fd == -1)
    {
        ftp_reply(sess, FTP_FILEFAIL, "Failed to open file.");
        return;
    }

    int ret;
    // 加读锁
    ret = lock_file_read(fd);
    if (ret == -1)
    {
        ftp_reply(sess, FTP_FILEFAIL, "Failed to open file.");
        return;
    }

    // 判断是否是普通文件
    struct stat sbuf;
    ret = fstat(fd, &sbuf);
    if (!S_ISREG(sbuf.st_mode))
    {
        ftp_reply(sess, FTP_FILEFAIL, "Failed to open file.");
        return;
    }

    if (offset != 0)
    {
        ret = lseek(fd, offset, SEEK_SET);
        if (ret == -1)
        {
            ftp_reply(sess, FTP_FILEFAIL, "Failed to open file.");
            return;
        }
    }

    //150 Opening BINARY mode data connection for /home/jjl/tmp/echocli.c (1085 bytes).
    // 150
    char text[1024] = {0};
    if (sess->is_ascii)
    {
        sprintf(text, "Opening ASCII mode data connection for %s (%lld bytes).",
                sess->arg, (long long)sbuf.st_size);
    }
    else
    {
        sprintf(text, "Opening BINARY mode data connection for %s (%lld bytes).",
                sess->arg, (long long)sbuf.st_size);
    }

    ftp_reply(sess, FTP_DATACONN, text);

    int flag = 0;

    // ssize_t sendfile(int out_fd, int in_fd, off_t *offset, size_t count);

    long long bytes_to_send = sbuf.st_size;
    if (offset > bytes_to_send)
    {
        bytes_to_send = 0;
    }
    else
    {
        bytes_to_send -= offset;
    }

    sess->bw_transfer_start_sec = get_time_sec();
    sess->bw_transfer_start_usec = get_time_usec();
    while (bytes_to_send)
    {
        int num_this_time = bytes_to_send > 4096 ? 4096 : bytes_to_send;
        ret = sendfile(sess->data_fd, fd, NULL, num_this_time);
        if (ret == -1)
        {
            flag = 2;
            break;
        }

        limit_rate(sess, ret, 0);
        if (sess->abor_received)
        {
            flag = 2;
            break;
        }
        bytes_to_send -= ret;
    }

    if (bytes_to_send == 0)
    {
        flag = 0;
    }

    // 关闭数据套接字
    close(sess->data_fd);
    sess->data_fd = -1;

    close(fd);

    if (flag == 0 && !sess->abor_received)
    {
        // 226
        ftp_reply(sess, FTP_TRANSFEROK, "Transfer complete.");
    }
    else if (flag == 1)
    {
        // 451
        ftp_reply(sess, FTP_BADSENDFILE, "Failure reading from local file.");
    }
    else if (flag == 2)
    {
        // 426
        ftp_reply(sess, FTP_BADSENDNET, "Failure writting to network stream.");
    }
    check_abor(sess);
    // 重新开启控制连接通道闹钟
    start_cmdio_alarm();
}
