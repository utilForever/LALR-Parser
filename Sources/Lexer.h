#ifndef LEXER_H
#define LEXER_H

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

#endif