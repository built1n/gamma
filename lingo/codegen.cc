#include <iostream>
#include <string>
using namespace std;
char hex_chars[]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
string toHex(unsigned char n)
{
  string ret;
  ret += hex_chars[(n & 0xF0)>> 4];
  ret += hex_chars[(n & 0xF)];
  return ret;
}
int main()
{
  for(int i=0;i<256;++i)
    {
      cout << "static void exec_instr_";
      cout.setf(ios::hex);
      cout << toHex(i) << "(lingo_ctx* ctx)" << endl;
      cout << "{" << endl;
      cout << "}" << endl;
    }
  cout << "static void (*lingoExecTable[256])(lingo_ctx*)={" << endl;
  for(int i=0;i<256;++i)
    {
      cout << "&exec_instr_";
      cout.setf(ios::hex);
      cout << toHex(i) << ", " << endl;
    }
  cout << "};" << endl;
}
