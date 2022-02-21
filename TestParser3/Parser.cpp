#include "Parser.h"

#include <iostream>

namespace simpleparser{
    void Parser::parse(std::vector<Token> &tokens){
        mCurrentToken = tokens.begin();
        mEndToken = tokens.end();

        while(mCurrentToken != mEndToken){
            //std::cout << "Tester: " << mCurrentToken->mText << std::endl;
            ++mCurrentToken;
        }
    }
}


/*
<EXPR> ::= <simple-EXPR>
<simple-EXPR>	::=  <concatenation> | <basic-OP> 
<concatenation> ::= <basic-OP> <simple-EXPR> 
<basic-OP>	::= <star> | <plus> | <count> | <character>
<plus>  ::= <EXPR> "+" <EXPR>
<star>	::=	<character> "*"
<count> ::= <character>  "{" any number "}"
<group>	::=	"(" <EXPR> ")"
<any>	::=	"."
<character>	::=	 any non metacharacter 


<EXPR> ::= <simple-EXPR>
<simple-EXPR>	::=  <concatenation> | <BIG> 
<concatenation> ::= <BIG> <simple-EXPR> 
<BIG>	::= <star> | <plus> | <count> | <character>
<plus>  ::= <EXPR> "+" <EXPR>
<star>	::=	<character> "*"
<count> ::= <character>  "{" any number "}"
<group>	::=	"(" <EXPR> ")"
<any>	::=	"."
<character>	::=	 any non metacharacter 

<EXPR> ::= <or>  |  <simple-EXPR>
<or>	::=	<simple-EXPR> "+" <EXPR>
<simple-EXPR>	::=  concatenation> | <basic-RE> 
<concatenation> ::= <basic-RE> <simple-EXPR> 
<basic-RE>	::= <group> | <repetition> | <counter> | <lowercase> | <output> | <element>
<output> ::= <element> "\O" "{" <digit> "}" | <element> "\O"
<lowercase> ::= <EXPR> "\I"
<repetition>	::=	<element> "*"
<counter> ::= <element>  "{" <digit> "}"
<element>	::=	 <char> | <any> 
<group>	::=	"(" <EXPR> ")"
<digit> ::= "0" | "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9"
<any>	::=	"."
<char>	::= any non metacharacter 
*/