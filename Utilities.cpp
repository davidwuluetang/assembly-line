// Name: David Tang
// Seneca Student ID: 150276228
// Seneca email: dtang30@myseneca.ca
// Date of completion: Ocotober 26, 2023
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.
#include <iostream>
#include <string>
#include "Utilities.h"
using namespace std;

namespace sdds {
	char Utilities::m_delimiter = '\0';

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {
		size_t pos{};
		string token;

		pos = str.find(m_delimiter, next_pos);
		if (pos == next_pos) {
			more = false;
			const string msg = "Delimiter found at" + to_string(next_pos);
			throw msg;
		}
		else {
			if (pos == string::npos)
				more = false;
			token = str.substr(next_pos, pos - next_pos);
			next_pos = pos + 1;
			if (token.front() == ' ') {
				pos = token.find_first_not_of(' ');
				token.erase(0, pos);
			}
			if (token.back() == ' ') {
				pos = token.find_last_not_of(' ');
				token.erase(pos + 1);
			}
			if (m_widthField < token.length())
				m_widthField = token.length();
		}
		return token;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}