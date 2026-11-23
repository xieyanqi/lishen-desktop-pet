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
 void key() { if(!enabled)return; lastKey=time; ++keyCount;
   if(action!=Action::Glasses) {if(keyCount%2)leftHit=time;else rightHit=time;}
   // Finish the small idle gesture before returning to typing.
   if(action==Action::Idle || action==Action::Typing) action=Action::Typing;
 }
 void preview(Action a) {action=a; actionStart=time; nextIdle=time+14;}
 void tick(double dt,float x,float y) {
   dt=std::clamp(dt,0.0,0.1); time+=dt;
   float smooth=float(1-std::exp(-dt*9));
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
   return phase<0.17?float(std::sin(phase/0.17*3.141592653589793)):0;
 }
};
}
