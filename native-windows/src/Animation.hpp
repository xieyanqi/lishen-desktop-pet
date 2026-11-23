#pragma once
#include <algorithm>
#include <cmath>
#include <cstdint>
#include <random>
namespace lishen {
enum class Action { Idle, Typing, Glasses };
struct Animation {
 double time=0, lastKey=-100, nextIdle=10, actionStart=0, pulseLeft=0, pulseRight=0;
 double leftHit=-100,rightHit=-100;
 float gazeX=0,gazeY=0; bool enabled=true, rest=false; unsigned keyCount=0;
 Action action=Action::Idle; std::mt19937 random{173};
 struct Key {int row,col; float x()const{return 90+col*13.5f+row*3;} float y()const{return 267+row*7.f;}};
 Key left{1,3},right{1,8},latest{1,3};
 float lx=130.5f,ly=274,rx=198,ry=274,pupil=1,pet=0;
 bool hovered=false;
 void letter(unsigned vk){
   const char* rows[]={"QWERTYUIOP","ASDFGHJKL","ZXCVBNM"};
   if(!enabled)return;
   for(int r=0;r<3;r++)for(int col=0;rows[r][col];col++){
     if(unsigned(rows[r][col])!=vk)continue;
     latest={r,col};lastKey=time;
     if(action!=Action::Glasses){
       if(latest.x()<155){left=latest;leftHit=time;}else{right=latest;rightHit=time;}
       action=Action::Typing;
     }
     return;
   }
 }
 void key() { if(!enabled)return; lastKey=time; ++keyCount;
   if(action!=Action::Glasses) {if(keyCount%2)leftHit=time;else rightHit=time;}
   // Finish the small idle gesture before returning to typing.
   if(action==Action::Idle || action==Action::Typing) action=Action::Typing;
 }
 void preview(Action a) {action=a; actionStart=time; nextIdle=time+14;}
 void tick(double dt,float x,float y) {
   dt=std::clamp(dt,0.0,0.1); time+=dt;
   float smooth=float(1-std::exp(-dt*9));
   float radius=std::hypot(x,y);
   pupil+=(1.38f-.53f*std::clamp(radius,0.f,1.f)-pupil)*smooth;
   pet+=((hovered && action==Action::Idle?1.f:0.f)-pet)*smooth;
   if(action==Action::Typing && time-lastKey<1.4){
     x=(latest.x()-159)/78; y=(latest.y()-256)/28;
   }
   float snap=float(1-std::exp(-dt*48));
   lx+=(left.x()-lx)*snap;ly+=(left.y()-ly)*snap;
   rx+=(right.x()-rx)*snap;ry+=(right.y()-ry)*snap;
   gazeX+=(std::clamp(x,-1.0f,1.0f)-gazeX)*smooth;
   gazeY+=(std::clamp(y,-1.0f,1.0f)-gazeY)*smooth;
   auto tap=[&](double hit){
     double t=(time-hit)/.24;
     return t>=0 && t<1?std::pow(std::sin(t*3.141592653589793),2):0.0;
   };
   pulseLeft=action==Action::Glasses?0:tap(leftHit);
   pulseRight=action==Action::Glasses?0:tap(rightHit);
   if(action!=Action::Idle && action!=Action::Typing && time-actionStart>=4) {
      action=(enabled && time-lastKey<1.4)?Action::Typing:Action::Idle; nextIdle=time+10+(random()%9);
   }
   if(action==Action::Typing && (!enabled || time-lastKey>1.4)) {action=Action::Idle;nextIdle=time+8;}
   if(action==Action::Idle && time>=nextIdle) {
      preview(Action::Glasses);
   }
 }
 float gesture() const {return float(std::sin(std::clamp((time-actionStart)/4.0,0.0,1.0)*3.141592653589793));}
 float eyelid() const {
   double phase=std::fmod(time,4.7);
   return std::max(pet,phase<0.17?float(std::sin(phase/0.17*3.141592653589793)):0.f);
 }
};
}
