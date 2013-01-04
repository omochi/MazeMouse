#include "Log.h"

Log Log::main = Log();

void Log::open(std::ostream &os){
	m_os = &os;
}
void Log::add(std::string str){
	if(m_os)*m_os << str;
	m_buf.append(str);
}
std::string Log::buf() const{
	return m_buf;
}
void Log::clear(){
	m_buf = std::string();
}
