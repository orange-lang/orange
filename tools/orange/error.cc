#include <orange/error.h>

CMessageType CompilerMessage::type() const { return m_type; }

std::string CompilerMessage::what() const { return m_what; }

path CompilerMessage::file_path() const { return m_file_path; }

int CompilerMessage::line_begin() const { return m_line_begin; }

int CompilerMessage::line_end() const { return m_line_end; }

int CompilerMessage::column_begin() const { return m_column_begin; }

int CompilerMessage::column_end() const { return m_column_end; }

CompilerMessage::CompilerMessage(CMessageType type, std::string what, path filePath, int lineBegin, int lineEnd, int colBegin, int colEnd) {
	m_type = type;
	m_what = what;
	m_file_path = filePath; 
	m_line_begin = lineBegin; 
	m_line_end = lineEnd;
	m_column_begin = colBegin; 
	m_column_end = colEnd; 
}