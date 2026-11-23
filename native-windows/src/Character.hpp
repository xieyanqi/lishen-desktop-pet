#pragma once
#include "Animation.hpp"
#include <initializer_list>
namespace lishen {
struct Point {float x,y;};
// Portable vector scene, rendered by GDI+ in Windows and SVG in the preview.
// Drawing and animation code is original. No KuroCat artwork is used.
template<class C> void character(C& c,const Animation& a) {
 using P=Point;
 const char* outline="#353647"; const char* skin="#f7dfd1";
 const char* coat=a.rest?"#343442":"#f7fafc";
 float breath=std::sin(float(a.time)*1.8f)*1.1f;
 float hx=a.gazeX*3.2f,hy=a.gazeY*1.3f+breath;
 float gesture=a.gesture(); bool tea=a.action==Action::Tea,sweet=a.action==Action::Sweet,glasses=a.action==Action::Glasses;
 c.ellipse(74,291,174,15,"#d9e5ee","none",0);
 // Seated legs and shoes.
 c.ellipse(89,233,65,61,"#40414e",outline,2);
 c.ellipse(157,234,65,60,"#40414e",outline,2);
 c.ellipse(82,268,49,28,"#303440",outline,2);
 c.ellipse(185,268,49,28,"#303440",outline,2);
 c.line(93,276,115,280,"#697080",2); c.line(196,279,221,274,"#697080",2);
 // Coat with lapels, blue shirt, tie and badge.
 c.curve({{115,173},{90,188},{91,242},{79,273},{103,286},{131,265},{158,261},{185,265},{211,286},{236,273},{222,239},{227,188},{201,173}},coat,outline,2);
 c.poly({{140,177},{176,177},{181,244},{136,244}},"#accbdc",outline,1.5f);
 c.poly({{152,181},{165,181},{170,195},{160,231},{150,195}},"#566c89",outline,1);
 c.poly({{134,178},{115,186},{133,210},{140,200},{135,239},{151,215}},coat,"#aab6c9",1.2f);
 c.poly({{181,178},{201,186},{184,210},{178,200},{184,239},{167,215}},coat,"#aab6c9",1.2f);
 c.line(192,210,207,210,"#8699af",1.5f); c.line(199,204,199,216,"#8699af",1.5f);
 // Neck and back hair.
 c.ellipse(143,162,31,26,skin,outline,1.5f);
 c.ellipse(66+hx,49+hy,186,140,"#292935",outline,2);
 // Ears and face.
 c.ellipse(69+hx,119+hy,22,31,skin,outline,1.4f); c.ellipse(230+hx,119+hy,22,31,skin,outline,1.4f);
 c.curve({{82+hx,99+hy},{78+hx,126+hy},{87+hx,158+hy},{112+hx,174+hy},{139+hx,190+hy},{178+hx,190+hy},{207+hx,175+hy},{233+hx,159+hy},{242+hx,129+hy},{232+hx,98+hy}},skin,outline,1.7f);
 // Eye whites and moving hazel irises.
 float eyeH=12*(1-a.eyelid());
 for(int side=0;side<2;side++) {
   float x=107+side*69+hx, y=133+hy;
   if(eyeH<2) c.line(x,y+4,x+32,y+4,outline,2.5f);
   else {
     c.ellipse(x,y,32,eyeH,"#fffaf5","none",0);
     c.ellipse(x+11+a.gazeX*4,y+a.gazeY*1.8f,12,eyeH,"#858367","none",0,"pupil");
     c.ellipse(x+15+a.gazeX*4,y+1+a.gazeY*1.8f,4,std::max(2.0f,eyeH-3),"#353d3e","none",0,"pupil");
     c.ellipse(x+13+a.gazeX*4,y+2,3,3,"#ffffff","none",0,"pupil");
     c.line(x-1,y+1,x+33,y+1,outline,2.3f);
   }
   c.line(x,y-8,x+30,y-10,"#4a4244",2);
 }
 c.ellipse(99+hx,151+hy,23,7,"#f1bdba","none",0); c.ellipse(198+hx,151+hy,23,7,"#f1bdba","none",0);
 c.line(157+hx,146+hy,155+hx,151+hy,"#c19a8b",1);
 c.curve({{148+hx,164+hy},{155+hx,169+hy},{164+hx,169+hy},{172+hx,163+hy}},"none","#946c70",1.7f);
 // Thin rectangular glasses, gently raised during the glasses gesture.
 float gy=glasses?-gesture*3:0;
 c.roundRect(99+hx,128+hy+gy,48,24,5,"none","#4e5260",1.8f);
 c.roundRect(171+hx,128+hy+gy,48,24,5,"none","#4e5260",1.8f);
 c.line(147+hx,135+hy+gy,171+hx,135+hy+gy,"#4e5260",1.5f);
 c.line(83+hx,129+hy,99+hx,134+hy+gy,"#4e5260",1.8f);c.line(219+hx,134+hy+gy,235+hx,129+hy,"#4e5260",1.8f);
 // Layered tapered bangs, swept around the forehead rather than covering the eyes.
 c.curve({{70+hx,117+hy},{53+hx,83+hy},{83+hx,31+hy},{116+hx,35+hy},{122+hx,12+hy},{162+hx,15+hy},{180+hx,31+hy},{209+hx,22+hy},{246+hx,55+hy},{246+hx,84+hy},{266+hx,101+hy},{251+hx,116+hy},{234+hx,126+hy},{233+hx,101+hy},{218+hx,77+hy},{200+hx,63+hy},{197+hx,91+hy},{207+hx,108+hy},{180+hx,102+hy},{172+hx,82+hy},{170+hx,64+hy},{163+hx,90+hy},{142+hx,112+hy},{119+hx,118+hy},{129+hx,97+hy},{135+hx,79+hy},{106+hx,98+hy},{88+hx,119+hy},{84+hx,137+hy},{74+hx,126+hy}},"#373544",outline,2);
 c.curve({{85+hx,78+hy},{110+hx,41+hy},{144+hx,33+hy},{174+hx,40+hy}},"none","#646072",3);
 c.curve({{144+hx,50+hy},{163+hx,38+hy},{190+hx,45+hy},{213+hx,58+hy}},"none","#595467",2);
 c.curve({{99+hx,89+hy},{121+hx,74+hy},{136+hx,59+hy},{143+hx,45+hy}},"none","#555164",2);
 // Keyboard stays fixed; the hands are independent articulated limbs.
 c.roundRect(78,263,164,29,7,"#dce9f1","#93aec2",1.7f);
 for(int row=0;row<3;row++) for(int k=0;k<11;k++) c.roundRect(85+k*13.5f,267+row*7,10,4,1,"#ffffff","none",0);
 float leftX=117,leftY=246-float(a.pulseLeft)*7,rightX=203,rightY=246-float(a.pulseRight)*7;
 if(tea||sweet) {leftX-=gesture*4;leftY-=gesture*75;}
 if(glasses) {rightX=211-gesture*3;rightY-=gesture*105;}
 c.line(109,195,leftX,leftY,outline,24);c.line(109,195,leftX,leftY,coat,21);
 c.line(207,194,rightX,rightY,outline,24);c.line(207,194,rightX,rightY,coat,21);
 c.ellipse(leftX-11,leftY-6,24,19,skin,outline,1.4f);c.ellipse(rightX-12,rightY-6,24,19,skin,outline,1.4f);
 if(tea) {
   c.ellipse(leftX+9,leftY-16,18,20,"none","#6fabc5",4);
   c.roundRect(leftX-12,leftY-25,29,29,5,"#acd6e8","#6797b3",1.5f);
   c.ellipse(leftX-12,leftY-27,29,7,"#d9edf5","#6797b3",1);
 } else if(sweet) {
   c.roundRect(leftX-3,leftY-29,22,26,3,"#674a42","#4e3835",1.3f);
   c.line(leftX+8,leftY-26,leftX+8,leftY-6,"#997666",1);c.line(leftX,leftY-17,leftX+17,leftY-17,"#997666",1);
 }
}
}
