#include <iostream>
#include <string>
using namespace std;
int main()
{
  cout << "static inline uint32_t getLong(lingo_ctx* ctx) // get the little endian 32-bit number following the opcode" << endl;
  cout << "{" << endl;
  cout << "  uint32_t pc=ctx->regs.pc;" << endl;
  cout << "  uint32_t ret=ctx->program[pc+4];" << endl;
  cout << "  ret |= ctx->program[pc+3] << 8;" << endl;
  cout << "  ret |= ctx->program[pc+2] << 16;" << endl;
  cout << "  ret |= ctx->program[pc+1] << 24;" << endl;
  cout << "  return ret;" << endl;
  cout <<" }" << endl;
  while(cin)
    {
      string opcode;
      cin >> opcode;
      string instr;
      cin >> instr;
      cout << "static void lingo_exec_" << opcode << "(lingo_ctx* ctx)" << endl;
      cout << "{" << endl;
      if(instr=="LX")
	{
	  cout << "ctx->regs.";
	  string reg;
	  cin >> reg;
	  cout << reg << "=getLong(ctx);" << endl;
	}
      else if(instr=="NOP")
	{
	  cout << "asm volatile(\"nop\");" <<endl;
	}
      else if(instr=="LXP")
	{
	  string reg;
	  cin >> reg;
	  cout << "ctx->regs." << reg << "=ctx->program[getLong(ctx)];" << endl;
	}
      else if(instr=="LR") // this takes two arguments: SOURCE, DEST
	{
	  string source, dest;
	  cin >> source >> dest;
	  cout << "ctx->regs." << dest << "=ctx->regs." << source << ";" << endl;
	}
      else if(instr=="LPR") // load register pointer
	{
	  string location;
	  string dest;
	  cin >> location >> dest;
	  cout << "ctx->regs." << dest << "=ctx->program[ctx->regs." << location << "];" << endl;
	}
      else if(instr=="LMX")
	{
	  string source;
	  cin >> source;
	  cout << "ctx->program[getLong(ctx)]=ctx->regs." << source << ";" << endl;
	}
      else if(instr=="LMR")
	{
	  string source, dest;
	  cin >> source >> dest;
	  cout << "ctx->program[ctx->regs." << dest << "]=ctx->regs." << source << ";" << endl;
	}
      else if(instr=="LSR")
	{
	  string reg;
	  cin >> reg;
	  cout << "ctx->regs.RA=ctx->regs." << reg << ";" << endl;
	}
      cout << "}" << endl;
    }
}
