 #version 430
 layout(location=2)uniform ivec4 m;
 layout(binding=0)uniform sampler3D l;
 layout(binding=1)uniform sampler2D i;
 float z=(m.x*73856093^int(gl_FragCoord.x)*19349663^int(gl_FragCoord.y)*83492791)%38069,v=6.283,y=.1,a=m.y/44100.,x=m.z/44100.;
 float s()
 {
   return fract(sin(z++)*43758.5);
 }
 float s(float v,float a)
 {
   return(abs(mod(a-v,.1818)-.0909)+v+a)/2;
 }
 float h(vec3 a,vec3 z)
 {
   return length(max(abs(a)-z,0));
 }
 float h(vec3 m)
 {
   m.xz*=mat2(1,1,-1,1)*.7071;
   float l=min(min(1-s(length(m.xz),abs(m.y)),s(length(m.xz),m.y)+.2),length(m-vec3(normalize(m.xz)*.45,0).xzy)-.02);
  l=min(l,m.y+1);
   m=abs(m);
   if(m.z>m.x)
     m.xz=m.zx;
   return min(min(l,length(m-vec3(normalize(m.xy)*.45,0))-.02),a>120?length(m)-.4:100.);
 }
 float s(vec3 m)
 {
   float i=min(m.y+.2,-(abs(length(m.xz)-1.85)-1.65-clamp(m.y-1,-1,0)));
   i=min(i,max(m.y-.15,2.5-length(m.xz)));
   m.xz=vec2(length(m.xz)-2,mod(atan(m.z,m.x)/v*9,1)-.5);
   return min(i,min(min(min(h(m-vec3(0,.05,0),vec3(.135,.025,.15)),h(m-vec3(-.13,.3,0),vec3(.025,.15,.15)))-.01,max(m.y,length(m.xz)-.02)+min(m.y+.1,0)),h(m-vec3(-.15,.2,0),vec3(.025,.15,.05))));
 }
 float n(vec3 m)
 {
   return m.z-=.8,min(min(min(max(min(min(max(s(length(m.xz)-1,.3+.1*cos(m.y*4)),-s(length(m.xz)-.95,.3+.1*cos(m.y*14))),s(length(m.xz)-.35,.1+.15*cos(m.y*2.2))),max(s(length(m.xz)-.4,.1+.15*cos(m.y*20.2)),-(length(m.xz)-.4))),m.z-.375),-(length(m.xz)-1.4)),length(m.xz-vec2(.5,.9))-.1),length(m.xz-vec2(-.3,.9))-.1);
 }
 float f(vec3 m)
 {
m.xz*=mat2(1,-1,-1,-1)*.7071;
   float l=min(s(length(m.xy)-.25,s(h(m,vec3(.2))-.5,abs(s(length(m.xz)-1,.6)))),h(m-vec3(0,(a-55)/5.+7,4.7),vec3(1,8,.8)));
   m.z-=1;
   return min(min(l-.2,1-s(length(m.xzy)-1,s(length(m.xy)-1,.6+.2*cos(m.z*3+m.y)))),m.y+.6+cos(m.z*80)/2000);
 }
 float t(vec3 m)
 {
   return a<43?s(m):a<75?f(m):a<103?n(m):h(m);
 }
 vec3 e(float m)
 {
   return a<43?vec3(-1.7+m/30,1.2,5.1)/2:a<75?vec3(.2-1.5*fract((m-43)/70),-.4,1):a<103?vec3(0,m/30+1.5,m<82.5?1.5:m<90?1.75:2):vec3(0,-.3+(m-120)/60,1.4);
 }
 vec3 g=e(a),w=e(x),r=(vec3(s(),s(),s())-.5)/256;
 vec3 e(vec3 m,vec3 z)
 {
   return m-=z,vec3(-m.xy/m.z*vec2(.28125,.5)+.5,length(m)*32);
 }
 vec3 e(vec3 m,vec3 v,float z)
 {
   vec3 i=vec3(0);
   float y=1;
   for(int F=0;F++<120&&y>.01;)
     {
       vec3 d=e(m+=v*.03,g);
       vec4 t=textureLod(l,r+vec3(d.xy,d.z/256),log2(F*z/7));
       i+=t.xyz*y;
       y*=1-t.w;
     }
   return i;
 }
 void main()
 {
   vec4 z=vec4(0);
   vec2 x=vec2(mod(float(m.x),2.)/2,mod(m.x/2.,2.)/2);
   vec3 f=g,n=normalize(vec3((gl_FragCoord.xy+x)/360+vec2(s()-.5,s()-.5)/60*(1-smoothstep(0,1,abs(a-9)/2)+1-min(texelFetch(i,ivec2(gl_FragCoord.xy),0).w/.1,1))-vec2(1.7778,1),-1));
   if(m.w<1)
     {
       for(int F=0;F++<120&&abs(y=t(f+=n*y*.8))>.0001;)
         ;
       vec3 d=vec3(.001,0,0),r=normalize(vec3(t(f+d.xyy),t(f+d.yxy),t(f+d.yyx))-y);
       if(a<43||a>=75&&a<103)
         r=normalize(r+vec3(0,sin(clamp((mod(f.y+.12,.05)/.05-.8)/.2*v,0.,v)),0));
       vec3 c=f,h=reflect(n,r),p=normalize(cross(r.xyz,r.zxy)),o=cross(r.xyz,p),u=vec3(.9);
       z.w=length(f-g)/255*32;
       float b=1+8*step(.5,fract(atan(f.z-.8,f.x)/v*32));
       if(a<43)
         {
           if(length(f.xz)>1&&abs(f.y-1.)<.1)
             z.xyz=vec3(1,.4,.2);
           float F=atan(f.z,f.x)/v*40;
           if(abs(length(f.xz)-2.8)<.1&&fract(F)>.03&&cos(floor(F)*9)+2.1<a/13.)
             z.xyz+=.7;
           if(length(f.xz)<.35)
             z.xyz=vec3(1,.1,.02);
           b=2;
         }
       else
          if(a<75)
           {
				 f.xz*=mat2(1,-1,-1,-1)*.7071;
             if(abs(f.z)>3.8||(f.z>3.&&(a>50&&abs(length(f.xy)-1)<.02)||abs(length(f.xy)-1.4)<.02))
               z.xyz=vec3(1,.7,.5);
             if(f.y<-.5999&&(abs(abs(f.x)-.7)<.2||abs(abs(f.z)-.8)<.03))
               z.xyz=vec3(1,.4,.2)/2;
  	 if(abs(f.z)<1&&abs(abs(f.y)-.2)<.01)
                z.xyz=vec3(1,.2,.1);
             b=1;
             u/=1.3;
           }
         else
            if(a<103)
             {
               if(length(f.xz-vec2(0,.8))<.125)
                 z.xyz=vec3(1,.8,.6);
               if(abs(f.x)>1.3)
                 z.xyz=vec3(1,.4,.2)*1.2;
               if(f.z+f.x/2<-.7)
                 z.xyz=vec3(1,.2,.1);
               u/=1.4;
             }
           else
             {
               if(r.y<-.999&&length(f)>1)
                 z.xyz=vec3(1,.4,.2)/(2-step(f.y,0));
               if(length(f)<.41&&a>120)
                 z.xyz+=1;
             }
       f=c+r*.05;
       z.xyz+=e(f,h,b)*.75*clamp(1-dot(-n,r),0,1);
       for(int F=0;F++<4;)
         {
           float C=v*s(),q=s();
           z.xyz+=e(f,(p*cos(C)+o*sin(C))*sqrt(q)+r*sqrt(1.-q),7)/4*u*sqrt(1.-q);
         }
       f=w;
       y=.1;
       for(int F=0;F++<120&&abs(y=t(f+=normalize(vec3((gl_FragCoord.xy+vec2(mod(m.x-1.,2.)/2,mod((m.x-1)/2.,2.)/2))/360-vec2(1.7778,1),-1))*y*.8))>.0001;)
         ;
       z.xyz=mix(clamp(z.xyz+s()/600,0,1),texture(i,e(c,w).xy-x/vec2(1280,720)).xyz,length(f-c)<.05?.82:.6)*smoothstep(0.,4.,min(a,min(min(abs(a-43),abs(a-75)),abs(a-103))));
     }
   else
      if(m.w<2)
       {
         int r=8-int(log2(511-gl_FragCoord.x));
         if(r==0)
           {
             f=g+normalize(vec3((gl_FragCoord.x/128-1)*1.7778,gl_FragCoord.y/128-1,-1))*m.x*.03125;
             y=t(f);
             if(y<-.1)
               z.w=smoothstep(.1,.2,-y);
             else
               {
                 for(int F=-3;F<4;++F)
                   for(int c=-3;c<4;++c)
                     {
                       vec4 d=texelFetch(i,ivec2(c,F)+ivec2(e(f,w).xy*vec2(1280,720)),0);
                       if(abs(m.x-d.w*255)<2)
                         z.xyz+=d.xyz,z.w+=1;
                     }
                 if(z.w>0.)
                   z/=z.w;
               }
           }
         else
			{
            for(int F=0;F<2;++F)
             for(int c=0;c<2;++c)
               for(int d=0;d<2;++d)
                 z+=texelFetch(l,ivec3(gl_FragCoord.xy-vec2(511-(exp2(9-r)-1),0),m.x)*2+ivec3(d,c,F),r-1)/8;
			}
       }
     else
       {
         vec2 r=abs(gl_FragCoord.xy/vec2(640,360)-1);
         z=textureLod(i,gl_FragCoord.xy/vec2(1280,720)+.02,6.5);

         z=(z*z+texelFetch(i,ivec2(gl_FragCoord.xy),0))*(2.3-(pow(r.x,8.)+pow(r.y,8.))*.7);

         z=pow(z/(z+1)*2.3,vec4(.8))*step(1e-3,a);
         a-=120;
         r*=exp(-a/7)/(.05+length(r))*4;
         for(int F=0;F++<15;)
           r+=vec2(cos(r.y*8),sin(r.x*4+r.x*9)-a/8+1)/7.,r=abs(r);
         z+=exp(-length(r));
       }
   gl_FragColor=z;
 };
