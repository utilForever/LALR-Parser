#ifndef LEXER_H
#define LEXER_H

#include "Utils.h"

#include <cassert>
#include <fstream>

enum class Symbol : int
{
	UNDEFINED	= 00,
	LETTER		= 01,
	BLANK		= 02,
	DIGIT		= 04,
	OTHER		= 010,
	NEWLINE		= 020,
	INDICATOR	= 040
};

using SymbolType = std::underlying_type_t<Symbol>;

inline int operator+(const Symbol& symbol)
{
	return static_cast<int>(symbol);
}

inline Symbol operator&(Symbol lhs, Symbol rhs)
{
	return static_cast<Symbol>(static_cast<SymbolType>(lhs) & static_cast<SymbolType>(rhs));
}

inline Symbol& operator&=(Symbol& lhs, Symbol rhs)
{
	lhs = static_cast<Symbol>(static_cast<SymbolType>(lhs) & static_cast<SymbolType>(rhs));
	return lhs;
}

inline Symbol operator|(Symbol lhs, Symbol rhs)
{
	return static_cast<Symbol>(static_cast<SymbolType>(lhs) | static_cast<SymbolType>(rhs));
}

inline Symbol& operator|=(Symbol& lhs, Symbol rhs)
{
	lhs = static_cast<Symbol>(static_cast<SymbolType>(lhs) | static_cast<SymbolType>(rhs));
	return lhs;
}

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

	// End of file
	END_OF_FILE,

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
	char GetChVal() const
	{
		assert(token == TokenType::CHAR);
		return val.chVal;
	}

	int GetNumVal() const
	{
		assert(token == TokenType::NUM_INT);
		return val.numVal;
	}

	char* GetStrVal() const
	{
		assert(token == TokenType::STRING_LITERAL);
		return val.strVal;
	}

	double GetFpVal() const
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

class Lexer
{
public:
	explicit Lexer(const char* fileName);
	virtual ~Lexer();
	Lexer(const Lexer&) = delete;
	Lexer(Lexer&&) = delete;
	Lexer& operator=(const Lexer&) = delete;
	Lexer& operator=(Lexer&&) = delete;

	virtual Token* GetToken();

	int GetLineNumber() const
	{
		return m_lineNumber;
	}

protected:
	class CommentDFA
	{
	public:
		explicit CommentDFA(Lexer& lexer) : m_lexer(lexer)
		{
			
		}

		void GetToken(Token* token);

	private:
		Lexer& m_lexer;
	};

	class StringDFA
	{
	public:
		explicit StringDFA(Lexer& lexer) : m_lexer(lexer)
		{
			
		}

		void GetToken(Token* token);

	private:
		Lexer& m_lexer;

		static int m_strMaxLength;
	};

	class CharDFA
	{
	public:
		explicit CharDFA(Lexer& lexer) : m_lexer(lexer)
		{
			
		}

		void GetToken(Token* token);

	private:
		Lexer& m_lexer;

		static int m_charSeqMaxLength;
		static char m_reservedEscSeq[10];
	};
	
	class NumericsDFA
	{
	public:
		explicit NumericsDFA(Lexer& lexer) : m_lexer(lexer)
		{
			
		}

		void GetToken(Token* token);

	private:
		Lexer& m_lexer;

		static int m_wordLength;
		static unsigned int m_bufferMaxSize;
	};

	class IdentifierDFA
	{
	public:
		explicit IdentifierDFA(Lexer& lexer) : m_lexer(lexer)
		{
			m_hashKeywords.Build(m_keywords);
		}

		void GetToken(Token* token);

		const char* GetKeyword(const char* str)
		{
			return m_hashKeywords.Match(str);
		}

	private:
		Lexer& m_lexer;
		HashingTab m_hashKeywords;
		
		static int m_idMaxLength;
		static const char* m_keywords[];
	};

	IdentifierDFA m_identifierDFA;
	NumericsDFA m_numericsDFA;
	CharDFA m_charDFA;
	StringDFA m_stringDFA;
	CommentDFA m_commentDFA;

private:
	std::ifstream m_sourceFile;
	char* m_lineBuffer;
	char* m_lineBufferTail;

	char* m_tokenHead;
	char* m_tokenIter;

	static int m_lineBufferSize;
	static unsigned int m_tokenMaxLength;

	int m_lineNumber;
};

#endif