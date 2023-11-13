#ifndef FILETOOLSBACKUP_H
#define FILETOOLSBACKUP_H

#include <QObject>
#include <libimobiledevice/mobilebackup2.h>
#include <libimobiledevice/afc.h>
class FileToolsBackUp : public QObject
{
    Q_OBJECT
public:
    explicit FileToolsBackUp(QObject *parent = nullptr);

    virtual ~FileToolsBackUp();
public:
    /*
     * 设置NP通知的回调函数
     * 作为NP通知的回调函数，当用户取消备份操作或者备份域发生了改变
     * 则手机端会调用该函数，进而改变全局变量，控制PC端的备份进程
    */
    static void notify_cb(const char *notification, void *userdata);
    /*
     * 从AFC客户端对象获取指定文件的内容
    */
    static void mobilebackup_afc_get_file_contents(afc_client_t afc, const char *filename, char **data, uint64_t *size);
    /*
     * 生产uuid
     * 作用：？
    */
    static char* get_uuid();
    /*
     * 生成info.plist文件
    */
    static plist_t mobilebackup_factory_info_plist_new(const char* udid, idevice_t device, afc_client_t afc);
    /*
     * 通过mb2状态检查快照状态 ？？？
    */
    static int mb2_status_check_snapshot_state(const char *path, const char *udid, const char *matches);
    /*
     * 打开手机端指定的文件
    */
    static void do_post_notification(idevice_t device, const char *notification);
    /*
     * 打印进度条
    */
    static void print_progress_real(double progress, int flush);
    /*
     * 计算进度 并 打印进度条
    */
    static void print_progress(uint64_t current, uint64_t total);
    /*
     * 设置整体进度
    */
    static void mb2_set_overall_progress(double progress);
    /*
     * 从消息中获取整体进度
    */
    static void mb2_set_overall_progress_from_message(plist_t message, char* identifier);
    /*
     * 往mb2状态描述变量里添加文件错误
    */
    static void mb2_multi_status_add_file_error(plist_t status_dict, const char *path, int error_code, const char *error_message);
    /*
     * errno 转 苹果errcode
    */
    static int errno_to_device_error(int errno_value);
    /*
     * 处理文件的下载？
    */
    static int mb2_handle_send_file(mobilebackup2_client_t mobilebackup2, const char *backup_dir, const char *path, plist_t *errplist);
    static void mb2_handle_send_files(mobilebackup2_client_t mobilebackup2, plist_t message, const char *backup_dir);
    /*
     * 接收文件名
    */
    static int mb2_receive_filename(mobilebackup2_client_t mobilebackup2, char** filename);
    static int mb2_handle_receive_files(mobilebackup2_client_t mobilebackup2, plist_t message, const char *backup_dir);
    /*
    * 处理目录列表？
    */
    static void mb2_handle_list_directory(mobilebackup2_client_t mobilebackup2, plist_t message, const char *backup_dir);
    /*
     * 生成目录
    */
    static void mb2_handle_make_directory(mobilebackup2_client_t mobilebackup2, plist_t message, const char *backup_dir);
    /*
     * 拷贝文件
    */
    static void mb2_copy_file_by_path(const char *src, const char *dst);
    /*
     * 拷贝目录
    */
    static void mb2_copy_directory_by_path(const char *src, const char *dst);
    /**
     * signal handler function for cleaning up properly
     */
    static void clean_exit(int sig);
signals:


public:
    static int quit_flag;
    static int backup_domain_changed;
    static double overall_progress;
};

#endif // FILETOOLSBACKUP_H
