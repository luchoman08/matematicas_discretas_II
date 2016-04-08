#include <map>
#include <string>
#include <iostream>

int main(){
  std::map<std::string,unsigned> map_mes_idx;
  map_mes_idx["enero"] = 1;
  map_mes_idx["febrero"] = 2;
  //...
  std::map<std::string,unsigned>::const_iterator
    mit (map_mes_idx.begin()),
    mend(map_mes_idx.end());
  for(;mit!=mend;++mit) std::cout << mit->first << '\t' << mit->second << std::endl;
  return 0;
}
