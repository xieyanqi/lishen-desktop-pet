#pragma once
#include <objidl.h>
#include <gdiplus.h>
#include <vector>
#include "Character.hpp"
namespace lishen {
class GdiCanvas {
 Gdiplus::Graphics& g;
 static Gdiplus::Color color(const char* s) { unsigned v=0; if(s[0]=='#')v=static_cast<unsigned>(std::strtoul(s+1,nullptr,16)); return Gdiplus::Color(255,(v>>16)&255,(v>>8)&255,v&255); }
public:
 explicit GdiCanvas(Gdiplus::Graphics& graphics):g(graphics){}
 void ellipse(float x,float y,float w,float h,const char* fill,const char* stroke,float width,const char* =nullptr) {
   if(fill[0]!='n'){Gdiplus::SolidBrush b(color(fill));g.FillEllipse(&b,x,y,w,h);}
   if(stroke[0]!='n'){Gdiplus::Pen p(color(stroke),width);g.DrawEllipse(&p,x,y,w,h);}
 }
 void line(float x,float y,float xx,float yy,const char* stroke,float width) {
   Gdiplus::Pen p(color(stroke),width);p.SetStartCap(Gdiplus::LineCapRound);p.SetEndCap(Gdiplus::LineCapRound);g.DrawLine(&p,x,y,xx,yy);
 }
 void path(Gdiplus::GraphicsPath& path,const char* fill,const char* stroke,float width) {
   if(fill[0]!='n'){Gdiplus::SolidBrush b(color(fill));g.FillPath(&b,&path);}
   if(stroke[0]!='n'){Gdiplus::Pen p(color(stroke),width);p.SetLineJoin(Gdiplus::LineJoinRound);g.DrawPath(&p,&path);}
 }
 void poly(std::initializer_list<Point> list,const char* fill,const char* stroke,float width) {
   std::vector<Gdiplus::PointF> pts;for(auto p:list)pts.emplace_back(p.x,p.y);
   Gdiplus::GraphicsPath shape;shape.AddPolygon(pts.data(),static_cast<INT>(pts.size()));path(shape,fill,stroke,width);
 }
 void curve(std::initializer_list<Point> list,const char* fill,const char* stroke,float width) {
   std::vector<Gdiplus::PointF> pts;for(auto p:list)pts.emplace_back(p.x,p.y);
   Gdiplus::GraphicsPath shape;
   if(fill[0]!='n')shape.AddClosedCurve(pts.data(),static_cast<INT>(pts.size()),0.35f);
   else shape.AddCurve(pts.data(),static_cast<INT>(pts.size()),0.35f);
   path(shape,fill,stroke,width);
 }
 void roundRect(float x,float y,float w,float h,float radius,const char* fill,const char* stroke,float width) {
   float d=radius*2;Gdiplus::GraphicsPath shape;
   shape.AddArc(x,y,d,d,180,90);shape.AddArc(x+w-d,y,d,d,270,90);
   shape.AddArc(x+w-d,y+h-d,d,d,0,90);shape.AddArc(x,y+h-d,d,d,90,90);shape.CloseFigure();path(shape,fill,stroke,width);
 }
};
}
