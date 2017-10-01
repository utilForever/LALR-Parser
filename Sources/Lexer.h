#ifndef LEXER_H
#define LEXER_H

#include <cassert>

enum class Symbol
{
	LETTER,
	BLANK,
	DIGIT,
	OTHER,
	NEWLINE,
	INDICATOR
};

enum class TokenType
{
	// Keywords
	KEYWORD_INT,
	KEYWORD_CHAR,
	KEYWORD_DOUBLE,
	KEYWORD_VOID,
	KEYWORD_IF,
	KEYWORD_ELSE,
	KEYWORD_WHILE,
	KEYWORD_FOR,
	KEYWORD_BREAK,
	KEYWORD_CONTINUE,
	KEYWORD_GOTO,
	KEYWORD_RETURN,
	KEYWORD_READ,
	KEYWORD_WRITE,

	// Operators
	// Assignment operators
	OP_ASSIGN,
	// Arithmetic operators
	OP_ADD,
	OP_SUB,
	OP_MUL,
	OP_DIV,
	OP_MOD,
	// Logical operators
	OP_NOT,
	OP_AND,
	OP_OR,
	// Comparison operators
	OP_EQUAL,
	OP_NOTEQUAL,
	OP_LESSTHAN,
	OP_GREATERTHAN,
	OP_LESSTHANEQUAL,
	OP_GREATERTHANEQUAL,

	// Punctuations
	PUNCT_COMMA,
	PUNCT_SEMICOLON,
	PUNCT_COLON,
	PUNCT_LPAREN,
	PUNCT_RPAREN,
	PUNCT_LBRACE,
	PUNCT_RBRACE,
	PUNCT_LBRACK,
	PUNCT_RBRACK,

	// Identifier
	ID,

	// Number
	NUM_INT,
	NUM_DOUBLE,
	NUM,

	// Char
	CHAR,

	// String literal
	STRING_LITERAL,

	// Undefined or error token
	ERROR,

	// Not really token
	UNKNOWN
};

struct Token
{
	// Constructors
	Token(TokenType _token = TokenType::ERROR) : token(_token)
	{
		val.numVal = 0;
	}

	Token(TokenType _token, char ch) : token(_token)
	{
		val.chVal = ch;
	}

	Token(TokenType _token, int num) : token(_token)
	{
		val.numVal = num;
	}

	Token(TokenType _token, char* str) : token(_token)
	{
		val.strVal = str;
	}

	Token(TokenType _token, double d) : token(_token)
	{
		val.fpVal = d;
	}

	// Destructor
	~Token()
	{
		if (token == TokenType::STRING_LITERAL ||
			token == TokenType::NUM_INT ||
			token == TokenType::NUM_DOUBLE ||
			token == TokenType::NUM ||
			token == TokenType::ID)
		{
			delete val.strVal;
		}
	}

	// Interface for accessing internal data
	char GetChVal()
	{
		assert(token == TokenType::CHAR);
		return val.chVal;
	}

	int GetNumVal()
	{
		assert(token == TokenType::NUM_INT);
		return val.numVal;
	}

	char* GetStrVal()
	{
		assert(token == TokenType::STRING_LITERAL);
		return val.strVal;
	}

	double GetFpVal()
	{
		assert(token == TokenType::NUM_DOUBLE);
		return val.fpVal;
	}

	TokenType token;
	union
	{
		char chVal;
		int numVal;
		char* strVal;
		double fpVal;
	} val;
};

#endif