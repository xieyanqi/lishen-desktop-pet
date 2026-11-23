#pragma once
#include "Pose.hpp"
#include <initializer_list>
namespace lishen {
// Portable vector scene, rendered by GDI+ in Windows and SVG in the preview.
// Drawing and animation code is original. No KuroCat artwork is used.
template<class C> void character(C& c,const Animation& a) {
 const char* outline="#353647"; const char* skin="#f7dfd1";
 const char* coat=a.rest?"#343442":"#f7fafc";
 const Pose p=pose(a);
 float hx=p.headX,hy=p.headY;
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
     c.ellipse(x+17-6*a.pupil+a.gazeX*4,y+a.gazeY*1.8f,12*a.pupil,eyeH,"#858367","none",0,"pupil");
     c.ellipse(x+17-2*a.pupil+a.gazeX*4,y+1+a.gazeY*1.8f,4*a.pupil,std::max(2.0f,eyeH-3),"#353d3e","none",0,"pupil");
     c.ellipse(x+13+a.gazeX*4,y+2,3,3,"#ffffff","none",0,"pupil");
     c.line(x-1,y+1,x+33,y+1,outline,2.3f);
   }
   c.line(x,y-8,x+30,y-10,"#4a4244",2);
 }
 c.ellipse(99+hx,151+hy,23,7,"#f1bdba","none",0); c.ellipse(198+hx,151+hy,23,7,"#f1bdba","none",0);
 c.line(157+hx,146+hy,155+hx,151+hy,"#c19a8b",1);
 c.curve({{148+hx,164+hy},{155+hx,169+hy},{164+hx,169+hy},{172+hx,163+hy}},"none","#946c70",1.7f);
 // Thin rectangular glasses, gently raised during the glasses gesture.
 float gy=p.glassesY;
 c.roundRect(99+hx,128+hy+gy,48,24,5,"none","#4e5260",1.8f);
 c.roundRect(171+hx,128+hy+gy,48,24,5,"none","#4e5260",1.8f);
 c.line(147+hx,135+hy+gy,171+hx,135+hy+gy,"#4e5260",1.5f);
 c.line(83+hx,129+hy,99+hx,134+hy+gy,"#4e5260",1.8f);c.line(219+hx,134+hy+gy,235+hx,129+hy,"#4e5260",1.8f);
 // Layered tapered bangs, swept around the forehead rather than covering the eyes.
 c.curve({{70+hx,117+hy},{53+hx,83+hy},{83+hx,31+hy},{116+hx,35+hy},{122+hx,12+hy},{162+hx,15+hy},{180+hx,31+hy},{209+hx,22+hy},{246+hx,55+hy},{246+hx,84+hy},{266+hx,101+hy},{251+hx,116+hy},{234+hx,126+hy},{233+hx,101+hy},{218+hx,77+hy},{200+hx,63+hy},{197+hx,91+hy},{207+hx,108+hy},{180+hx,102+hy},{172+hx,82+hy},{170+hx,64+hy},{163+hx,90+hy},{142+hx,112+hy},{119+hx,118+hy},{129+hx,97+hy},{135+hx,79+hy},{106+hx,98+hy},{88+hx,119+hy},{84+hx,137+hy},{74+hx,126+hy}},"#373544",outline,2);
 c.curve({{85+hx,78+hy},{110+hx,41+hy},{144+hx,33+hy},{174+hx,40+hy}},"none","#646072",3);
 c.curve({{144+hx,50+hy},{163+hx,38+hy},{190+hx,45+hy},{213+hx,58+hy}},"none","#595467",2);
 c.curve({{99+hx,89+hy},{121+hx,74+hy},{136+hx,59+hy},{143+hx,45+hy}},"none","#555164",2);
 // Fixed keyboard; only the two contacted keys move down with their fingers.
 c.roundRect(78,263,164,29,7,"#dce9f1","#93aec2",1.7f);
 for(int row=0;row<3;row++) for(int k=0;k<(row==0?10:row==1?9:7);k++) {
   float press=row==a.left.row && k==a.left.col?p.pressLeft:row==a.right.row && k==a.right.col?p.pressRight:0;
   c.roundRect(85+k*13.5f+row*3,267+row*7+press*1.6f,10,4,1,
       press>.15f?"#9dc9e1":"#ffffff","none",0);
   const char* letters[]={"QWERTYUIOP","ASDFGHJKL","ZXCVBNM"};
   c.legend(90+k*13.5f+row*3,271+row*7+press*1.6f,letters[row][k]);
 }
 // Articulated shoulders, elbows, forearms, cuffs, palms, and fingers.
 auto arm=[&](Point shoulder,Point palm,bool right){
   Point wrist{palm.x,palm.y-5};Point bend=elbow(shoulder,wrist,45,52,right);
   c.line(shoulder.x,shoulder.y,bend.x,bend.y,outline,23);
   c.line(bend.x,bend.y,wrist.x,wrist.y,outline,21);
   c.line(shoulder.x,shoulder.y,bend.x,bend.y,coat,20);
   c.line(bend.x,bend.y,wrist.x,wrist.y,coat,18);
   c.line(wrist.x-6,wrist.y-3,wrist.x+6,wrist.y-3,"#b4c4d0",1.3f);
   c.ellipse(palm.x-10,palm.y-7,20,17,skin,outline,1.2f);
 };
 arm({109,195},p.leftPalm,false);arm({207,194},p.rightPalm,true);
 auto fingers=[&](Point palm,float reach,Point index){
   // A small fan of fingers rests on keys. The index unfolds toward the frame.
   for(int j=0;j<3;j++){
     float x=palm.x-6+j*5;
     float tipY=palm.y+15-j;
     if(j==2 && reach>.001f) {
       Point base{palm.x+3,palm.y-1};
       Point knuckle=mix(Point{palm.x+8,palm.y+6},Point{index.x-4,index.y+8},reach);
       c.line(base.x,base.y,knuckle.x,knuckle.y,outline,6);
       c.line(knuckle.x,knuckle.y,index.x,index.y,outline,5);
       c.line(base.x,base.y,knuckle.x,knuckle.y,skin,3.8f);
       c.line(knuckle.x,knuckle.y,index.x,index.y,skin,2.8f);
     } else {
       c.line(x,palm.y+3,x,tipY,outline,5);
       c.line(x,palm.y+3,x,tipY,skin,3);
     }
   }
 };
 if(a.pet>.45f)for(int i=0;i<3;i++){
   float phase=float(std::fmod(a.time*.65+i/3.,1.));
   float size=(3+phase*4)*std::sin(phase*3.14159f)*a.pet;
   c.ellipse(239+i*7+phase*10,103-phase*35,size,size,"#e8f6fc","#89bdd8",1);
 }
 fingers(p.leftPalm,0,{0,0});fingers(p.rightPalm,p.reach,p.indexTip);
}
}
