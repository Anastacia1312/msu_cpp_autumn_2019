#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

enum class Token
{
	PLUS,
	MINUS, 
	STAR, 
	SLASH, 
	NUMBER, 
	END,
	INV,
};

Token get_token (const char*& expr)
{
	while (const auto c = *expr++) 
	{
		switch(c) 
		{ 
			case '+': 
				return Token::PLUS;
			case '-': 
				return Token::MINUS;  
			case '*': 
				return Token::STAR; 
			case '/': 
				return Token::SLASH; 
			case ' ': 
				continue; 
		} 
		if ((c>='0') && (c<='9')) 
		{ 
			bool tmp = false; 
			for (auto c = *expr; (c>='0') && (c<='9'); ++expr) 
			{ 
				tmp = true; 
				c = *expr;
            } 
            --expr; 
            if (tmp) --expr; 
            return Token::NUMBER; 
        } 
        return Token::INV;
    }
    return Token::END;
}

int get_number (const char*& expr)
{ 
	auto token = get_token(expr); 
	if (token == Token::NUMBER) 
	{ 
		auto c = *expr; 
		int number = 0;
		int i = 1;
		int j = 1;
		while ((c<='9') && (c>='0')) 
		{ 
			number += static_cast<int>(c-'0') * i; 
			c = *--expr; 
			i = i * 10; 
			j++; 
		} 
		for (int k = 0; k < j; k++) 
			++expr;
		return number; 
	} 
	else if (token == Token::MINUS) 
		return - get_number (expr); 
	else 
		throw std::invalid_argument("Invalid symbol in expression");
}

int func (const char*& expr, Token &oper)
{ 
	int result = get_number (expr); 
	oper = get_token (expr); 
	if (oper == Token::INV)
		throw std::invalid_argument("Invalid symbol in expression");
	while (oper == Token::STAR || oper == Token::SLASH || oper == Token::NUMBER) 
	{
		if (oper == Token::STAR) 
			result = result * get_number (expr);
		else if (oper == Token::SLASH) 
		{ 
			int div = get_number (expr); 
			if (div != 0) 
				result = result / div; 
			else 
				throw std::invalid_argument("Division by zero"); 
		} 
		else 
			throw std::invalid_argument("Wrong expression"); 
		oper = get_token (expr); 
	}
	return result;
}

int func_sign (const char*& expr)
{ 
	Token oper = Token::PLUS; 
	int result = func (expr, oper); 
	while (oper != Token::END) 
	{ 
		if (oper == Token::PLUS) 
			result = result + func (expr, oper); 
		else if (oper == Token::MINUS) 
			result = result - func (expr, oper);
	} 
	return result; 
}

int main(int argc, char* argv[]) 
{
    try
    {
        if (argc < 2) 
        {
            throw std::invalid_argument("No argument");  
        } 
        const char* expr = argv[1]; 
        std::cout << func_sign (expr) << std::endl;
        return 0;
    }
	catch (std::invalid_argument&exception) 
	{ 
        std::cout << exception.what() << std::endl;
        return 1;
	}
}