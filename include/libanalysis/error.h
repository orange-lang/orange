//
// Copyright 2014-2016 Robert Fratto. See the LICENSE.txt file at the top-level
// directory of this distribution.
//
// Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
// may not be copied, modified, or distributed except according to those terms.
//

#pragma once

#include <string>
#include <vector>

namespace orange { namespace analysis {
	class NodeTypeContext;

	enum MessageSeverity { INFO, WARNING, ERROR, FATAL };

	struct AnalysisMessage {
		/// Indicates the severity of the message
		MessageSeverity severity;

		/// The contents of the message
		std::string message;

		/// The nodeID (if any) the message is tied to
		int nodeID;

		/// The context (if any) the message is tied to
		NodeTypeContext* context;
	};

	struct AnalysisMessageLog {
	private:
		std::vector<AnalysisMessage> mMessages;
	public:
		std::vector<AnalysisMessage> GetMessages() const;

		AnalysisMessageLog();
	};
}}