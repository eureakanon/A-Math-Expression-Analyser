#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <iostream>
#include <iomanip>      // 修正：原代码为 <iomanip> 缺少 'i'
#include <cstring>
#include <fstream>
#include <sstream>
#include <dirent.h>
using namespace std;
enum TokenType{
    TOKEN_NUM,
    TOKEN_IDENTIFIER,/*标识符*/
    TOKEN_FUNCTION,
    TOKEN_PLUS,/*+*/
    TOKEN_MINUS,/*-*/
    TOKEN_STAR,/* * */
    TOKEN_SLASH,/* / */
    TOKEN_CARET,/* ^ */
    TOKEN_LEFTPAREN,/*(*/
    TOKEN_RIGHTPAREN,/*)*/
    TOKEN_CHANGELINE,/*\n */
    TOKEN_NOTE,/*#*/
    TOKEN_EOF,/*END OF FILE*/
    TOKEN_ERROR/*错误*/
};/*词法分析能返回的结果*/
enum FunctionType/*如果遇到了未定义的TOKEN,我们认为是变量，初始化为0.0*/
{
    SIGN_FUNCTION,
    ABSOLUTE_VALUE,
    SIN,
    COS,
    TAN,
    EXP,
    LOG,
    ARCSIN,
    ARCCOS,
    ARCTAN
};
map<string,double>Variable_Map;/*注册过的标识符号+初始值*/
struct Token
{
    TokenType token_type;
    string origin_name;
    double token_value;
};
int token;/*current token*/
char* src;/*next char*/
int line;
Token tokenizer()
{
    Token result;
    result.token_type=TOKEN_ERROR;
    result.origin_name="Unknown_error";
    result.token_value=(double)0;
    while(*src==' '||*src=='\t')
    {
        src++;
    }/*跳过制表符*/
    if(*src=='\0')
    {
        result.token_type=TOKEN_EOF;
        result.origin_name="End_of_file";
        result.token_value=(double)'\0';
        return result;
    }
    token=*src++;/*token and next_char*/
    if(token=='\n')
    {
        line++;
        result.token_type=TOKEN_CHANGELINE;
        result.origin_name="User_changed_line";
        result.token_value=(double)'\n';
        return result;
    }
    else if(token=='+')
    {
        result.token_type=TOKEN_PLUS;
        result.origin_name="Plus";
        result.token_value=(double)'+';
        return result;
    }
    else if(token=='-')
    {
        result.token_type=TOKEN_MINUS;
        result.origin_name="Minus";
        result.token_value=(double)'-';
        return result;
    }
    else if(token=='*')
    {
        result.token_type=TOKEN_STAR;
        result.origin_name="Multiply";
        result.token_value=(double)'*';
        return result;
    }
    else if(token=='/')
    {
        result.token_type=TOKEN_SLASH;
        result.origin_name="Division";
        result.token_value=(double)'/';
        return result;
    }
    else if(token=='^')
    {
        result.token_type=TOKEN_CARET;
        result.origin_name="Power";
        result.token_value=(double)'^';
        return result;
    }
    else if(token=='(')
    {
        result.token_type=TOKEN_LEFTPAREN;
        result.origin_name="Left_paren";
        result.token_value=(double)'(';
        return result;
    }
    else if(token==')')
    {
        result.token_type=TOKEN_RIGHTPAREN;
        result.origin_name="Right_paren";
        result.token_value=(double)')';
        return result;
    }
    else if(token=='#')/*对注释符号进行跳过*/
    {
        result.token_type=TOKEN_NOTE;
        result.origin_name="NOTE";
        result.token_value=(double)'#';
        while(*src!='\n'&&*src!='\0')
        {
            src++;
        }
        return result;
    }
    else if(token>='0'&&token<='9')/*我们只解析十进制有限小树比如1234.5678*/
    {
        int Integer_sum=token-'0';
        while(*src>='0'&&*src<='9')
        {
            Integer_sum=Integer_sum*10+*src-'0';
            src++;
        }
        double Real_sum=0;
        int digit_count=0;
        if(*src=='.')
        {
            src++;
        }
        while(*src>='0'&&*src<='9')
        {
            Real_sum=Real_sum*10+*src-'0';
            digit_count++;
            src++;
        }
        Real_sum=Real_sum/(pow(10.0,digit_count));
        result.token_type=TOKEN_NUM;
        result.origin_name="Number";
        result.token_value=(double)(Integer_sum)+(double)(Real_sum);
        return result;
    }
    else if(token>='a'&&token<='z'||token>='A'&&token<='Z')
    {
        string msg;
        msg.push_back((char)(token));
        while(*src>='a'&&*src<='z'||*src>='A'&&*src<='Z'||*src>='0'&&*src<='9')
        {
            msg.push_back(*src);
            src++;
        }
        if(msg=="sgn"||msg=="SGN")
        {
            result.token_type=TOKEN_FUNCTION;
            result.origin_name="sign_function_called";
            result.token_value=(double)(SIGN_FUNCTION);
        }
        else if(msg=="abs"||msg=="ABS")
        {
            result.token_type=TOKEN_FUNCTION;
            result.origin_name="absolute_value_function_called";
            result.token_value=(double)(ABSOLUTE_VALUE);
        }
        else if(msg=="sin"||msg=="SIN")
        {
            result.token_type=TOKEN_FUNCTION;
            result.origin_name="sin_function_called";
            result.token_value=(double)(SIN);
        }
        else if(msg=="cos"||msg=="COS")
        {
            result.token_type=TOKEN_FUNCTION;
            result.origin_name="cos_function_called";
            result.token_value=(double)(COS);
        }
        else if(msg=="tan"||msg=="TAN")
        {
            result.token_type=TOKEN_FUNCTION;
            result.origin_name="tan_function_called";
            result.token_value=(double)(TAN);
        }
        else if(msg=="exp"||msg=="EXP")
        {
            result.token_type=TOKEN_FUNCTION;
            result.origin_name="exp_function_called";
            result.token_value=(double)(EXP);
        }
        else if(msg=="log"||msg=="LOG")
        {
            result.token_type=TOKEN_FUNCTION;
            result.origin_name="log_function_called";
            result.token_value=(double)(LOG);
        }
        else if(msg=="arcsin"||msg=="ARCSIN")
        {
            result.token_type=TOKEN_FUNCTION;
            result.origin_name="arcsin_function_called";
            result.token_value=(double)(ARCSIN);
        }
        else if(msg=="arccos"||msg=="ARCCOS")
        {
            result.token_type=TOKEN_FUNCTION;
            result.origin_name="arccos_function_called";
            result.token_value=(double)(ARCCOS);
        }
        else if(msg=="arctan"||msg=="ARCTAN")
        {
            result.token_type=TOKEN_FUNCTION;
            result.origin_name="arctan_function_called";
            result.token_value=(double)(ARCTAN);
        }
        else{
            auto it=Variable_Map.find(msg);
            if(it!=Variable_Map.end())
            {
                result.token_type=TOKEN_IDENTIFIER;
                result.origin_name=msg;
                result.token_value=it->second;
            }
            else
            {
                result.token_type=TOKEN_IDENTIFIER;
                result.origin_name=msg;
                result.token_value=(double)0;
                Variable_Map.insert({msg,(double)0});
            }
        }
        return result;
    }
    else
    {
        return result;
    }
}
/*next token*/
enum NodeType
{
    NODE_NUM,
    NODE_VAR,
    NODE_BINOP,
    NODE_UNOP,
    NODE_FUNCALL
};/*代表了节点的类型*/
enum BinOp
{
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_POW
};/*所有的二元运算*/
enum UnOp
{
    OP_NEG
};/*只有负号一种*/
struct ASTNode{/*激动人心的部分:抽象语法树*/
    NodeType type;
    double value;
    string var_name;
    BinOp binop;
    UnOp unop;
    FunctionType func;
    ASTNode* left;
    ASTNode* right;
};
/*接下来是内存分配机制*/
ASTNode* make_num(double val)
{   
    ASTNode* node=new ASTNode;
    node->type=NODE_NUM;
    node->value=val;
    node->left=NULL;
    node->right=NULL;
    return node;
}
ASTNode* make_var(const string& name)
{
    ASTNode* node=new ASTNode;
    node->type=NODE_VAR;
    node->var_name=name;
    node->left=NULL;
    node->right=NULL;
    return node;
}
ASTNode* make_binop(BinOp op,ASTNode* l,ASTNode* r)/*这里内存分配是不一样的，因为二元运算符一定需要两个参数*/
{
    ASTNode* node=new ASTNode;
    node->type=NODE_BINOP;
    node->binop=op;
    node->left=l;
    node->right=r;
    return node;
}
ASTNode* make_unop(UnOp op,ASTNode* operand)/*一个参数就默认为left*/
{
    ASTNode* node=new ASTNode;
    node->type=NODE_UNOP;
    node->unop=op;
    node->left=operand;
    node->right=NULL;
    return node;
}
ASTNode* make_funcall(FunctionType f,ASTNode* arg)
{
    ASTNode* node=new ASTNode;
    node->type=NODE_FUNCALL;
    node->func=f;
    node->left=arg;
    node->right=NULL;
    return node;
}
Token current_token;
void advance()/*下一个不是换行和注释的token*/
{
    current_token=tokenizer();
    while(current_token.token_type==TOKEN_NOTE||current_token.token_type==TOKEN_CHANGELINE)
    {
        current_token=tokenizer();
    }
}
/*递归下降，本人还没搞明白*/
ASTNode* expr();/*前向声明*/
ASTNode* primary()/*原子表达式的解析:1.变量,2.取反,3.函数调用*/
{
    ASTNode* node=NULL;
    if(current_token.token_type==TOKEN_NUM)
    {
        node=make_num(current_token.token_value);
        advance();
    }
    else if(current_token.token_type==TOKEN_IDENTIFIER)
    {
        node=make_var(current_token.origin_name);
        advance();
    }
    else if(current_token.token_type==TOKEN_FUNCTION)
    {
        FunctionType type=(FunctionType)(int)(current_token.token_value);
        advance();/*吃掉函数名*/
        if(current_token.token_type!=TOKEN_LEFTPAREN)
        {
            cerr<<"Error:expected '(' After Function called"<<endl;
            exit(1);
        }
        advance();/*吃掉左括号*/
        node=expr();
        if(current_token.token_type!=TOKEN_RIGHTPAREN)
        {
            cerr<<"Error:expected ')' After Function called"<<endl;
            exit(1);

        }
        advance();/*吃掉有括号*/
        node=make_funcall(type,node);
    }
    else if(current_token.token_type==TOKEN_LEFTPAREN)/*解析(expr的式子)*/
    {
        advance();/*吃掉左括号*/
        node=expr();
        if(current_token.token_type!=TOKEN_RIGHTPAREN)
        {
            cerr<<"Error:unpaired '(' and ')' "<<endl;
            exit(1);
        }
        advance();
    }
    else
    {
        cerr<<"Error:unexpected token"<<endl;
        exit(1);
    }
    return node;
}
ASTNode* factor()
{
    // 一元负号：作用于后面整个 factor（包括幂运算）
    if (current_token.token_type == TOKEN_MINUS) {
        advance();                     // 吃掉 '-'
        ASTNode* operand = factor();   // 递归获取后面的整个因子（如 x^2）
        return make_unop(OP_NEG, operand);
    }

    // 正因子：原子 + 可选幂运算
    ASTNode* node = primary();
    while (current_token.token_type == TOKEN_CARET) {
        advance();
        ASTNode* rhs = factor();       // 右结合
        node = make_binop(OP_POW, node, rhs);
    }
    return node;
}
ASTNode* term()
{
    ASTNode* node=factor();
    while(current_token.token_type==TOKEN_STAR||current_token.token_type==TOKEN_SLASH)
    {
        TokenType op=current_token.token_type;
        advance();
        ASTNode* rhs=factor();
        if(op==TOKEN_STAR)
        {
            node=make_binop(OP_MUL,node,rhs);
        }
        else
        {
            node=make_binop(OP_DIV,node,rhs);
        }
    }
    return node;
}
ASTNode* expr()
{
    ASTNode* node=term();
    while(current_token.token_type==TOKEN_PLUS||current_token.token_type==TOKEN_MINUS)
    {
        TokenType op=current_token.token_type;
        advance();
        ASTNode* rhs=term();
        if(op==TOKEN_PLUS)
        {
            node=make_binop(OP_ADD,node,rhs);
        }
        else
        {
            node=make_binop(OP_SUB,node,rhs);
        }
    }
    return node;
}
double evaluate(ASTNode* node)
{
    if(node==NULL)
    {
        return 0.0;
    }
    if(node->type==NODE_NUM)
    {
        return node->value;
    }
    else if(node->type==NODE_VAR)
    {
        auto it=Variable_Map.find(node->var_name);
        if(it!=Variable_Map.end())
        {
            return it->second;
        }
        else
        {
            cerr<<"Unknown Variable Name:"<<node->var_name<<endl;
            return 0.0;
        }
    }
    else if(node->type==NODE_BINOP)
    {
        double l=evaluate(node->left);
        double r=evaluate(node->right);
        if(node->binop==OP_ADD)
        {
            return l+r;
        }
        else if(node->binop==OP_SUB)
        {
            return l-r;
        }
        else if(node->binop==OP_MUL)
        {
            return l*r;
        }
        else if(node->binop==OP_DIV)
        {
            if(r==0.0)
            {
                cerr<<"Math Error:Division By 0.0"<<endl;
                return 0.0;
            }
            return l/r;
        }
        else if(node->binop==OP_POW)
        {
            return pow(l,r);
        }
        else
        {
            cerr<<"Unknown Operand return default value 0.0"<<endl;
            return 0.0;
        }
    }
    else if(node->type==NODE_UNOP)
    {
        double val=evaluate(node->left);
        if(node->unop==OP_NEG)
        {
            return -val;
        }
        else
        {
            cerr<<"Unknown One Unit Operand return default value 0.0"<<endl;
            return 0.0;
        }
    }
    else if(node->type==NODE_FUNCALL)
    {
        double arg=evaluate(node->left);
        if(node->func==SIGN_FUNCTION)
        {
            return (arg > 0.0) ? 1.0 : (arg < 0.0 ? -1.0 : 0.0);
        }
        else if(node->func==ABSOLUTE_VALUE)
        {
            return fabs(arg);
        }
        else if(node->func==SIN)
        {
            return sin(arg);
        }
        else if(node->func==COS)
        {
            return cos(arg);
        }
        else if(node->func==TAN)
        {
            return tan(arg);
        }
        else if(node->func==EXP)
        {
            return exp(arg);
        }
        else if(node->func==LOG)
        {
            if (arg <= 0.0) {
                    cerr << "Math Error: log of non-positive number" << endl;
                    return 0.0;
            }
            return log(arg);
        }
        else if(node->func==ARCSIN)
        {
            return asin(arg);
        }
        else if(node->func==ARCCOS)
        {
            return acos(arg);
        }
        else if(node->func==ARCTAN)
        {
            return atan(arg);
        }
        else
        {
            cerr<<"Error:Unknown function return identical function"<<endl;
            return arg;
        }

    }
    return 0.0;
}
void free_ast(ASTNode* node)
{
    if(node==NULL)
    {
        return;
    }
    free_ast(node->left);
    free_ast(node->right);
    delete node;
}
void parse_variables_from_string(const string& init_str) {
    if (init_str.empty() || init_str[0] != '$') return;

    size_t end = init_str.find('$', 1);
    if (end == string::npos) return;

    string content = init_str.substr(1, end - 1);  // 去掉首尾的 $
    stringstream ss(content);
    string item;
    while (getline(ss, item, ',')) {
        size_t eq_pos = item.find('=');
        if (eq_pos != string::npos) {
            string var = item.substr(0, eq_pos);
            string val_str = item.substr(eq_pos + 1);
            double val = atof(val_str.c_str());
            Variable_Map[var] = val;
        }
    }
}

