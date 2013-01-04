#pragma once

#include <string>
#include <iostream>

class Log{
	private:
		std::string m_buf;
		std::ostream *m_os;
	public:
		Log();
		void open(std::ostream &os);
		void add(std::string str);
		std::string buf() const;
		void clear();

		static Log main;		
};

