//! nolibc printf copyright (c) 2020 regents of kparc, bsd-2-clause
#include"_.h"

#ifndef PRINTF
#include<unistd.h> //<! size_t write(2)
#define VMX 16
typedef union{UJ uj;}arg;typedef arg args[VMX]; //!< avoid gcc error
#define PU(f,t) ZZ S f(S s,t i){t j;do*--s='0'+i-10*(j=i/10);W(i=j);R s;} //!< parse signed/unsigned
#define TU(f,t,u) ZZ I f(t x,I p,I l){I n;S r=jS(x,&n,u);R txp(r,n,p);}   //!< tx signed/unsigned

//! strlen memset parseint itoa atoi hexstr
ZG xb[26];ZI sln(S s){I r=0;W(*s++)r++;R r;}ZS ng(S s){R*--s='-',s;}PU(pj,J)PU(pu,UJ);
ZS jS(UJ i,I*n,G u){S r=(!u&&0>(J)i)?ng(jS(-i,n,u)):u?pu(xb+25,i):pj(xb+25,i);R*n=25+(xb-r),r;}
UI sI(S a,I*n){G c;UI i=0,r=*n=0;W((c=*a++)&&IN('0',c,'9'))i++,r=r*10u+((UI)c-'0');R*n=i,r;}ZS hh(S s,G c);
ZS hh(S s,G c){N(2,G a=i?c&15:c>>4;s[i]="0W"[9<a]+a)R s;}ZI jX(UJ j){S s=xb+25;UJ k=j;do hh(s-=2,k);W(k>>=8);R 25-(s-xb);}

//! (tx)byte (txn)bytes (txN)times (b)yte (i)nt he(x) (s)tr (p)ad
ZI tx(G c){R write(1,&c,1);}ZI txn(S x,I n){P(!n,n)N(n,tx(x[i]));R n;}ZI txN(G c,I n){N(n,tx(c))R n;}
ZI txp(S x,I n,I p){R txN(' ',MX(0,p-n))+txn(x,n)+txN(' ',ABS(MN(0,p+n)));}ZI txb(G c,I p,I l){R txp(&c,1,p);}
ZI txx(UJ j,I p,I l){I n=jX(j)+2;S b=xb+25-n;*b='0',b[1]='x';R txp(b,n,p);}TU(txj,J,0)TU(txu,UJ,1)
ZI txs(S x,I p,I l){R txp((S)x,l?l:sln(x),p);}

#define vi (a[i++].uj)
#define pf(f,a...) txpf(f,(args){a})  //!< arguments of pf() coerced to an array of ulls, up to VMX
#define va(c,t,f) C(c,n+=f((t)vi,flg*flw,prc);) //!< call f((type)nextarg,options)
#define nx continue

//! %[%-][09..][.09..*]dcups
I txpf(S f,args a){                   //!< (f)ormat string (aka tape), (a)rguments
 G c;I j,i=0,n=0;                     //!< total le(n)gth, arg(i)ndex, curr(c)har
 UI flg,flw,prc;                      //!< fmt flags, field width, precision
 W(c=*f++){                           //!< while more chars left on tape,
  flg=prc=0,flg=j=1;                  //!< reset state, then:
  Z('%'-c,tx(c);nx)                   //!< echo c unless %, otherwise:
  W(j)SW(c=*f,C('-',flg=-1,f++),j=0)  //!< scan flags (%flg)
  flw=sI(f,&j),f+=j,c=*f;             //!< scan field width (%flw)
  Z('.'==c,prc=sI(++f,&j);f+=j;c=*f;  //!< scan precision (%.prc)
   Z(!j,Z('*'-c,f++;nx)               //!< %.[not 09*] is empty field
    c=*++f;prc=(I)vi))c=*f;           //!< scan positional precision (%.*)
  W('l'==c||'h'==c)c=*++f;            //!< skip [lh..] nyi
  SW(c,                               //!< conversion specifier dispatch
   va('c',G,txb)va('d',J,txj)va('u',UJ,txu)
   va('p',UJ,txx)va('s',S,txs)C('%',tx(c)))
  f++;}R n;}

_ exit(I);
#if NOLC
ZS memset(S x,I c,I n){N(n,x[i]=c);R x;}ZS memcpy(S d,S s,I n){W(n--)*d++=*s++;R d;}
#endif
#else
#define pf printf
#define sln strlen
#endif//PRINTF

#ifndef LIB
I main(I c,char**a){

  ZS t_prc="kparcxxxx";
  pf("\n  (%%)=(%%) (kparc)=(%.*s) (kparc)=(%.5s) ()=(%.s)\n",5LL,t_prc,t_prc,t_prc);

  UJ umx= 18446744073709551615ULL;
  J  jmx=  9223372036854775807LL;
  I  imx=           2147483647;
  UI uimx=          4294967295U;

  pf("\n   umx = (%20llu)\n   jmn = (%20lld)\n   jmx = (%20lld)\n   imn = (%20d)\n   imx = (%20d)\n  uimx = (%20u)\n",umx,-jmx,jmx,-imx,imx,uimx);

  pf("\n  pmx32 = (%19p)\n  pmx64 = (%19p)\n",uimx,umx);

  I n;S ti,t[]={"atw","nsl","attila","icsa","alex","ktye","kparc"};pf("\n");
  N(7,ti=t[i],n=sln(ti);pf("%3d|%-8s|%8s|%3d|%-3d|%12p|%-5p|%3c|%-3c|%%|\n",i,ti,ti,n,n,0xdeadbeef,0x04,'k','k'))

  pf(" n=(%d) %s\n\n",
   pf("\n pf: s=(%s %s %s) p=(%p) c=(%c) eot=(%p)",
    "i uncover","the soul-destroying","abhorrence",0xcafebabe,'K',0x04)
  ,"//:~");

  R exit(0),0;}
#endif

//:~
