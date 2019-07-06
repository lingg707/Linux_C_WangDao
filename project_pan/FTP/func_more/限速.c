//限速是通过使进程睡眠实现的，设置一个定时器计算当前的速度，
//如果发现大于限定的速度，那么就通过:
//睡眠时间 = (当前传输速度 / 最大传输速度-1) * 当前传输时间来计算。
void limit_rate(session_t *sess, int bytes_transfered, int is_upload)
{
    sess->data_process = 1;

    // 睡眠时间 = (当前传输速度 / 最大传输速度 – 1) * 当前传输时间;
    long curr_sec = get_time_sec();
    long curr_usec = get_time_usec();

    double elapsed;
    elapsed = (double)(curr_sec - sess->bw_transfer_start_sec);
    elapsed += (double)(curr_usec - sess->bw_transfer_start_usec) / (double)1000000;
    if (elapsed <= (double)0)
    {
        elapsed = (double)0.01;
    }

    // 计算当前传输速度
    unsigned int bw_rate = (unsigned int)((double)bytes_transfered / elapsed);
    double rate_ratio;
    if (is_upload)
    {
        if (bw_rate <= sess->bw_upload_rate_max)
        {
            // 不需要限速
            sess->bw_transfer_start_sec = curr_sec;
            sess->bw_transfer_start_usec = curr_usec;
            return;
        }
        rate_ratio = bw_rate / sess->bw_upload_rate_max;
    }
    else
    {
        if (bw_rate <= sess->bw_download_rate_max)
        {
            // 不需要限速
            sess->bw_transfer_start_sec = curr_sec;
            sess->bw_transfer_start_usec = curr_usec;
            return;
        }
        rate_ratio = bw_rate / sess->bw_download_rate_max;
    }

    // 睡眠时间 = (当前传输速度 / 最大传输速度 – 1) * 当前传输时间;
    double pause_time;
    pause_time = (rate_ratio - (double)1) * elapsed;
    nano_sleep(pause_time);
    sess->bw_transfer_start_sec = get_time_sec();
    sess->bw_transfer_start_usec = get_time_usec();
}
