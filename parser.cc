#include <iostream>
#include "parser.h"

static bool IsType(Lexeme *lexeme) {
	switch (lexeme->type) {
		case KEYWORD_INT:
		case KEYWORD_FLOAT:
		case KEYWORD_DOUBLE:
		case KEYWORD_INT8:
		case KEYWORD_UINT8:
		case KEYWORD_INT16:
		case KEYWORD_UINT16:
		case KEYWORD_INT32:
		case KEYWORD_UINT32:
		case KEYWORD_INT64:
		case KEYWORD_UINT64:
			return true; 
			break;
		default:
			return false;
			break;
	}

	return false; 
}

Lexeme* Parser::getLexeme() const {
	if (lookahead >= lexemes.size()) {
		return nullptr;
	} else {
		return lexemes[lookahead];
	}
}

bool LexemeIs(Lexeme *lex, LexemeType type) {
	if (lex == nullptr) {
		return false; 
	} 
	return lex->type == type;
}

/*
	declaration	::=		TYPE decl_assign opt_assigns
	opt_assigns	::=		',' decl_assign opt_assigns | $
	decl_assign	::=		ID opt_assign
	opt_assign  ::=		assign_ops expression | $
	assign_ops	::=		'=' | '<-'
*/
ODeclaraions *Parser::parseDeclaration() {
	ODeclaraions *decl = new ODeclaraions();
	LexemeType type; 

	if (IsType(getLexeme())) {
		type = getLexeme()->type; 
		lookahead++;
	} else {
		std::cerr << "ERROR: Unknown token " << getLexeme()->string() << ". Expected type." << std::endl;
		lookahead++;
		return nullptr;
	}

	while (LexemeIs(getLexeme(), ID)) {
		OVariable* var = new OVariable();
		var->type = type;
		var->name = getLexeme()->value.string; 
		lookahead++;

		if (LexemeIs(getLexeme(), ASSIGN)) {
			lookahead++;
			var->value = parseExpression();
		}

		decl->vars.push_back(var);

		if (LexemeIs(getLexeme(), COMMA)) {
			lookahead++;
		} else {
			break; 
		}
	}

	return decl;
}

// 	primary			::= 	'(' expression ')' | NUMBER | ID
OExpression *Parser::parsePrimary() {
	if (LexemeIs(getLexeme(), OPEN_PAREN)) {
		lookahead++;
		OExpression *ret = parseExpression();
		if (LexemeIs(getLexeme(), CLOSE_PAREN)) {
			lookahead++; 
			return ret; 
		} else {
			std::cerr << "ERROR: Unknown token " << getLexeme()->string() << ". Expected )." << std::endl;
			lookahead++;
			return nullptr;
		}
	} else if (LexemeIs(getLexeme(), ID)) {
		OID *id = new OID;
		id->name = getLexeme()->value.string;
		lookahead++;

		if (LexemeIs(getLexeme(), OPEN_PAREN)) {
			lookahead++;

			OFuncCall *funcC = new OFuncCall;
			funcC->name = id->name;

			while (LexemeIs(getLexeme(), CLOSE_PAREN) == false) {
				if (LexemeIs(getLexeme(), COMMA)) {
					lookahead++;
				} 

				funcC->args.push_back(parseExpression());
			}

			if (LexemeIs(getLexeme(), CLOSE_PAREN)) {
				lookahead++;
			}

			delete id; 
			return funcC;
		}

		return id;
	} 

	switch (getLexeme()->type) {
		case TYPE_FLOAT: 
			{
				OFloat *f = new OFloat; 
				f->type = getLexeme()->type;
				f->value = getLexeme()->value.floatVal;
				lookahead++;
				return f; 
			}
		case TYPE_DOUBLE:
			{
				ODouble *d = new ODouble; 
				d->type = getLexeme()->type;
				d->value = getLexeme()->value.doubleVal;
				lookahead++;
				return d; 		
			}
		case TYPE_INT8:
		case TYPE_INT16:
		case TYPE_INT32:
		case TYPE_INT64:
			{
				OInt *i = new OInt;
				i->type = getLexeme()->type;
				i->value = getLexeme()->value.int64;
				lookahead++;
				return i;
			}
		case TYPE_UINT8:
		case TYPE_UINT16:
		case TYPE_UINT32:
		case TYPE_UINT64:
			{
				OUint *ui = new OUint;
				ui->type = getLexeme()->type;
				ui->value = getLexeme()->value.uint64;
				lookahead++;
				return ui;
			}
		default:
			std::cerr << "ERROR: Unknown token " << getLexeme()->string() << ". Expected id or constant." << std::endl;
			lookahead++;
			return nullptr;
	}
}

/*
	expression	::= 	assign_expr
	assign_expr ::=		add_expr ( ('=' | '+=' | '-=' | '*=' | '/=' | '%=') add_expr) *
	add_expr	 	::=		mult_expr ( ('-' | '+') mult_expr) *
	mult_expr		::= 	primary ( ('*' | '/') primary ) *
*/
OExpression *Parser::parseExpression1(OExpression *LHS, int min_prec) {
	while (1) {
		if (getLexeme() == nullptr)
			return LHS;

		int current_prec = Precedence(getLexeme()->type);
		if (current_prec < min_prec) {
			return LHS; 
		}

		Lexeme* op = getLexeme();
		if (op == nullptr) 
			return LHS;

		if (Precedence(op->type) == -1) {
			std::cerr << "ERROR: Unknown token " << op->string() << ". Expected operator." << std::endl;
			return (OExpression *)nullptr;
		}
		lookahead++;

		OExpression *RHS = parsePrimary();
		if (RHS == nullptr) {
			return nullptr;
		}

		if (getLexeme() != nullptr) {
			int next_prec = Precedence(getLexeme()->type); 
			if (current_prec < next_prec) {
				RHS = parseExpression1(RHS, next_prec);
			}
		}		

		if (op->type == ASSIGN) {
			OID* LHSID = dynamic_cast<OID*>(LHS);
			if (LHSID == nullptr) {
				std::cerr << "destination of = must be a variable\n";
				return nullptr; 
			}

			OVariable *v = new OVariable();
			v->type = LHSID->type; 
			v->name = LHSID->name;
			v->value = RHS; 
			LHS = v; 
		} else {
			OBinopStatement* stmt = new OBinopStatement();
			stmt->LHS = LHS; 
			stmt->RHS = RHS; 
			stmt->op = op->type;
			LHS = stmt;
		}
	}
}

