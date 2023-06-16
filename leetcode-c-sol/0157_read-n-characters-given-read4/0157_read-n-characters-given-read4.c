/**
 * The read4 API is defined in the parent class Reader4.
 *     int read4(char *buf4);
 */

/**
 * @param buf Destination buffer
 * @param n   Number of characters to read
 * @return    The number of actual characters read
 */
int _read(char *buf, int n)
{
    int ret = 0;
    while (n >= 4) {
        int tmp = read4(buf);
        n -= tmp;
        buf += tmp;
        ret += tmp;
        /* End of the buf4 read */
        if (tmp == 0) {
            *buf = 0;
            goto out;
        }
    }

    read4(buf);
    buf[n] = 0;
    ret += n;
out:
    return ret;
}