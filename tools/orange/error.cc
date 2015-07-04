/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level 
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file 
** may not be copied, modified, or distributed except according to those terms.
*/ 

#include <orange/error.h>
#include <orange/generator.h>
#include <sstream>

CMessageType CompilerMessage::type() const { return m_type; }

std::string CompilerMessage::what() const { return m_what; }

std::string CompilerMessage::file_path() const { return m_file_path; }

int CompilerMessage::line_begin() const { return m_line_begin; }

int CompilerMessage::line_end() const { return m_line_end; }

int CompilerMessage::column_begin() const { return m_column_begin; }

int CompilerMessage::column_end() const { return m_column_end; }

bool CompilerMessage::hasLineInfo() const {
	// If any of the fields aren't -1, we have info.
	return m_line_begin != -1 || m_line_end != -1 || m_column_begin != -1 || m_column_end != -1; 
}

std::string CompilerMessage::string() const {
	std::stringstream ss;

	ss << m_file_path << ":";

	if (hasLineInfo()) {
		ss << m_line_begin << ":" << m_column_begin << ":"; 
	}

	ss << what();

	return ss.str();
}


CompilerMessage::CompilerMessage(CMessageType type, std::string what, std::string filePath, int lineBegin, int lineEnd, int colBegin, int colEnd) {
	m_type = type;
	m_what = what;
	m_file_path = filePath; 
	m_line_begin = lineBegin; 
	m_line_end = lineEnd;
	m_column_begin = colBegin; 
	m_column_end = colEnd; 
}

CompilerMessage::CompilerMessage(CodeElement element, std::string what) {
	m_type = ERROR; 
	m_what = what; 
	m_file_path = GE::runner()->pathname(); 
	m_line_begin = element.location().row_begin;
	m_line_end = element.location().row_end;
	m_column_begin = element.location().col_begin;
	m_column_end = element.location().col_end;
}


#include <orange/orange.h>
#include "parser.hh"

void yyerror(const char *s) { 
	Runner *activeRunner = GeneratingEngine::sharedEngine()->active();

	CompilerMessage msg(ERROR, s, activeRunner->pathname(), yylloc.first_line, yylloc.last_line, yylloc.first_column, yylloc.last_column); 
	activeRunner->log(msg);
}
