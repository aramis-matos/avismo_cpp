#include "driver.hh"
#include "parser.hh"
#include <fstream>

void add_keywords (std::map<std::string,std::string>& list) {
    std::ifstream keywords;
    std::string val;

    keywords.open("keywords.txt");
    while (getline(keywords,val)) {
        list[val] = "";
    }
    keywords.close();
}


driver::driver ()
{
  add_keywords(this->variables);
}

int
driver::parse (const std::string &f)
{
  file = f;
  location.initialize (&file);
  scan_begin ();
  yy::parser parser (*this);
  parser.set_debug_level (trace_parsing);
  int res = parser.parse ();
  scan_end ();
  return res;
}
