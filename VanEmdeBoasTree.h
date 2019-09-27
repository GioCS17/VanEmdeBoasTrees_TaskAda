#include<cmath>
#include<algorithm>

class VanEmdeBoasTree{

  private :
    int u;
    VanEmdeBoasTree *summary;
    VanEmdeBoasTree **clusters;
    int maximum;
    int minimum;

  public:
    VanEmdeBoasTree(int);
    VanEmdeBoasTree();
    bool insert(int);
    bool find(int);
    int successor(int);
    int getMin();
    int getMax();

};
