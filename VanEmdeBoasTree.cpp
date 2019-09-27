#include "VanEmdeBoasTree.h"

VanEmdeBoasTree::VanEmdeBoasTree(int u){
  this->u=u;
  this->maximum=-1;
  this->minimum=-1;

  if(u<=2){
    this->summary=nullptr;
    this->clusters=nullptr;
  }
  else{
    this->summary=new  VanEmdeBoasTree(int(sqrt(u)));
    this->clusters=new  VanEmdeBoasTree*[int(sqrt(u))];
  }
}
bool VanEmdeBoasTree::insert(int num){

  if(maximum==-1){
    maximum=minimum=num;
    return true;
  }


  if(num<minimum)
    std::swap(num,minimum);

  if(u>2){
    int current=num;
    minimum=num;
    insert(num);
  }
  else{
    int auxU=int(sqrt(this->u));
    int l=num%auxU, h=num/auxU;
    if(clusters[h]==NULL){
      clusters[h]=new VanEmdeBoasTree(auxU);
      clusters[h]->insert(l);
      summary->insert(h);
    }
    else
      clusters[h]->insert(l);
  }
  maximum=maximum<num?num:maximum;

  return true;
}

bool VanEmdeBoasTree::find(int num){
  if(minimum==-1) return false;
  if(u<=2){
    if(num==maximum || num==minimum) return true;
    return false;
  }
  else{
    if(num<minimum || num > maximum) return false;
    if(num==minimum || num == maximum) return true;
    int h=num/int(sqrt(u)), l=num%int(sqrt(u));
    if(clusters[h]==nullptr) return false;
    return clusters[h]->find(l);
  }
}

int VanEmdeBoasTree::getMin(){ return minimum; }
int VanEmdeBoasTree::getMax(){ return maximum; }

int VanEmdeBoasTree::successor(int num){
  if(u==2){
    if(num==0 && maximum==1) return 1;
    else return -1;
  }
  else{
    if(minimum==-1) return -1;
    if(num>=maximum) return -1;
    if(num<minimum) return minimum;
    int auxU=sqrt(u);
    int h=num/auxU,l=num%auxU;
    if(clusters[h]==nullptr){
      int next=summary->successor(h);
      int ret=next*auxU+clusters[next]->getMin();
      return ret;
    }
    else{
      int ln,hn=h;
      int maxIn=clusters[h]->getMax();
      if(l<maxIn) ln=clusters[h]->successor(l);
      else{
        hn=summary->successor(h);
        ln=clusters[hn]->getMin();
      }
      int r=hn*auxU+ln;
      return r;

    }
  }
}
