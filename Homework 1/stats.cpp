// Provided by:  Tahsin Parvez
// Email Address: tparvez000@citymail.cuny.edu
// FILE: stats.cpp

#include "stats.h"
#include <cassert> //	Assertion function

namespace main_savitch_2C 
{

	statistician::statistician()
	//constrtucts a statistician that can do basic statistics with numbers stored
	{
		m_len = 0;
		m_sum = 0;
		
	}

	void statistician::next(double r)
	{
		// Call on the length, sum, mean, min, and max functions
		// Update the private values based on the functions
		m_len = m_len + 1;

		m_sum += r;

		if (m_len == 1){
			m_min = r;
			m_max = r;
		}
		else if (r > m_max){
			m_max = r;
		}
		else if (r < m_min){
			m_min = r;
		}
	}

	void statistician::reset()
	{
		m_len = 0;
		m_sum = 0;
		m_min = 0;
		m_max = 0;
	}

	int statistician::length() const{return m_len;}
	double statistician::sum() const{return m_sum;}

	double statistician::mean() const
	{
		assert(m_len > 0);
		return (m_sum / m_len);
	}
	
	double statistician::minimum() const
	{
		assert(m_len > 0);
		return m_min;
	}

	double statistician::maximum() const
	{
		assert(m_len > 0);
		return m_max;
	}


	statistician operator +(const statistician& s1, const statistician& s2) 
	{
		statistician temp;
		
		temp.m_sum = s1.m_sum + s2.m_sum;
		temp.m_len = s1.m_len + s2.m_len;
		
		if (s1.m_len == 0)
		{
			temp.m_min = s2.m_min;
			temp.m_max = s2.m_max;
		}
		if (s2.m_len == 0)
		{
			temp.m_min = s1.m_min;
			temp.m_max = s1.m_max;
		}
		if (s1.m_len > 0 && s2.m_len > 0)
		{
			if (s1.m_min < s2.m_min)
				temp.m_min = s1.m_min;
			else
				temp.m_min = s2.m_min;
			if (s1.m_max > s2.m_max)
				temp.m_max = s1.m_max;
			else
				temp.m_max = s2.m_max;
		}


		return temp;
	}
	

	statistician operator *(double scale, const statistician& s)
	{
		statistician temp;

		temp.m_sum = s.m_sum * scale;
		temp.m_len = s.m_len;

		// If statement to deal with the negative scaling edge case. Max will invert into min scaled by input. 
		if (scale > 0)
		{
			temp.m_min = s.m_min * scale;
			temp.m_max = s.m_max * scale;
		}
		else
		{
			temp.m_min = s.m_max * scale;
			temp.m_max = s.m_min * scale;
		}
		
		return temp;
	}


	bool operator ==(const statistician& s1, const statistician& s2)
	{
		if (s1.length() == 0 && s2.length() == 0){
				return true;
			}
			else if (s1.length() == s2.length() && s1.sum() == s2.sum() && s1.maximum() == s2.maximum() && s1.minimum() == s2.minimum()){
				return true;
			}			
			else{
				return false;
			}
		
	}
}