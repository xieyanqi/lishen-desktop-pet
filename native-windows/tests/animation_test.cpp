#include "../src/Animation.hpp"
#include <cassert>
#include <cmath>
using namespace lishen;
int main(){
 Animation a;
 a.key();assert(a.action==Action::Typing && a.pulseLeft==1);
 a.key();assert(a.pulseRight==1);
 for(int i=0;i<20;i++)a.tick(0.1,1,-1);
 assert(a.action==Action::Idle && a.gazeX>0.9 && a.gazeY<-0.9);
 a.preview(Action::Tea);a.key();assert(a.action==Action::Tea);
 for(int i=0;i<45;i++)a.tick(0.1,0,0);
 assert(a.action==Action::Idle);
 a.enabled=false;a.key();assert(a.action!=Action::Typing);
 for(int i=0;i<1000;i++) {a.tick(0.1,100,-100);assert(std::isfinite(a.gesture()));assert(a.gazeX<=1 && a.gazeY>=-1);}
}
