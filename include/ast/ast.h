/*
** Copyright 2014-2017 Robert Fratto. See the LICENSE.txt file at the top-level
** directory of this distribution.
**
** Licensed under the MIT license <http://opensource.org/licenses/MIT>. This file
** may not be copied, modified, or distributed except according to those terms.
*/

#pragma once 

#include <memory>
#include <string>
#include <vector>

namespace std {
	template <typename T> 
	using shared_vec = std::vector<std::shared_ptr<T>>;
}

namespace orange { namespace ast {
	class Node;
	class Type;

	struct Node {
	protected:
		Node() {}
	public:
		virtual ~Node() {}
	};

	struct Statement : Node {
	protected: 
		Statement() { }
	};

	struct Expression : Node {
	protected: 
		Expression() { }
	};

	struct Identifier : Expression {
	protected:
		Identifier() { }
	};

	struct AliasDecl : Statement {
		std::string name;
		std::shared_ptr<Type> original;
	};
	
	struct ClassDecl : Statement { 
		std::string name; 
		std::shared_vec<Identifier> supers;
		std::shared_vec<Node> body;
	};

	struct VarDecl : Statement { 
		std::string name; 
		std::shared_ptr<Type> type;
		std::shared_ptr<Expression> value;
	};

	struct GetterStmt : Statement {
		std::shared_vec<Node> body;
	};

	struct SetterStmt : Statement {
		std::shared_ptr<VarDecl> setterVariable;
		std::shared_vec<Node> body;
	};

	struct PropertyDecl : Statement { 
		std::string name; 
		std::shared_ptr<Type> type;
		std::shared_ptr<GetterStmt> getter; 
		std::shared_ptr<SetterStmt> setter; 
	};

	struct EnumDecl : Statement { 
		std::string name;
		std::vector<std::string> members;
	};

	struct FunctionDecl : Statement { 
		std::string name; 
		std::shared_vec<VarDecl> parameters;
		std::shared_ptr<Type> retType;
		std::shared_vec<Node> body;
	};

	struct ExternFuncDecl : Statement { 
		std::string name; 
		std::shared_vec<VarDecl> parameters;
		std::shared_ptr<Type> retType;
	};

	struct ExtensionDecl : Statement { 
		std::string name; 
		std::shared_vec<Identifier> supers;
		std::shared_ptr<Node> body;
	};

	struct InterfaceDecl : Statement { 
		std::string name; 
		std::shared_vec<Identifier> supers; 
		std::shared_ptr<Node> body;
	};

	struct PackageDecl : Statement { 
		std::string name;
	};

	struct ImportDecl : Statement {
		std::string name;	
	};

	struct ArrayExpr : Expression { 
		std::shared_vec<Expression> members;
	};

	struct CastExpr : Expression { 
		std::shared_ptr<Expression> source; 
		std::shared_ptr<Type> targetType;
	};

	enum LoopConditionTime { BEFORE, AFTER };

	struct LoopExpr : Expression { 
		std::shared_ptr<Expression> initializer; 
		std::shared_ptr<Expression> condition; 
		std::shared_ptr<Expression> afterthought; 

		LoopConditionTime checkWhen;

		std::shared_vec<Node> body;
	};

	struct UnaryExpr : Expression { 
		std::string operation;
		std::shared_ptr<Expression> operand;
	};

	struct BinaryExpr : Expression { 
		std::shared_ptr<Expression> LHS;
		std::string operation;
		std::shared_ptr<Expression> RHS;
	};

	struct NamedIDExpr : Identifier {
		std::string name;
	};

	struct IDAccessExpr : Identifier { 
		std::shared_ptr<Identifier> LHS;
		std::string RHS;
	};

	struct CallExpr : Expression { 
		std::shared_ptr<Expression> object;
		std::shared_vec<Expression> arguments;
	};

	struct ArrayAccessExpr : Expression { 
		std::shared_ptr<Expression> object; 
		std::shared_ptr<Expression> index;
	};

	struct MemberAccessExpr : Expression { 
		std::shared_ptr<Expression> object; 
		std::string name;
	};
}}
