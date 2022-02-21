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

*/