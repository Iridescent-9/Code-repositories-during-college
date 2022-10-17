#include "pcb.h"

float pcb::get_turnaround_time() const
{
	return turnaround_time_;
}

float pcb::get_weighted_turnaround_time() const
{
	return weighted_turnaround_time_;
}

std::ostream& operator<<(std::ostream& os, const pcb& p)
{
	os << std::left << std::setw(14) << p.p_name_ << std::left << std::setw(14) << p.arrive_time_ << std::left <<
		std::setw(14) << p.service_time_ << std::left << std::setw(14) << p.start_time_ << std::left << std::setw(14) <<
		p.finish_time_ << std::left << std::setw(14) << p.turnaround_time_ << std::left << std::setw(14) << p.weighted_turnaround_time_;
	return os;
}

pcb::pcb() = default;

pcb::pcb(std::string name, const float a_t, const float s_t) : arrive_time_(a_t), service_time_(s_t),p_name_(std::move(name))
{
	remaining_time_ = service_time_;
}

