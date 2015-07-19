#pragma once

////////////////////////////////////////////////////////////////////////////////
// ����������

extern char *var_cfg_str;
extern acl::master_str_tbl var_conf_str_tab[];

extern int  var_cfg_bool;
extern acl::master_bool_tbl var_conf_bool_tab[];

extern int  var_cfg_int;
extern acl::master_int_tbl var_conf_int_tab[];

extern long long int  var_cfg_int64;
extern acl::master_int64_tbl var_conf_int64_tab[];

////////////////////////////////////////////////////////////////////////////////

//class acl::socket_stream;

class master_service : public acl::master_threads
{
public:
	master_service();
	~master_service();

	const char* get_addr(const char* from) const;

protected:
	/**
	 * ���麯������ĳ���ͻ������������ݿɶ���رջ����ʱ���ô˺���
	 * @param stream {socket_stream*}
	 * @return {bool} ���� false ���ʾ���������غ���Ҫ�ر����ӣ�
	 *  �����ʾ��Ҫ���ֳ����ӣ����������������Ӧ��Ӧ�÷��� false
	 */
	virtual bool thread_on_read(acl::socket_stream* stream);

	/**
	 * ���̳߳��е�ĳ���̻߳��һ������ʱ�Ļص�������
	 * ���������һЩ��ʼ������
	 * @param stream {socket_stream*}
	 * @return {bool} ������� false ���ʾ����Ҫ��ر����ӣ�����
	 *  �ؽ��������ٴ����� thread_main ����
	 */
	virtual bool thread_on_accept(acl::socket_stream* stream);

	/**
	 * ��ĳ���������ӵ� IO ��д��ʱʱ�Ļص�����������ú������� true ���ʾ�����ȴ���һ��
	 * ��д��������ϣ���رո�����
	 * @param stream {socket_stream*}
	 * @return {bool} ������� false ���ʾ����Ҫ��ر����ӣ�����
	 *  �ؽ��������ٴ����� thread_main ����
	 */
	virtual bool thread_on_timeout(acl::socket_stream* stream);

	/**
	 * ����ĳ���̰߳󶨵����ӹر�ʱ�Ļص�����
	 * @param stream {socket_stream*}
	 */
	virtual void thread_on_close(acl::socket_stream* stream);

	/**
	 * ���̳߳���һ�����̱߳�����ʱ�Ļص�����
	 */
	virtual void thread_on_init();

	/**
	 * ���̳߳���һ���߳��˳�ʱ�Ļص�����
	 */
	virtual void thread_on_exit();

	/**
	 * �������л��û����ݺ���õĻص��������˺���������ʱ������
	 * ��Ȩ��Ϊ��ͨ���޼���
	 */
	virtual void proc_on_init();

	/**
	 * �������˳�ǰ���õĻص�����
	 */
	virtual void proc_on_exit();

private:
	acl::polarssl_conf* server_ssl_conf_;
	acl::polarssl_conf* client_ssl_conf_;
	std::map<acl::string, acl::string> addrs_map_;
	acl::ofstream out_;

	acl::polarssl_io* setup_ssl(acl::socket_stream& conn,
			acl::polarssl_conf& conf);

	void create_addrs_map();
};