// 列出 ./formula/ 目录下的所有文件名
void list_formulas() {
    DIR* dir = opendir("./formula");
    if (!dir) {
        cerr << "Error: cannot open directory './formula'" << endl;
        return;
    }
    struct dirent* entry;
    while ((entry = readdir(dir)) != NULL) {
        // 跳过 . 和 ..
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        cout << entry->d_name << endl;
    }
    closedir(dir);
}

// 读取文件全部内容到 string
string read_file(const string& path) {
    ifstream file(path.c_str());
    if (!file) {
        cerr << "Error: cannot open file '" << path << "'" << endl;
        return "";
    }
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}
int main() {
    // 预设一些全局变量（也可从文件加载）
    Variable_Map["x"] = 2.0;
    Variable_Map["y"] = 3.0;
    Variable_Map["pi"] = 3.141592653589793;

    cout << "Commands:" << endl;
    cout << "  ls               - list files in ./formula/" << endl;
    cout << "  run <filename>   - parse and evaluate formula from ./formula/filename" << endl;
    cout << "  debug <filename> - show all tokens from ./formula/filename" << endl;
    cout << "  exit             - quit" << endl;

    string command;
    while (true) {
        cout << ">> ";
        if (!getline(cin, command)) break;   // EOF

        if (command.empty()) continue;

        // 分离命令和参数
        stringstream ss(command);
        string cmd;
        ss >> cmd;

        if (cmd == "exit") {
            break;
        }
        else if (cmd == "ls") {
            list_formulas();
        }
        else if (cmd == "run" || cmd == "debug") {
            string filename;
            ss >> filename;
            if (filename.empty()) {
                cerr << "Error: missing filename" << endl;
                continue;
            }

            // 构造路径 ./formula/filename
            string path = "./formula/" + filename;
            string content = read_file(path);
            if (content.empty()) continue;

            // 查找变量初始化部分 $...$
            size_t first_dollar = content.find('$');
            size_t second_dollar = string::npos;
            if (first_dollar != string::npos) {
                second_dollar = content.find('$', first_dollar + 1);
            }

            string init_part, expr_part;
            if (first_dollar != string::npos && second_dollar != string::npos) {
                init_part = content.substr(first_dollar, second_dollar - first_dollar + 1);
                expr_part = content.substr(second_dollar + 1);   // 剩余部分
                // 解析变量定义
                parse_variables_from_string(init_part);
            } else {
                // 没有变量初始化，整个内容就是表达式
                expr_part = content;
            }

            if (cmd == "run") {
                // 将表达式字符串复制到可修改的缓冲区
                char* buffer = new char[expr_part.size() + 1];
                strcpy(buffer, expr_part.c_str());
                src = buffer;
                line = 1;

                advance();                          // 读取第一个有效 token
                ASTNode* root = expr();
                if (current_token.token_type != TOKEN_EOF) {
                    cerr << "Warning: unexpected token after expression" << endl;
                }

                double result = evaluate(root);
                cout << result << endl;

                free_ast(root);
                delete[] buffer;
            }
            else if (cmd == "debug") {
                // debug 模式：只做词法分析，不解析语法
                char* buffer = new char[expr_part.size() + 1];
                strcpy(buffer, expr_part.c_str());
                src = buffer;
                line = 1;

                Token tok;
                cout << "Tokens:" << endl;
                while (true) {
                    tok = tokenizer();
                    if (tok.token_type == TOKEN_EOF) break;

                    // 跳过换行和注释
                    if (tok.token_type == TOKEN_CHANGELINE || tok.token_type == TOKEN_NOTE)
                        continue;

                    cout << "  type=" << tok.token_type
                         << "  name=\"" << tok.origin_name << "\""
                         << "  value=" << tok.token_value << endl;
                }
                delete[] buffer;
            }
        }
        else {
            cerr << "Unknown command: " << cmd << endl;
            cerr << "Available: ls, run <file>, debug <file>, exit" << endl;
        }
    }

    return 0;
}
