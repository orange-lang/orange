/*
** Copyright 2014-2015 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/
#pragma once

#include <string>

/**
 * A flag that can be set for any given state.
 */
class StateFlag {
private:
	/// Determines whether or not the flag was used while parsing.
	bool m_used = false;

	/// Determines whether or not the flag needs a value.
	bool m_needsValue = false;

	/// The shortform, 1-character name of this flag. Triggered by -.
	std::string m_shortform_name = "";

	/// The longform, multi-character name of this flag. Triggered by --.
	std::string m_longform_name = "";
	
	/// The description of the flag. Printed out in help.
	std::string m_description;

	/// Determines value of the flag while parsing.
	std::string m_value = "";
public:
	/// Gets whether or not the flag has a short name.
	bool hasShortName() const;
	
	/// Gets whether or not the flag has a long name.
	bool hasLongName() const;
	
	/// Gets the short form name of this flag.
	std::string getShortName() const;

	/// Gets the long form name of this flag.
	std::string getLongName() const;

	/// Gets the value of the flag, found while parsing.
	std::string getValue() const;
	
	/// Gets whether or not this flag needs a value/arg.
	bool getNeedsValue() const;

	/// Returns whether or not the flag was used in the command line.
	bool getUsed() const;

	/**
	 * Force set this flag to be used. This is useful for forcing behavior.
	 * @param used True if this flag was used, false otherwise.
	 */
	void setUsed(bool used);
	
	/** 
	 * Assigns the value to this flag. 
	 * @param val The value to assign.
	 */
	void setValue(std::string val);

	/**
	 * Give a description to this flag to be printed out in a help menu.
	 * @param description The description of this flag.
	 */
	void setDescription(std::string description);

	/**
	 * Creates a state flag with an initial name.
	 * If this name is more than 1 character long, it'll be used
	 * as the longform name (i.e., triggered by --flagName).
	 * If the name is just one character long, it'll be used as
	 * the shortform name (i.e., triggered by -flagName).
	 * @param flagName
	 *	The flag name to give to this StateFlag.
	 *  Must not be empty.
	 * @param needsValue Optional. Whether or not this argument needs a value.
	 */
	StateFlag(std::string flagName, bool needsValue = false);

	/**
	 * Creates a state flag with a short name and a long name.
	 * @param shortName The short name to use for the flag. Must not be empty.
	 * @param longName The long name to use for the flag. Must not be empty.
	 * @param needsValue Optional. Whether or not this argument needs a value.
	 */
	StateFlag(std::string shortName, std::string longName, bool needsValue = false);
};
