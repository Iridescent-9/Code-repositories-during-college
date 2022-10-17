#pragma once
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <deque>

class pcb
{
private:
	bool finish_ = false; //进程是否完成
	bool flag_ = false; //是否被调度过
	float arrive_time_ = 0; //到达时间
	float finish_time_ = 0; //完成时间
	float prior_ = 0; //优先级
	float remaining_time_ = 0; //剩余时间
	float service_time_ = 0; //服务时间
	float start_time_ = 0; //开始时间
	float turnaround_time_ = 0; //周转时间
	float wait_time_ = 0; //等待时间
	float weighted_turnaround_time_ = 0; //带权周转时间
	std::string p_name_; //进程名

public:
	explicit pcb(std::string name, float a_t = 0, float s_t = 0);
	[[nodiscard]] float get_turnaround_time() const;
	[[nodiscard]] float get_weighted_turnaround_time() const;
	friend std::ostream& operator<<(std::ostream&, const pcb&);
	friend void calculate_response_ratio(std::vector<pcb>&);
	friend void fcfs_subfunction(std::vector<pcb>&, std::vector<std::string>&);
	friend void hrrn_subfunction(std::vector<pcb>&, std::vector<std::string>&);
	friend void rr_set_start_time(std::deque<pcb>&, const float&);
	friend void rr_subfunction(std::vector<pcb>&, std::vector<std::string>&, const float&);
	friend void sjf_subfunction(std::vector<pcb>&, std::vector<std::string>&);
	friend void sort_process(std::vector<pcb>&);
	pcb();
};
