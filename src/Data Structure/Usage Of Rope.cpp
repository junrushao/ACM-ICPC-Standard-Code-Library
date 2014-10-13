#include <ext/rope>
using __gnu_cxx::crope; using __gnu_cxx::rope;
a = b.substr(from, len);        // `$[from, from + len)$`
a = b.substr(from);             // `$[from, from]$`
b.c_str();                      // `might lead to memory leaks`
b.delete_c_str();               // `delete the c\_{}str that created before`
a.insert(p, str);               // `insert str before position $p$`
a.erase(i, n);                  // `erase $[i, i + n)$`