OExpression *Parser::parseExpression() {
	OExpression *LHS = parsePrimary();
	return parseExpression1(LHS, 0);
}


/*
	function		::= 	'def' opt_id statements 'end'
	opt_id			::= 	ID opt_parens | '(' opt_args ')'
	opt_parens 	::=		'(' opt_args ')' | $
*/
OFunction *Parser::parseFunction() {
	OFunction *ret = new OFunction;

	if (getLexeme()->type != KEYWORD_DEF) {
		std::cerr << "ERROR: Unknown token " << getLexeme()->string() << ". Expected def." << std::endl;
		lookahead++;
		return nullptr;
	} 
	lookahead++;

	// opt_id 
	if (LexemeIs(getLexeme(), ID)) { 
		ret->name = getLexeme()->value.string; 
		lookahead++;

		// opt_parens 
		if (LexemeIs(getLexeme(), OPEN_PAREN)) {
			lookahead++;

			ret->args = parseArgs();

			if (LexemeIs(getLexeme(), CLOSE_PAREN)) {
				lookahead++; 
			} else {
				std::cerr << "ERROR: Unknown token " << getLexeme()->string() << ". Expected )." << std::endl;
				lookahead++;
				return nullptr;
			}
		}
	} else if (LexemeIs(getLexeme(), OPEN_PAREN)) {
		lookahead++;

		ret->args = parseArgs();

		if (LexemeIs(getLexeme(), CLOSE_PAREN)) {
			lookahead++;
		} else {
			std::cerr << "ERROR: Unknown token " << getLexeme()->string() << ". Expected )." << std::endl;
			lookahead++;
			return nullptr;
		}
	} else {
		std::cerr << "ERROR: Unknown token " << getLexeme()->string() << ". Expected id or anonymous function." << std::endl;
		lookahead++;
		return nullptr;
	}

	// TODO: parse body 
	ret->block = Parse(false);

	if (getLexeme()->type != KEYWORD_END) {
		std::cerr << "ERROR: Unknown token " << getLexeme()->string() << ". Expected end." << std::endl;
		lookahead++;
		return nullptr;
	} 
	lookahead++;

	return ret;
}

/*
	opt_args		::=		args | $
	args 				::=		arg opt_comma
	arg 				::=		opt_type ID opt_comma
	opt_type		::=		TYPE | $
	opt_comma		::=		',' args
*/
std::vector<OID *> Parser::parseArgs() {
	std::vector<OID *> list;

	while (IsType(getLexeme()) || LexemeIs(getLexeme(), ID)) {
		OID *id = new OID; 

		if (IsType(getLexeme())) {
			id->type = getLexeme()->type; 
			lookahead++;
		}

		if (LexemeIs(getLexeme(), ID)) {
			id->name = getLexeme()->value.string; 
			lookahead++;
		} else {
			std::cerr << "ERROR: Unknown token " << getLexeme()->string() << ". Expected id." << std::endl;
			lookahead++;
			return list;
		}

		list.push_back(id);

		if (LexemeIs(getLexeme(), COMMA)) {
			lookahead++;
		} else {
			break; 
		}
	}

	return list;
}


/*
	start 			::=		statements
	statements	::= 	statement statements
	statement 	::= 	function | expression | declaration | $
*/
OBlock *Parser::Parse(bool defaultIsError) {
	OBlock *globalBlock = new OBlock;

	// parse statement until there's nothing left to parse 
	Lexeme *lexeme = nullptr;
	while ((lexeme = getLexeme())) {
		switch (lexeme->type) {
			case KEYWORD_DEF: 
				// parse function 
				globalBlock->Statements.push_back(parseFunction());
				break;
			case OPEN_PAREN:
			case TYPE_FLOAT:
			case TYPE_DOUBLE:
			case TYPE_INT8:
			case TYPE_UINT8:
			case TYPE_INT16:
			case TYPE_UINT16:
			case TYPE_INT32:
			case TYPE_UINT32:
			case TYPE_INT64:
			case TYPE_UINT64:
			case ID: 
				// parse expression 
				globalBlock->Statements.push_back(parseExpression());
				break; 
			case KEYWORD_INT:
			case KEYWORD_FLOAT:
			case KEYWORD_DOUBLE:
			case KEYWORD_INT8:
			case KEYWORD_UINT8:
			case KEYWORD_INT16:
			case KEYWORD_UINT16:
			case KEYWORD_INT32:
			case KEYWORD_UINT32:
			case KEYWORD_INT64:
			case KEYWORD_UINT64:
				// parse declaration
				globalBlock->Statements.push_back(parseDeclaration());
				break; 
			default:
				if (defaultIsError) {
					std::cerr << "ERROR: Invalid token " << lexeme->string() << "." << std::endl;
					lookahead++;			
				} else return globalBlock; 
				break;
		}
	}

	return globalBlock;
}
