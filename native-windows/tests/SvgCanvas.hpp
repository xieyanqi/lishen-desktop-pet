#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include "../src/Character.hpp"
using namespace lishen;
struct SvgCanvas {
 std::ostringstream out;
 void legend(float x,float y,char key){out<<"<text x='"<<x<<"' y='"<<y<<"' text-anchor='middle' font-family='sans-serif' font-size='4.8' fill='#526e81'>"<<key<<"</text>";}
 void style(const char*f,const char*s,float w){out<<" fill='"<<f<<"' stroke='"<<s<<"' stroke-width='"<<w<<"' stroke-linecap='round' stroke-linejoin='round'";}
 void ellipse(float x,float y,float w,float h,const char*f,const char*s,float z,const char* tag=nullptr){out<<"<ellipse cx='"<<x+w/2<<"' cy='"<<y+h/2<<"' rx='"<<w/2<<"' ry='"<<h/2<<"'";if(tag)out<<" class='pupil'";style(f,s,z);out<<"/>";}
 void line(float x,float y,float xx,float yy,const char*s,float w){out<<"<path d='M"<<x<<","<<y<<" L"<<xx<<","<<yy<<"'";style("none",s,w);out<<"/>";}
 void poly(std::initializer_list<Point> ps,const char*f,const char*s,float w){out<<"<polygon points='";for(auto p:ps)out<<p.x<<","<<p.y<<" ";out<<"'";style(f,s,w);out<<"/>";}
 void roundRect(float x,float y,float w,float h,float r,const char*f,const char*s,float z){out<<"<rect x='"<<x<<"' y='"<<y<<"' width='"<<w<<"' height='"<<h<<"' rx='"<<r<<"'";style(f,s,z);out<<"/>";}
 void curve(std::initializer_list<Point> ps,const char*f,const char*s,float w){std::vector<Point> p(ps);bool closed=f[0]!='n';out<<"<path d='M"<<p[0].x<<","<<p[0].y;int n=int(p.size());
  for(int i=0;i<(closed?n:n-1);i++){auto at=[&](int k){return p[closed?(k+n)%n:std::clamp(k,0,n-1)];};auto p0=at(i-1),p1=at(i),p2=at(i+1),p3=at(i+2);float t=.35f/3;
   out<<" C"<<p1.x+(p2.x-p0.x)*t<<","<<p1.y+(p2.y-p0.y)*t<<" "<<p2.x-(p3.x-p1.x)*t<<","<<p2.y-(p3.y-p1.y)*t<<" "<<p2.x<<","<<p2.y;
  }if(closed)out<<" Z";out<<"'";style(f,s,w);out<<"/>";
 }
};
