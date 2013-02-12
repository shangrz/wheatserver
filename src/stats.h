#ifndef _STATS_H_
#define _STATS_H_

#define WHEAT_STATCOMMAND_PACKET_FIELD       8
#define WHEAT_STAT_SEND_FORMAT \
    "\r\rSTAT\n%d\n%lld\n%lld\n%lld\n%lld\n%lld\n%ld$"

// If want to add or delete statistic field, pay attention to place
// 1. where handle this field
// 2. parseStat();
// 3. logWorkerStatFormat()
// 4. plusStat()
// 5. initWorkerStat()
struct workerStat {
    int master_stat_fd;
    time_t refresh_time;

    // packet overload
    long long stat_total_connection;    // Number of the total client
    long long stat_total_request;       // Number of the total request parsed
    // Number of the failed request parsed. Such as http protocol, non-200
    // response is included
    long long stat_failed_request;
    // Max size of request buffer size since worker started
    long long stat_buffer_size;
    long long stat_work_time;           // Total of handling request time
    time_t stat_last_send;              // Time since last send.
};

// if want to add or delete below fields
// 1. initMasterStat()
// 2. where handle this field
// 3. logMasterStatFormat()
struct masterStat {
    int total_run_workers;           // Number of total worker ever run
    int timeout_workers;                // Number of total worker timeout
};

struct masterClient;

struct workerStat *initWorkerStat(int only_malloc);
struct masterStat *initMasterStat();
void resetStat(struct workerStat *w);
void sendStatPacket();
void logStat();
void statCommand(struct masterClient *c);

#endif
