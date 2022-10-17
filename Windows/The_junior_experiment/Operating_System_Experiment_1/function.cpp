#include "function.h"

void choice(std::vector<pcb>& p, std::vector<std::string>& list, int& n_p, const int& i)
{
	switch (i)
	{
	case 1:
		first_come_first_service(p, list, n_p);
		break;
	case 2:
		shortest_job_first(p, list, n_p);
		break;
	case 3:
		round_robin(p, list, n_p);
		break;
	case 4:
		highest_response_ratio_next(p, list, n_p);
		break;
	default:
		;
	}
}

void display_menu()
{
	std::cout << "1.先来先服务" << std::endl;
	std::cout << "2.短作业优先" << std::endl;
	std::cout << "3.时间片轮转" << std::endl;
	std::cout << "4.高响应比优先" << std::endl;
	std::cout << "5.退出程序" << std::endl;
	std::cout << "输入功能序号" << std::endl;
}

void first_come_first_service(std::vector<pcb>& p, std::vector<std::string>& list, int& n_p)
{
	std::cout << "----------先来先服务----------" << std::endl;
	initialize_process(p, n_p);
	sort_process(p);
	fcfs_subfunction(p, list);
	print_process_information(p, list, n_p);
}

void shortest_job_first(std::vector<pcb>& p, std::vector<std::string>& list, int& n_p)
{
	std::cout << "----------短作业优先----------" << std::endl;
	initialize_process(p, n_p);
	sjf_subfunction(p, list);
	sort_process(p);
	print_process_information(p, list, n_p);
}

void round_robin(std::vector<pcb>& p, std::vector<std::string>& list, int& n_p)
{
	std::cout << "----------时间片轮转----------" << std::endl;
	std::cout << "请输入时间片大小" << std::endl;
	float rr_t = 0;
	std::cin >> rr_t;
	initialize_process(p, n_p);
	sort_process(p);
	rr_subfunction(p, list, rr_t);
	print_process_information(p, list, n_p);
}

void highest_response_ratio_next(std::vector<pcb>& p, std::vector<std::string>& list, int& n_p)
{
	std::cout << "----------高响应比优先----------" << std::endl;
	initialize_process(p, n_p);
	sort_process(p);
	hrrn_subfunction(p, list);
	print_process_information(p, list, n_p);
}

void initialize_process(std::vector<pcb>& p, int& n_p)
{
	std::cout << "请输入进程数" << std::endl;
	std::cin >> n_p;
	std::string name;
	float a_t, s_t;
	std::cout << "请输入进程名、到达时间、服务时间" << std::endl;
	for (int i = 0; i < n_p; i++)
	{
		std::cout << "请输入第" << i + 1 << "个进程的信息" << std::endl;
		std::cin >> name >> a_t >> s_t;
		pcb new_process(name, a_t, s_t);
		p.push_back(new_process);
	}
}

void print_process_information(std::vector<pcb>& p, std::vector<std::string>& list, int& n_p)
{
	std::cout << "调用算法后进程的运行顺序是：";
	std::cout << list[0];
	for (int i = 1; i < static_cast<int>(list.size()); i++)
	{
		std::cout << "-->";
		std::cout << list[i];
	}
	std::cout << std::endl;
	std::cout << "具体进程调度信息：" << std::endl;
	std::cout << std::left << std::setw(14) << "进程名" << std::left << std::setw(18) << "到达时间" << std::left <<
		std::setw(18) << "服务时间" << std::left << std::setw(18) << "开始时间" << std::left << std::setw(18) << "完成时间" <<
		std::left << std::setw(18) << "周转时间" << std::left << std::setw(18)
		<< "带权周转时间" << std::endl;
	for (auto& x : p)
	{
		std::cout << x << std::endl;
	}
	float average_turnaround_time = 0;
	float average_weighted_turnaround_time = 0;
	for (auto& x : p)
	{
		average_turnaround_time += x.get_turnaround_time();
		average_weighted_turnaround_time += x.get_weighted_turnaround_time();
	}
	average_turnaround_time /= static_cast<float>(p.size());
	average_weighted_turnaround_time /= static_cast<float>(p.size());
	std::cout << "调用算法的平均周转时间为：" << average_turnaround_time << std::endl;
	std::cout << "调用算法的平均带权周转时间为：" << average_weighted_turnaround_time << std::endl;
	std::vector<pcb>().swap(p);
	std::vector<std::string>().swap(list);
	n_p = 0;
}

void fcfs_subfunction(std::vector<pcb>& p, std::vector<std::string>& list)
{
	for (int k = 0; k <= static_cast<int>(p.size()) - 1; k++)
	{
		if (k == 0)
		{
			p[k].start_time_ = p[k].arrive_time_;
			p[k].finish_time_ = p[k].start_time_ + p[k].service_time_;
		}
		else
		{
			p[k].start_time_ = (p[k - 1].finish_time_ >= p[k].arrive_time_) ? p[k - 1].finish_time_ : p[k].arrive_time_;
			p[k].finish_time_ = p[k].start_time_ + p[k].service_time_;
		}
	}
	for (auto& x : p)
	{
		x.turnaround_time_ = x.finish_time_ - x.arrive_time_;
		x.weighted_turnaround_time_ = x.turnaround_time_ / x.service_time_;
		list.push_back(x.p_name_);
	}
}

void sort_process(std::vector<pcb>& p)
{
	std::ranges::sort(p, [](const pcb& a_pcb, const pcb& b_pcb)
	{
		return a_pcb.arrive_time_ < b_pcb.arrive_time_;
	});
}

