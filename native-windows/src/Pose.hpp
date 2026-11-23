#pragma once
#include "Animation.hpp"
namespace lishen {
struct Point {float x,y;};
inline Point mix(Point a,Point b,float t){return {a.x+(b.x-a.x)*t,a.y+(b.y-a.y)*t};}
inline float ease(float t){t=std::clamp(t,0.0f,1.0f);return t*t*(3-2*t);}
struct Pose {
 float headX,headY,glassesY,reach,pressLeft,pressRight;
 Point leftPalm,rightPalm,indexTip,frameContact;
};
inline Pose pose(const Animation& a){
 Pose p{};p.headX=a.gazeX*3.2f;p.headY=a.gazeY*1.3f+std::sin(float(a.time)*1.8f)*1.1f;
 p.pressLeft=float(a.pulseLeft);p.pressRight=float(a.pulseRight);
 p.leftPalm={a.lx,a.ly-15+p.pressLeft*1.6f};p.rightPalm={a.rx,a.ry-15+p.pressRight*1.6f};
 if(a.action==Action::Glasses){
   float t=float(std::clamp((a.time-a.actionStart)/4,0.0,1.0));
   p.reach=t<.24f?ease(t/.24f):t<.74f?1:1-ease((t-.74f)/.26f);
   float push=t<.24f?0:t<.4f?ease((t-.24f)/.16f):t<.6f?1:t<.74f?1-ease((t-.6f)/.14f):0;
   p.glassesY=-6*push;
 }
 p.frameContact={219+p.headX,135+p.headY+p.glassesY};
 Point contactPalm={p.frameContact.x-8,p.frameContact.y+21};
 // Pass the fully extended outward pose before changing elbow branch.
 // Both branches meet here, so the elbow cannot flip through the face.
 Point restWrist{p.rightPalm.x,p.rightPalm.y-5};
 Point targetWrist{contactPalm.x,contactPalm.y-5};
 Point extended{304,194};
 Point wrist=p.reach<.5f?mix(restWrist,extended,ease(p.reach*2)):
                                  mix(extended,targetWrist,ease((p.reach-.5f)*2));
 p.rightPalm={wrist.x,wrist.y+5};
 p.indexTip=mix(Point{p.rightPalm.x+5,p.rightPalm.y+15},p.frameContact,p.reach);
 return p;
}
// Two fixed-length segments: bend away from the chest, never stretch the arm.
inline Point elbow(Point shoulder,Point wrist,float upper,float lower,bool right){
 float dx=wrist.x-shoulder.x,dy=wrist.y-shoulder.y;
 float d=std::sqrt(dx*dx+dy*dy);d=std::max(d,.001f);
 float along=std::clamp((upper*upper-lower*lower+d*d)/(2*d),-upper,upper);
 float height=std::sqrt(std::max(0.0f,upper*upper-along*along));
 float sign=(right?1.0f:-1.0f)*(dy<=0?1.0f:-1.0f);
 return {shoulder.x+dx/d*along+sign*(-dy/d)*height,shoulder.y+dy/d*along+sign*(dx/d)*height};
}
}
