/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#include <stdexcept>
#include <grove/Module.h>
#include <grove/Namespace.h>

std::string Module::getFile() const
{
	return m_file;
}

Builder* Module::getBuilder() const
{
	return m_builder;
}

Namespace* Module::getNamespace() const
{
	return m_namespace;
}

void Module::parse()
{
	extern FILE* yyin;
	extern int yyparse(Module* mod);
	extern int yyonce;
	extern void yyflushbuffer();
	
	
	auto file = fopen(getFile().c_str(), "r");
	if (file == nullptr)
	{
		throw std::runtime_error("Module couldn't open file.");
	}
	
	yyflushbuffer();
	yyonce = 0;
	yyin = file;
	yyparse(this);
	
	fclose(file);
}

Block* Module::getBlock() const
{
	if (m_ctx.size() == 0)
	{
		throw std::runtime_error("No blocks have been added to module.");
	}
	
	return m_ctx.top();
}

void Module::pushBlock(Block *block)
{
	if (block == nullptr)
	{
		throw std::invalid_argument("block must not be nullptr.");
	}
	
	m_ctx.push(block);
}

Block* Module::popBlock()
{
	if (m_ctx.size() == 0)
	{
		throw std::invalid_argument("No blocks have been added to module.");
	}
	
	auto popped = m_ctx.top();
	m_ctx.pop();
	return popped;
}

Module::Module(Builder* builder, std::string filePath)
{
	if (builder == nullptr)
	{
		throw std::invalid_argument("builder must not be null.");
	}
	
	if (llvm::sys::fs::exists(llvm::Twine(filePath)) == false)
	{
		throw std::invalid_argument("file must exist");
	}
	
	m_builder = builder;
	m_namespace = new Namespace("local");
	m_file = filePath;
	
	parse();
}