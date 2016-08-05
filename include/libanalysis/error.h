//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <libast/ast.h>

#include <string>
#include <vector>

namespace orange { namespace analysis {
	class NodeTypeContext;

	enum MessageSeverity { INFO, WARNING, ERROR, FATAL };
	
	enum AnalysisError {
		ERROR_UNIMPLEMENTED,
		MISMATCHED_TYPES_FOR_BINDINGS,
		MISSING_DEFAULT_VALUE,
		INVALID_NAME,
		INVALID_VALUE,
		INVALID_TYPE,
		REFERENCE_NOT_FOUND,
		INCOMPATIBLE_TYPES,
		MISSING_RETURN,
		INVALID_PRECEDING_ELSE,
		ELIF_AFTER_ELSE,
		MISSING_YIELD
	};

	struct AnalysisMessage {
		/// Indicates the severity of the message
		MessageSeverity severity;

		/// The specific error that was logged.
		AnalysisError error;

		/// The nodeID (if any) the message is tied to
		int nodeID;

		/// The context (if any) the message is tied to
		NodeTypeContext* context;
		
		AnalysisMessage() { }
		
		AnalysisMessage(MessageSeverity sev, AnalysisError error, int nodeID, NodeTypeContext* ctx) :
			severity(sev), error(error), nodeID(nodeID), context(ctx) { }
	};

	struct AnalysisMessageLog {
	private:
		std::vector<AnalysisMessage> mMessages;
	public:
		std::vector<AnalysisMessage> GetMessages() const;
		
		/// Logs a message, with a provided severity, a node, and context.
		void LogMessage(MessageSeverity severity, AnalysisError error, orange::ast::Node* node, NodeTypeContext* ctx);
		
		/// Logs an AnalysisMessage.
		void LogMessage(AnalysisMessage message);

		AnalysisMessageLog();
	};
}}