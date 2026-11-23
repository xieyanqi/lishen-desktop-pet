#include "../src/Pose.hpp"
#ifdef NDEBUG
#undef NDEBUG
#endif
#include <cassert>
#include <cmath>
using namespace lishen;
float distance(Point a,Point b){return std::hypot(a.x-b.x,a.y-b.y);}
int main(){
 Animation mapped;
 for(char k='A';k<='Z';++k){
   mapped.letter(k);auto pos=mapped.latest;
   const char* rows[]={"QWERTYUIOP","ASDFGHJKL","ZXCVBNM"};
   assert(rows[pos.row][pos.col]==k);
   for(int i=0;i<12;i++)mapped.tick(.01,0,-1);
   assert(mapped.gazeY>0);
   assert(std::abs((pos.x()<155?mapped.lx:mapped.rx)-pos.x())<1);
 }
 for(int i=0;i<200;i++)mapped.tick(.02,-1,-1);
 assert(mapped.gazeX<-.9 && mapped.gazeY<-.9);
 mapped.hovered=true;
 for(int i=0;i<40;i++)mapped.tick(.02,0,0);
 assert(mapped.eyelid()>.98 && mapped.pupil>1.3);
 mapped.hovered=false;
 for(int i=0;i<40;i++)mapped.tick(.02,2,2);
 assert(mapped.pet<.01 && mapped.pupil<.9);
 Animation a;a.key();assert(a.action==Action::Typing);
 a.tick(.1,1,-1);assert(a.pulseLeft>.8 && a.pulseRight==0);
 a.key();a.tick(.1,1,-1);assert(a.pulseRight>.8);
 for(int i=0;i<20;i++)a.tick(.1,1,-1);
 assert(a.action==Action::Idle && a.gazeX>.9 && a.gazeY<-.9);
 a.preview(Action::Glasses);a.key();assert(a.action==Action::Glasses);
 for(int i=0;i<45;i++)a.tick(.1,0,0);
 assert(a.action==Action::Idle);
 a.enabled=false;a.key();assert(a.action!=Action::Typing);
 // Across all gaze extremes, the finger stays on the moving frame during contact.
 for(float gx:{-1.f,0.f,1.f})for(float gy:{-1.f,0.f,1.f})for(int i=0;i<=400;i++) {
   Animation b;b.action=Action::Glasses;b.time=i/100.0;b.gazeX=gx;b.gazeY=gy;Pose p=pose(b);
   if(b.time>=.96 && b.time<=2.96)assert(distance(p.indexTip,p.frameContact)<.001f);
   if(b.time<.96 || b.time>2.96)assert(std::abs(p.glassesY)<.001f);
   for(int side=0;side<2;side++) {
     Point shoulder{side?207.f:109.f,side?194.f:195.f};Point palm=side?p.rightPalm:p.leftPalm;Point wrist{palm.x,palm.y-5};
     Point bend=elbow(shoulder,wrist,45,52,side!=0);
     assert(std::abs(distance(shoulder,bend)-45)<.001f);
     assert(std::abs(distance(wrist,bend)-52)<.001f);
   }
 }
 // Finger and contacted key share the exact same downward displacement.
 for(float v:{0.f,.25f,.5f,1.f}){Animation b;b.pulseLeft=v;Pose p=pose(b);assert(std::abs((p.leftPalm.y+15)-(274+v*1.6f))<.001f);}
 for(int i=0;i<1000;i++){a.tick(.1,100,-100);assert(std::isfinite(a.gesture()));assert(a.gazeX<=1 && a.gazeY>=-1);}
}
