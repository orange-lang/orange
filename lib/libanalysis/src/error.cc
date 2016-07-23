//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#include <libanalysis/error.h>

using namespace orange::analysis;
using namespace orange::ast;

std::vector<AnalysisMessage> AnalysisMessageLog::GetMessages() const {
	return mMessages;
}

void AnalysisMessageLog::LogMessage(MessageSeverity severity, AnalysisError error, Node* node, NodeTypeContext* ctx) {
	AnalysisMessage logMessage;
	logMessage.severity = severity;
	logMessage.error = error;
	logMessage.nodeID = (node != nullptr) ? node->id : -1;
	logMessage.context = ctx;
	
	mMessages.push_back(logMessage);
}

void AnalysisMessageLog::LogMessage(AnalysisMessage message) {
	mMessages.push_back(message);
}

AnalysisMessageLog::AnalysisMessageLog() { }