void sjf_subfunction(std::vector<pcb>& p, std::vector<std::string>& list)
{
	std::ranges::sort(p, [](const pcb& a_pcb, const pcb& b_pcb)
	{
		return (a_pcb.arrive_time_ < b_pcb.arrive_time_ || (a_pcb.arrive_time_ == b_pcb.arrive_time_ && a_pcb.
			service_time_ < b_pcb.service_time_));
	});
	for (int m = 0; m < static_cast<int>(p.size()); m++)
	{
		if (m == 0)
		{
			p[m].start_time_ = p[m].arrive_time_;
			p[m].finish_time_ = p[m].arrive_time_ + p[m].service_time_;
		}
		else
		{
			p[m].finish_time_ = ((p[m - 1].finish_time_ >= p[m].arrive_time_) ? p[m - 1].finish_time_: p[m].arrive_time_) +p[m].service_time_;
			p[m].start_time_ = p[m].finish_time_ - p[m].service_time_;
		}
		int i = 0;
		for (int n = m + 1; n <= static_cast<int>(p.size()) - 1; n++)
		{
			if (p[n].arrive_time_ <= p[m].finish_time_)
			{
				i++;
			}
			else
			{
				break;
			}
		}
		if (m != static_cast<int>(p.size()) - 1)
		{
			float min = p[m + 1].service_time_;
			int next = m + 1;
			for (int k = m + 1; k < m + i; k++)
			{
				if (p[k + 1].service_time_ < min)
				{
					min = p[k + 1].service_time_;
					next = k + 1;
				}
			}
			std::swap(p[m + 1], p[next]);
		}
	}
	for (auto& x : p)
	{
		x.turnaround_time_ = x.finish_time_ - x.arrive_time_;
		x.weighted_turnaround_time_ = x.turnaround_time_ / x.service_time_;
		list.push_back(x.p_name_);
	}
}

void rr_subfunction(std::vector<pcb>& p, std::vector<std::string>& list, const float& rr)
{
	std::deque<pcb> queue;
	std::vector<pcb> temp;
	int i = 1;
	queue.push_back(p.front());
	float time = p.front().arrive_time_;
	while (temp.size() != p.size())
	{
		rr_set_start_time(queue, time);
		if (!queue.empty())
		{
			if (queue.front().remaining_time_ <= rr)
			{
				time += queue.front().remaining_time_;
				queue.front().remaining_time_ = 0;
				queue.front().finish_ = true;
			}
			else
			{
				time += rr;
				queue.front().remaining_time_ -= rr;
			}
		}
		else
		{
			time = p[i].arrive_time_;
			queue.push_back(p[i]);
			i++;
			if (queue.front().remaining_time_ <= rr)
			{
				rr_set_start_time(queue, time);
				time += queue.front().remaining_time_;
				queue.front().remaining_time_ = 0;
				queue.front().finish_ = true;
			}
			else
			{
				rr_set_start_time(queue, time);
				time += rr;
				queue.front().remaining_time_ -= rr;
			}
		}
		while (i < static_cast<int>(p.size()) && p[i].arrive_time_ <= time)
		{
			queue.push_back(p[i]);
			i++;
		}
		list.push_back(queue.front().p_name_);
		if (queue.front().finish_)
		{
			queue.front().finish_time_ = time;
			temp.push_back(queue.front());
			queue.pop_front();
		}
		else
		{
			pcb t = queue.front();
			queue.pop_front();
			queue.push_back(t);
		}
	}
	p.assign(temp.begin(), temp.end());
	sort_process(p);
	for (auto& x : p)
	{
		x.turnaround_time_ = x.finish_time_ - x.arrive_time_;
		x.weighted_turnaround_time_ = x.turnaround_time_ / x.service_time_;
	}
	std::vector<pcb>().swap(temp);
}


void rr_set_start_time(std::deque<pcb>& queue, const float& time)
{
	if (!queue.empty() && queue.front().flag_ == false)
	{
		queue.front().start_time_ = time;
		queue.front().flag_ = true;
	}
}

void hrrn_subfunction(std::vector<pcb>& p, std::vector<std::string>& list)
{
	for (int i = 0; i < static_cast<int>(p.size()); i++)
	{
		p.front().flag_ = true;
		if (p.front().flag_ && !(list.empty()))
		{
			if (const auto it = std::ranges::find_if(p, [&list](const pcb& a_pcb)
			{
				return a_pcb.p_name_ == list.back();
			}); p.front().arrive_time_ > it->finish_time_)
			{
				p.front().start_time_ = p.front().arrive_time_;
			}
			else
			{
				p.front().start_time_ = it->finish_time_;
			}
		}
		p.front().finish_time_ = p.front().service_time_ + p.front().wait_time_ + p.front().arrive_time_;
		p.front().turnaround_time_ = p.front().finish_time_ - p.front().arrive_time_;
		p.front().weighted_turnaround_time_ = p.front().turnaround_time_ / p.front().service_time_;
		list.push_back(p.front().p_name_);
		calculate_response_ratio(p);
		std::ranges::sort(p, [](const pcb& a_pcb, const pcb& b_pcb)
		{
			return a_pcb.prior_ > b_pcb.prior_;
		});
	}
	sort_process(p);
}

void calculate_response_ratio(std::vector<pcb>& p)
{
	for (int i = 0; i < static_cast<int>(p.size()); i++)
	{
		if (p[i].flag_)
		{
			p[i].prior_ = 0;
			continue;
		}
		if (p[i].arrive_time_ < p.front().finish_time_)
		{
			p[i].wait_time_ = p.front().finish_time_ - p[i].arrive_time_;
		}
		p[i].prior_ = p[i].wait_time_ / p[i].service_time_ + 1;
	}
}
